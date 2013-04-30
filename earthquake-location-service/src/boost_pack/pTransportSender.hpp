/**@file pTransportSender.hpp
 * @note Generated file, find templates in SX folders (under bricks/).
 */

#ifndef PTRANSPORTSENDER_HPP_INCLUDED
#define PTRANSPORTSENDER_HPP_INCLUDED

#include "RTDS_SDLPROCESS.hpp"

namespace Network
{
	
	/**@brief This is the process pTransportSender.
	 */
	struct pTransportSender
	:	RTDS::SDLProcess
	{
		
		/**@brief Constructor for pTransportSender.
		 */
		pTransportSender(RTDS::Logger& logger = RTDS::emptyLogger)
		:	RTDS::SDLProcess(logger)
		{}
		
		/**@brief Lifeline of this process.
		 */
		virtual int main();
		
	private:
		
		/**@brief Method sendMessage 
		 * @param[in] RTDS_GlobalProcessInfo * RTDS_currentContext 
		 * @param[in] NetworkTopologyPtr topology 
		 * @param[in] ID receiverID 
		 * @param[in] int type 
		 * @param[in] payload_t payload 
		 * @return void
		 */
		void sendMessage(RTDS_GlobalProcessInfo * RTDS_currentContext, NetworkTopologyPtr topology, ID receiverID, int type, payload_t payload);
	};
	
}

/* post-includes */
#include "../BlockMember.h"
#include "../NetworkTopology.h"
#include "../Common.h"
#include "Messages.h"
#include "NetworkConnection.h"
#include "NetworkHandler.h"

#endif	/* PTRANSPORTSENDER_HPP_INCLUDED */
