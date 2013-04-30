/** @file
 *  Generated file, find templates in SX folders
 */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "RTDS_SDLTIMER.hpp"

#include "Network.hpp"
#include "Creator.hpp"
#include "RTDS_messages.h"
#include "RTDS_gen.h"

#define RTDS_PROCESS_NUMBER RTDS_process_Creator
#define RTDS_PROCESS_NAME Creator

/*
** PROCESS Creator:
** ----------------
*/



using Network::Creator;

int
Creator::main()
{
  short RTDS_transitionExecuted;
  int RTDS_savedSdlState = 0;

  #ifdef ODEMX
  blockMember = new BlockMember();
  #elif defined BOOST
  blockMember = new BlockMember();
  #else
  BlockMemberPtr blockMember = new BlockMember();
  #endif
  RTDS_QueueId app, transport_sender, transport_receiver, cluster;
  RTDS_MSG_DATA_DECL

  /* declare framework-side variables for the process */
  RTDS::SDLProcess* const RTDS_currentContext = this;
  int RTDS_sdlStatePrev = sdlState;

  /* starts stdio.run() asynchronous stops when isRunnings destructor is destroyed */
  boost::thread _workThread_t(boost::bind(&boost::asio::io_service::run, &ioService));
  std::auto_ptr<boost::asio::io_service::work> _workThread_ptr(isRunning);
  isRunning = NULL;

  /* silence warnings; these variables are not usually used */
  RTDS_savedSdlState += 0;
  RTDS_sdlStatePrev += 0;
  RTDS_msgData = NULL;
  RTDS_msgData += 0;

  SX_DEBUG("\n=== process " SX_STR(RTDS_PROCESS_NAME) "(%p) %.*s\n"
  "[%llu]\n", msgQueue.writer,
  70 - sizeof("=== process " SX_STR(RTDS_PROCESS_NAME)),
  "===================================================================",
  getCurrentTime());

  /* Initial transition */
  RTDS_PROCESS_CREATE("app", RTDS_process_pApp, pApp, RTDS_DEFAULT_PROCESS_PRIORITY);
  app = OFFSPRING;
  blockMember->addBlockMember(APP,app);
  RTDS_PROCESS_CREATE("transport_sender", RTDS_process_pTransportSender, pTransportSender, RTDS_DEFAULT_PROCESS_PRIORITY);
  transport_sender = OFFSPRING;
  blockMember->addBlockMember(TRANSPORT_SENDER,OFFSPRING);
  RTDS_PROCESS_CREATE("transport_receiver", RTDS_process_pTransportReceiver, pTransportReceiver, RTDS_DEFAULT_PROCESS_PRIORITY);
  transport_receiver = OFFSPRING;
  blockMember->addBlockMember(TRANSPORT_RECEIVER,OFFSPRING);
  RTDS_PROCESS_CREATE("cluster", RTDS_process_pCluster, pCluster, RTDS_DEFAULT_PROCESS_PRIORITY);
  cluster = OFFSPRING;
  blockMember->addBlockMember(CLUSTER,OFFSPRING);
  RTDS_MSG_SEND_mHello_TO_ID(app,   blockMember);
  RTDS_MSG_SEND_mHello_TO_ID(transport_sender,   blockMember);
  RTDS_MSG_SEND_mHello_TO_ID(transport_receiver,   blockMember);
  RTDS_MSG_SEND_mHello_TO_ID(cluster,   blockMember);
  #ifndef ODEMX
  #ifndef BOOST
  RTDS_MSG_SEND_mNodeHello_TO_NAME("Admin", RTDS_process_Admin,   transport_receiver,   transport_sender);
  #endif
  #endif
  RTDS_PROCESS_KILL;
  while (true)
    {
    /* pop new message from queue */
    currentMessage = msgQRead();
    RTDS_LOG_MESSAGE_RECEIVE(&currentMessage->sender, msgQueue.writer,
    currentMessage->sequenceNumber, getCurrentTime());

    SX_DEBUG("\n=== process " SX_STR(RTDS_PROCESS_NAME) "(%p) %.*s\n"
    "[%llu]\n", msgQueue.writer,
    70 - sizeof("=== process " SX_STR(RTDS_PROCESS_NAME)),
    "===================================================================",
    getCurrentTime());
    /* Double switch state / signal */
    RTDS_transitionExecuted = 1;
    switch(RTDS_currentContext->sdlState)
      {
      default:
        RTDS_transitionExecuted = 0;
        break;
      } /* End of switch(RTDS_currentContext->sdlState) */
    delete currentMessage;
    }
  
}

/* private methods (if applicable) */
