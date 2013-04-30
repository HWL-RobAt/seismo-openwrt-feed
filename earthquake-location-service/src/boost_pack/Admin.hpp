/**@file Admin.hpp
 * @note Generated file, find templates in SX folders (under bricks/).
 */

#ifndef ADMIN_HPP_INCLUDED
#define ADMIN_HPP_INCLUDED

#include "RTDS_SDLPROCESS.hpp"

namespace Network
{
	
	/**@brief This is the process Admin.
	 */
	struct Admin
	:	RTDS::SDLProcess
	{
		
		/**@brief Constructor for Admin.
		 */
		Admin(RTDS::Logger& logger = RTDS::emptyLogger)
		:	RTDS::SDLProcess(logger)
		{}
		
		/**@brief Lifeline of this process.
		 */
		virtual int main();
		
	private:
	};
	
}

/* post-includes */
#include "Network.hpp"


#endif	/* ADMIN_HPP_INCLUDED */
