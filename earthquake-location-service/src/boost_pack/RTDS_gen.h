/* Project: /home/seismo-user/bachelor-projekt/rtds-network-vorlage/network.rdp */
/* Diagram: /home/seismo-user/bachelor-projekt/rtds-network-vorlage/network.rdd */

#include "RTDS_MACRO.h"


/* DEFINES FOR STATES */
#define RTDS_state_waitForHello 1
#define RTDS_state_initialised 2
#define RTDS_state_waitForInit 3
#define RTDS_state_waitForId 4
#define RTDS_state_waitForTopology 5
#define RTDS_state_initializationPhase 6
#define RTDS_state_idleLoop 7
#define RTDS_state_RTDS_Idle 8

/* DEFINES FOR SIGNALS AND TIMERS */
#define RTDS_message_mSubmitTopology 1
#define RTDS_message_mUnicast 2
#define RTDS_message_mAbdicate 3
#define RTDS_message_mPong 4
#define RTDS_message_waitTimer 5
#define RTDS_message_mNodeHello 6
#define RTDS_message_mHello 7
#define RTDS_message_mBroadcast 8
#define RTDS_message_mPollResp 9
#define RTDS_message_mPing 10
#define RTDS_message_mPoll 11
#define RTDS_message_mPromote 12
#define RTDS_message_mGetSelfId 13
#define RTDS_message_mRecruit 14
#define RTDS_message_mSetSelfId 15
#define RTDS_message_mRecruitResp 16

/* DEFINES FOR SEMAPHORES */

/* DEFINES FOR PROCESSES */
#define RTDS_process_Creator 1
#define RTDS_process_Admin 2
#define RTDS_process_pCluster 3
#define RTDS_process_pApp 4
#define RTDS_process_pTransportReceiver 5
#define RTDS_process_pTransportSender 6
#define RTDS_process_RTDS_Env 7

/* PROCESS PROTOTYPES */
#include "Creator.hpp"
#include "Admin.hpp"
#include "pCluster.hpp"
#include "pApp.hpp"
#include "pTransportReceiver.hpp"
#include "pTransportSender.hpp"




