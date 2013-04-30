/**@file blockClass_node.hpp
 * @note Generated file, find templates in SX folders
 */

#ifndef BLOCKCLASS_NODE_HPP_INCLUDED
#define BLOCKCLASS_NODE_HPP_INCLUDED


#include "Creator.hpp"
#include "Common.h"

class NetworkHandler;

namespace Network
{
	
	/**@brief This is the blockClass_node.
	 */
	struct blockClass_node
	:	RTDS::SDLBlock
	{
		Creator* p_Creator[1];
		
		NetworkHandler* handler;

		/**@brief Constructor for blockClass_node.
		 */
		blockClass_node(RTDS::Logger& logger = RTDS::emptyLogger,
				RTDS::SDLBlock* cover = NULL)
		:	RTDS::SDLBlock(logger, cover)
		{
			for (int i = 0; i < 1; ++i)
			{
				embed(*(p_Creator[i] = new Creator(logger)),
				      RTDS_process_Creator);
			}
		}
		
		/**@brief Starts all sub-blocks and contained processes.
		 */
		void activate()
		{
			for (int i = 0; i < 1; ++i)
			{
				(*p_Creator[i]).activate();
			}
		}
		
	};
	
}

/* post-includes */
#include "../BlockMember.h"
#include "../NetworkTopology.h"
#include "../Common.h"
#include "Messages.h"

#include <iostream>


#endif	/* BLOCKCLASS_NODE_HPP_INCLUDED */
