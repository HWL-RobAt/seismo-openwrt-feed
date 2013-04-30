/**@file Creator.hpp
 * @note Generated file, find templates in SX folders (under bricks/).
 */

#ifndef CREATOR_HPP_INCLUDED
#define CREATOR_HPP_INCLUDED

#include "RTDS_SDLPROCESS.hpp"

#include "BlockMember.h"

namespace Network
{
	
	/**@brief This is the process Creator.
	 */
	struct Creator
	:	RTDS::SDLProcess
	{
		
		BlockMemberPtr blockMember;

		/**@brief Constructor for Creator.
		 */
		Creator(RTDS::Logger& logger = RTDS::emptyLogger)
		:	RTDS::SDLProcess(logger)
		{}
		
		/**@brief Lifeline of this process.
		 */
		virtual int main();
		
	private:
	};
	
}

/* post-includes */
#include "blockClass_node.hpp"


#endif	/* CREATOR_HPP_INCLUDED */
