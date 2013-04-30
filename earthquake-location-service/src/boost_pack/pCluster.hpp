/**@file pCluster.hpp
 * @note Generated file, find templates in SX folders (under bricks/).
 */

#ifndef PCLUSTER_HPP_INCLUDED
#define PCLUSTER_HPP_INCLUDED

#include "RTDS_SDLPROCESS.hpp"

namespace Network
{
	
	/**@brief This is the process pCluster.
	 */
	struct pCluster
	:	RTDS::SDLProcess
	{
		
		/**@brief Constructor for pCluster.
		 */
		pCluster(RTDS::Logger& logger = RTDS::emptyLogger)
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


#endif	/* PCLUSTER_HPP_INCLUDED */
