
#include "RTDS_SDLBLOCK.hpp"


namespace RTDS
{
	
	void
	SDLBlock::embed(SDLBlock& block)
	{
		std::vector<MessageQueue::qWriter*>::iterator iter;
		unsigned id;
		
		block.cover = this;
		for (iter = block.context.begin(), id = 0;
		     iter != block.context.end();
		     ++iter, ++id)
		{
			if (*iter)
				embed(**iter, id);
		}
	}
	
	void
	SDLBlock::embed(MessageQueue::qWriter& writer, unsigned id)
	{
		std::vector<MessageQueue::qWriter*>::iterator iter;
		
		if (context.size() <= id)
			context.resize(id+1);
		
		/* don't recurse if the definition exists already */
		if (!context[id])
		{
			if (cover)
				cover->embed(writer, id);
			
			context[id] = &writer;
		}
	}
	
	MessageQueue::qWriter*
	SDLBlock::getMsgQWriterByID(unsigned id) const
	{
		const SDLBlock* block;
		
		/* look for the ID in the covering blocks */
		block = this;
		do
		{
			if (block->context.size() > id && block->context[id])
			{
				return block->context[id];
			}
		}
		while ((block = block->cover));
		
		return NULL;
	}
	
}
