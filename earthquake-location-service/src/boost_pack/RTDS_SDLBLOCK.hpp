
#ifndef RTDS_ODEMX_H_INCLUDED
#define RTDS_ODEMX_H_INCLUDED

#include <vector>

#include "RTDS_SDLPROCESS.hpp"
#include "RTDS_LOGGER.hpp"
#include "RTDS_MSGQUEUE.hpp"


namespace RTDS
{
	
	/**@brief Base structure for generated SDL blocks.
	 */
	struct SDLBlock
	{
	protected:
		SDLBlock* cover;
		std::vector<MessageQueue::qWriter*> context;
		Logger& logger;
		
	public:
		/**@brief Initializing constructor.
		 */
		SDLBlock(Logger& logger, SDLBlock* cover = NULL);
		
		
		/**@brief Registers a block as being covered by this block.
		 */
		void embed(SDLBlock& block);
		
		/**@brief Registers a process for call-by-name functionality.
		 */
		void embed(SDLProcess& process, unsigned id);
		
		/**@brief Registers a message queue for call-by-name
		 * functionality.
		 */
		void embed(MessageQueue::qWriter& writer, unsigned id);
		
		/**@brief Returns the message queue from a process that is
		 * specified by an ID.
		 */
		MessageQueue::qWriter* getMsgQWriterByID(unsigned id) const;
	};
	
	
	/* ******************************************** INLINE IMPLEMENTATION */
	
	inline
	SDLBlock::SDLBlock(Logger& _logger, SDLBlock* _cover)
	:	cover(_cover),
		logger(_logger)
	{}
	
	inline void
	SDLBlock::embed(SDLProcess& process, unsigned id)
	{
		embed(process.getPort(), id);
		process.cover = this;
	}
	
}

#endif
