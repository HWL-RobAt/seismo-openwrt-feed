/**@file Network.hpp
 * @note Generated file, find templates in SX folders (under bricks/).
 */

#ifndef NETWORK_HPP_INCLUDED
#define NETWORK_HPP_INCLUDED

#include "RTDS_gen.h"
#include "RTDS_Common.h"
#include "../BlockMember.h"
#include "../NetworkTopology.h"
#include "../Common.h"
#include "Messages.h"

#include <vector>



namespace Network
{
	
	/**@brief This is the system block.
	 */
	struct System
	:	RTDS::SDLBlock
	{
		blockClass_node b_blockClass_node;
		Admin* p_Admin[1];
		
		/**@brief Constructor for the system block.
		 */
		System(RTDS::Logger& logger = RTDS::emptyLogger)
		:	RTDS::SDLBlock(logger),
			b_blockClass_node(logger, this)
		{
			for (int i = 0; i < 1; ++i)
			{
				embed(*(p_Admin[i] = new Admin(logger)),
				      RTDS_process_Admin);
			}
		}
		
		/**@brief Starts all sub-blocks and contained processes.
		 */
		void activate()
		{
			b_blockClass_node.activate();
			for (int i = 0; i < 1; ++i)
			{
				(*p_Admin[i]).activate();
			}
		}
		
	};
	
}

#endif	/* NETWORK_HPP_INCLUDED */
