/** @file
 *  Generated file, find templates in SX folders
 */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "RTDS_SDLTIMER.hpp"

#include "Network.hpp"
#include "pApp.hpp"
#include "RTDS_messages.h"
#include "RTDS_gen.h"

#define RTDS_PROCESS_NUMBER RTDS_process_pApp
#define RTDS_PROCESS_NAME pApp

/*
** PROCESS pApp:
** -------------
*/



using Network::pApp;

int
pApp::main()
{
  short RTDS_transitionExecuted;
  int RTDS_savedSdlState = 0;

  BlockMemberPtr blockMember;
  RTDS_QueueId myTE;
  int pingCounter;
  ID senderId;
  ID broadcast = BROADCAST_ID;
  ping_t ping_payload;
  pong_t pong_payload;
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
  RTDS_SDL_STATE_SET(RTDS_state_waitForInit);
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
      /* Transitions for state idleLoop */
      case RTDS_state_idleLoop:
        switch(RTDS_currentContext->currentMessage->messageNumber)
          {
          /* Transition for state idleLoop - message mPong */
          case RTDS_message_mPong:
            RTDS_MSG_RECEIVE_mPong(        senderId,         pong_payload);
            break;
          /* Transition for state idleLoop - message mPing */
          case RTDS_message_mPing:
            RTDS_MSG_RECEIVE_mPing(            senderId,             ping_payload);
            pingCounter++;
            pong_payload.i = pingCounter;
            RTDS_MSG_SEND_mPong_TO_ID(myTE,             senderId,             pong_payload);
            break;
          /* Transition for state idleLoop - message waitTimer */
          case RTDS_message_waitTimer:
            RTDS_SET_TIMER(RTDS_message_waitTimer, 5000);
            ping_payload.i = 1;
            RTDS_MSG_SEND_mPing_TO_ID(myTE,             broadcast,             ping_payload);
            break;
          default:
            RTDS_transitionExecuted = 0;
            break;
          } /* End of switch on message */
        break;
      /* Transitions for state waitForInit */
      case RTDS_state_waitForInit:
        switch(RTDS_currentContext->currentMessage->messageNumber)
          {
          /* Transition for state waitForInit - message mHello */
          case RTDS_message_mHello:
            RTDS_MSG_RECEIVE_mHello(        blockMember);
            myTE = blockMember->getBlockMember(TRANSPORT_SENDER);
            RTDS_SET_TIMER(RTDS_message_waitTimer, 5000);
            RTDS_SDL_STATE_SET(RTDS_state_idleLoop);
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
