/** @file
 *  Generated file, find templates in SX folders
 */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "RTDS_SDLTIMER.hpp"

#include "Network.hpp"
#include "pCluster.hpp"
#include "RTDS_messages.h"
#include "RTDS_gen.h"

#define RTDS_PROCESS_NUMBER RTDS_process_pCluster
#define RTDS_PROCESS_NAME pCluster

/*
** PROCESS pCluster:
** -----------------
*/



using Network::pCluster;

int
pCluster::main()
{
  short RTDS_transitionExecuted;
  int RTDS_savedSdlState = 0;

  BlockMemberPtr blockMember;
  RTDS_QueueId myTE; //sender
  ID selfId;
  ID cHead; //cluster head
  ID latest; //last received respRef
  std::list<ID> followerList;

  int rNum;
  srand(time(NULL));
  rNum = rand()/1000000 +1000;//recruitTimerSleep
  /**
  unclustered
  **/
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
  RTDS_SDL_STATE_SET(RTDS_state_waitForHello);
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
      /* Transitions for state waitForHello */
      case RTDS_state_waitForHello:
        switch(RTDS_currentContext->currentMessage->messageNumber)
          {
          /* Transition for state waitForHello - message mHello */
          case RTDS_message_mHello:
            RTDS_MSG_RECEIVE_mHello(        blockMember);
            myTE = blockMember->getBlockMember(TRANSPORT_SENDER);
            RTDS_SDL_STATE_SET(RTDS_state_waitForId);
            break;
          default:
            RTDS_transitionExecuted = 0;
            break;
          } /* End of switch on message */
        break;
      default:
        RTDS_transitionExecuted = 0;
        break;
      } /* End of switch(RTDS_currentContext->sdlState) */
    delete currentMessage;
    }
  
}

/* private methods (if applicable) */
