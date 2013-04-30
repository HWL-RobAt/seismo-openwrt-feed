/**@file pApp.hpp
 * @note Generated file, find templates in SX folders (under bricks/).
 */

#ifndef PAPP_HPP_INCLUDED
#define PAPP_HPP_INCLUDED

#include "RTDS_SDLPROCESS.hpp"

namespace Network
{
	
	/**@brief This is the process pApp.
	 */
	struct pApp
	:	RTDS::SDLProcess
	{
		
		/**@brief Constructor for pApp.
		 */
		pApp(RTDS::Logger& logger = RTDS::emptyLogger)
		:	RTDS::SDLProcess(logger)
		{}
		
		/**@brief Lifeline of this process.
		 */
		virtual int main();
		
	private:
	};
	
}

/* post-includes */
#include "../BlockMember.h"
#include "../NetworkTopology.h"
#include "../Common.h"
#include "Messages.h"


#endif	/* PAPP_HPP_INCLUDED */
