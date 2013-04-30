/** @file
 *  Generated file, find templates in SX folders
 */

#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include "RTDS_SDLTIMER.hpp"

#include "Network.hpp"
#include "pTransportSender.hpp"
#include "RTDS_messages.h"
#include "RTDS_gen.h"

#define RTDS_PROCESS_NUMBER RTDS_process_pTransportSender
#define RTDS_PROCESS_NAME pTransportSender

/*
** PROCESS pTransportSender:
** -------------------------
*/



using Network::pTransportSender;

int
pTransportSender::main()
{
  short RTDS_transitionExecuted;
  int RTDS_savedSdlState = 0;

  BlockMember* blockMember;
  NetworkTopologyPtr topology;
  payload_t payload;
  ID receiverID, cHead, tmp;
  ID selfId;
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
      /* Transitions for state initialised */
      case RTDS_state_initialised:
        switch(RTDS_currentContext->currentMessage->messageNumber)
          {
          /* Transition for state initialised - message mRecruitResp */
          case RTDS_message_mRecruitResp:
            RTDS_MSG_RECEIVE_mRecruitResp(        cHead,         tmp);
            sendMessage(RTDS_currentContext, topology, UNICAST_ID, RTDS_message_mRecruitResp, payload); RTDS_SDL_STATE_SET(RTDS_sdlStatePrev);
            break;
          /* Transition for state initialised - message mGetSelfId */
          case RTDS_message_mGetSelfId:
            RTDS_MSG_SEND_mSetSelfId_TO_ID(SENDER,             selfId);
            break;
          /* Transition for state initialised - message mRecruit */
          case RTDS_message_mRecruit:
            RTDS_MSG_RECEIVE_mRecruit(            tmp);
            sendMessage(RTDS_currentContext, topology, BROADCAST_ID, RTDS_message_mRecruit, payload); RTDS_SDL_STATE_SET(RTDS_sdlStatePrev);
            break;
          /* Transition for state initialised - message mPong */
          case RTDS_message_mPong:
            RTDS_MSG_RECEIVE_mPong(            receiverID,             payload.pong);
            sendMessage(RTDS_currentContext, topology, receiverID, RTDS_message_mPong, payload); RTDS_SDL_STATE_SET(RTDS_sdlStatePrev);
            break;
          /* Transition for state initialised - message mPing */
          case RTDS_message_mPing:
            RTDS_MSG_RECEIVE_mPing(            receiverID,             payload.ping);
            sendMessage(RTDS_currentContext, topology, receiverID, RTDS_message_mPing, payload); RTDS_SDL_STATE_SET(RTDS_sdlStatePrev);
            break;
          default:
            RTDS_transitionExecuted = 0;
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
            selfId = topology->getMyId();
            RTDS_SDL_STATE_SET(RTDS_state_initialised);
            break;
          /* Transition for state waitForTopology - message * */
          default:
            RTDS_MSG_SAVE(RTDS_currentContext->currentMessage);
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
void
pTransportSender::sendMessage(RTDS_GlobalProcessInfo * RTDS_currentContext, NetworkTopologyPtr topology, ID receiverID, int type, payload_t payload)
{{
  short RTDS_transitionExecuted;
  int RTDS_savedSdlState = 0;

  std::list<ExternalRef> allNodes;
  std::list<ExternalRef>::iterator nodeIt;
  ExternalRef receiver;
  ID selfID = topology->getMyId();
  RTDS_MSG_DATA_DECL

  /* declare framework-side variables for the method */
  int RTDS_sdlStatePrev = sdlState;

  /* silence warnings; these variables are not usually used */
  RTDS_savedSdlState += 0;
  RTDS_sdlStatePrev += 0;
  RTDS_msgData = NULL;
  RTDS_msgData += 0;

  /* Initial transition */
  do	/* Dummy do/while(0) to be able to do 'break's */
    {
    if ( receiverID == BROADCAST_ID )
      {
      allNodes = topology->getAllConnectedReferences();
      nodeIt = allNodes.begin();
      }
    else if ( receiverID == LOCAL_BROADCAST_ID )
      {
      allNodes = topology->getAllNeighborReferences();
      nodeIt = allNodes.begin();
      }
    else
      {
      receiver = topology->getReceiverReference(receiverID);
      #ifdef ODEMX
      //setup the message
      RTDS_mUnicast_data* data = new RTDS_mUnicast_data();
      data->param1 = selfID;
      data->param2 = type;
      data->param3 = payload;

      RTDS::MsgHeader* msg = new RTDS::MsgHeader( RTDS_message_mUnicast, *msgQueue.writer, sizeof(*data), reinterpret_cast<unsigned char*>(data));
      msg->sequenceNumber = ++sequenceNumber;

      //send it
      NetworkStack* stack = ((blockClass_node*)cover)->networkStack;
      stack->inputData(new Message(stack,receiver,true,msg));

      #elif defined BOOST

      RTDS_mUnicast_data data;
      data.param1 = selfID;
      data.param2 = type;
      data.param3 = payload;

      //send it
      SX_DEBUG(">      Sending over wire mUnicast to <%s>\n", receiver.c_str());
      std::ostringstream archive_stream;
      boost::archive::binary_oarchive oa(archive_stream);
      oa << data;

      BoostNetwork::Connection<>* c;
      c = ((blockClass_node*)cover)->handler->getConnection(receiver);
      c->get_ostream() << archive_stream.str();
      c->commit();

      #else

      RTDS_MSG_SEND_mUnicast_TO_ID(receiver, selfID, type, payload);

      #endif
      RTDS_PROCEDURE_CLEAN_UP; return;
      }
    RTDS_label1:
    if ( !(nodeIt != allNodes.end()) )
      {
      RTDS_PROCEDURE_CLEAN_UP; return;
      }
    else if ( nodeIt != allNodes.end() )
      {
      receiver = *nodeIt;

      #ifdef ODEMX
      //setup the message
      RTDS_mUnicast_data* data = new RTDS_mUnicast_data();
      data->param1 = selfID;
      data->param2 = type;
      data->param3 = payload;

      RTDS::MsgHeader* msg = new RTDS::MsgHeader( RTDS_message_mUnicast, *msgQueue.writer, sizeof(*data), reinterpret_cast<unsigned char*>(data));
      msg->sequenceNumber = ++sequenceNumber;

      //send it
      NetworkStack* stack = ((blockClass_node*)cover)->networkStack;
      stack->inputData(new Message(stack,receiver,true,msg));

      #elif defined BOOST

      RTDS_mUnicast_data data;
      data.param1 = selfID;
      data.param2 = type;
      data.param3 = payload;

      //send it
      SX_DEBUG(">      Sending over wire mUnicast to <%s>\n", receiver.c_str());
      std::ostringstream archive_stream;
      boost::archive::binary_oarchive oa(archive_stream);
      oa << data;

      BoostNetwork::Connection<>* c;
      c = ((blockClass_node*)cover)->handler->getConnection(receiver);
      c->get_ostream() << archive_stream.str();
      c->commit();

      #else

      RTDS_MSG_SEND_mUnicast_TO_ID(receiver, selfID, type, payload);

      #endif
      nodeIt++;
      }
    goto RTDS_label1;
    } while (0);
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

}

