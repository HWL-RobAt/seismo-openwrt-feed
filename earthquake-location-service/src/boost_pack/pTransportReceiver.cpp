/** @file
 *  Generated file, find templates in SX folders
 */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "RTDS_SDLTIMER.hpp"

#include "Network.hpp"
#include "pTransportReceiver.hpp"
#include "RTDS_messages.h"
#include "RTDS_gen.h"

#define RTDS_PROCESS_NUMBER RTDS_process_pTransportReceiver
#define RTDS_PROCESS_NAME pTransportReceiver

/*
** PROCESS pTransportReceiver:
** ---------------------------
*/



using Network::pTransportReceiver;

int
pTransportReceiver::main()
{
  short RTDS_transitionExecuted;
  int RTDS_savedSdlState = 0;

  BlockMember* blockMember;
  NetworkTopologyPtr topology;
  int messageType;
  RTDS_QueueId cluster, transport_sender, app;
  payload_t payload;
  ID senderID, ch;
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
            RTDS_SDL_STATE_SET(RTDS_state_waitForTopology);
            break;
          /* Transition for state waitForHello - message * */
          default:
            RTDS_MSG_SAVE(RTDS_currentContext->currentMessage);
            break;
          } /* End of switch on message */
        break;
      /* Transitions for state waitForTopology */
      case RTDS_state_waitForTopology:
        switch(RTDS_currentContext->currentMessage->messageNumber)
          {
          /* Transition for state waitForTopology - message mSubmitTopology */
          case RTDS_message_mSubmitTopology:
            RTDS_MSG_RECEIVE_mSubmitTopology(        topology);
            transport_sender = blockMember->getBlockMember(TRANSPORT_SENDER);
            cluster = blockMember->getBlockMember(CLUSTER);
            app = blockMember->getBlockMember(APP);
            RTDS_MSG_SEND_mSubmitTopology_TO_ID(transport_sender,             topology);
            RTDS_SDL_STATE_SET(RTDS_state_initialised);
            break;
          /* Transition for state waitForTopology - message * */
          default:
            RTDS_MSG_SAVE(RTDS_currentContext->currentMessage);
            break;
          } /* End of switch on message */
        break;
      /* Transitions for state initialised */
      case RTDS_state_initialised:
        switch(RTDS_currentContext->currentMessage->messageNumber)
          {
          /* Transition for state initialised - message mUnicast */
          case RTDS_message_mUnicast:
            RTDS_MSG_RECEIVE_mUnicast(        senderID,         messageType,         payload);
            if ( messageType == RTDS_message_mPing )
              {
              RTDS_MSG_SEND_mPing_TO_ID(app,               senderID,               payload.ping);
              break;
              }
            else if ( messageType == RTDS_message_mPong )
              {
              RTDS_MSG_SEND_mPong_TO_ID(app,               senderID,               payload.pong);
              break;
              }
            else if ( messageType == RTDS_message_mRecruit )
              {
              RTDS_MSG_SEND_mRecruit_TO_ID(cluster,               ch);
              break;
              }
            else if ( messageType == RTDS_message_mRecruitResp )
              {
              RTDS_MSG_SEND_mRecruitResp_TO_ID(cluster,               ch,               senderID);
              break;
              }
            else
              {
              break;
              }
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
