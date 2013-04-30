/**@file pTransportReceiver.hpp
 * @note Generated file, find templates in SX folders (under bricks/).
 */

#ifndef PTRANSPORTRECEIVER_HPP_INCLUDED
#define PTRANSPORTRECEIVER_HPP_INCLUDED

#include "RTDS_SDLPROCESS.hpp"

namespace Network
{
	
	/**@brief This is the process pTransportReceiver.
	 */
	struct pTransportReceiver
	:	RTDS::SDLProcess
	{
		
		/**@brief Constructor for pTransportReceiver.
		 */
		pTransportReceiver(RTDS::Logger& logger = RTDS::emptyLogger)
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


#endif	/* PTRANSPORTRECEIVER_HPP_INCLUDED */
