#ifndef _RTDS_MESSAGES_H_
#define _RTDS_MESSAGES_H_

#include "RTDS_CommonTypes.h"



/* DATA TYPES FOR MESSAGES */
#ifndef RTDS_mSubmitTopology_DATA_DEFINED
typedef struct RTDS_mSubmitTopology_data
{
	NetworkTopologyPtr	param1;
} RTDS_mSubmitTopology_data;
#define RTDS_mSubmitTopology_DATA_DEFINED
#endif

#ifndef RTDS_mSetSelfId_DATA_DEFINED
typedef struct RTDS_mSetSelfId_data
{
	ID	param1;
} RTDS_mSetSelfId_data;
#define RTDS_mSetSelfId_DATA_DEFINED
#endif

#ifndef RTDS_mUnicast_DATA_DEFINED
typedef struct RTDS_mUnicast_data
{
	ID	param1;
	int	param2;
	payload_t	param3;
} RTDS_mUnicast_data;
#define RTDS_mUnicast_DATA_DEFINED
#endif

#ifndef RTDS_mBroadcast_DATA_DEFINED
typedef struct RTDS_mBroadcast_data
{
	ID	param1;
	int	param2;
	payload_t	param3;
} RTDS_mBroadcast_data;
#define RTDS_mBroadcast_DATA_DEFINED
#endif

#ifndef RTDS_mPong_DATA_DEFINED
typedef struct RTDS_mPong_data
{
	ID	param1;
	pong_t	param2;
} RTDS_mPong_data;
#define RTDS_mPong_DATA_DEFINED
#endif

#ifndef RTDS_mNodeHello_DATA_DEFINED
typedef struct RTDS_mNodeHello_data
{
	RTDS_QueueId	param1;
	RTDS_QueueId	param2;
} RTDS_mNodeHello_data;
#define RTDS_mNodeHello_DATA_DEFINED
#endif

#ifndef RTDS_mRecruit_DATA_DEFINED
typedef struct RTDS_mRecruit_data
{
	ID	param1;
} RTDS_mRecruit_data;
#define RTDS_mRecruit_DATA_DEFINED
#endif

#ifndef RTDS_mHello_DATA_DEFINED
typedef struct RTDS_mHello_data
{
	BlockMemberPtr	param1;
} RTDS_mHello_data;
#define RTDS_mHello_DATA_DEFINED
#endif

#ifndef RTDS_mPoll_DATA_DEFINED
typedef struct RTDS_mPoll_data
{
	ID	param1;
	ID	param2;
} RTDS_mPoll_data;
#define RTDS_mPoll_DATA_DEFINED
#endif

#ifndef RTDS_mPing_DATA_DEFINED
typedef struct RTDS_mPing_data
{
	ID	param1;
	ping_t	param2;
} RTDS_mPing_data;
#define RTDS_mPing_DATA_DEFINED
#endif

#ifndef RTDS_mRecruitResp_DATA_DEFINED
typedef struct RTDS_mRecruitResp_data
{
	ID	param1;
	ID	param2;
} RTDS_mRecruitResp_data;
#define RTDS_mRecruitResp_DATA_DEFINED
#endif

/* MACRO FOR DECLARATIONS FOR MESSAGE SEND/RECEIVE */

#ifndef RTDS_MSG_DATA_DECL
#define RTDS_MSG_DATA_DECL unsigned char * RTDS_msgData;
#endif  /* RTDS_MSG_DATA_DECL defined */

/* MACRO FOR RECEPTION OF MESSAGE mSubmitTopology */

#ifndef RTDS_MSG_RECEIVE_mSubmitTopology
#define RTDS_MSG_RECEIVE_mSubmitTopology(RTDS_PARAM1) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		RTDS_PARAM1 = ((RTDS_mSubmitTopology_data*)(RTDS_currentContext->currentMessage->pData))->param1; \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mSubmitTopology defined */

/* MACRO FOR SENDING MESSAGE mSubmitTopology TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mSubmitTopology_TO_NAME
#define RTDS_MSG_SEND_mSubmitTopology_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mSubmitTopology_data(); \
	((RTDS_mSubmitTopology_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mSubmitTopology, sizeof(RTDS_mSubmitTopology_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mSubmitTopology_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mSubmitTopology TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mSubmitTopology_TO_ID
#define RTDS_MSG_SEND_mSubmitTopology_TO_ID(RECEIVER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mSubmitTopology_data(); \
	((RTDS_mSubmitTopology_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mSubmitTopology, sizeof(RTDS_mSubmitTopology_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mSubmitTopology_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mSubmitTopology TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mSubmitTopology_TO_ENV
#define RTDS_MSG_SEND_mSubmitTopology_TO_ENV(RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mSubmitTopology_data(); \
	((RTDS_mSubmitTopology_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mSubmitTopology, sizeof(RTDS_mSubmitTopology_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mSubmitTopology_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mSubmitTopology_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mSubmitTopology_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mSubmitTopology_data(); \
	((RTDS_mSubmitTopology_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	MACRO_NAME(RTDS_message_mSubmitTopology, sizeof(RTDS_mSubmitTopology_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mSubmitTopology_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mPing */

#ifndef RTDS_MSG_RECEIVE_mPing
#define RTDS_MSG_RECEIVE_mPing(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		(RTDS_PARAM1) = (((RTDS_mPing_data*)(RTDS_currentContext->currentMessage->pData))->param1); \
		(RTDS_PARAM2) = (((RTDS_mPing_data*)(RTDS_currentContext->currentMessage->pData))->param2); \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mPing defined */

/* MACRO FOR SENDING MESSAGE mPing TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mPing_TO_NAME
#define RTDS_MSG_SEND_mPing_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPing_data(); \
	(((RTDS_mPing_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPing_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mPing, sizeof(RTDS_mPing_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mPing_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mPing TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mPing_TO_ID
#define RTDS_MSG_SEND_mPing_TO_ID(RECEIVER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPing_data(); \
	(((RTDS_mPing_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPing_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mPing, sizeof(RTDS_mPing_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mPing_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mPing TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mPing_TO_ENV
#define RTDS_MSG_SEND_mPing_TO_ENV(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPing_data(); \
	(((RTDS_mPing_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPing_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mPing, sizeof(RTDS_mPing_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mPing_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mPing_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mPing_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPing_data(); \
	(((RTDS_mPing_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPing_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	MACRO_NAME(RTDS_message_mPing, sizeof(RTDS_mPing_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mPing_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mUnicast */

#ifndef RTDS_MSG_RECEIVE_mUnicast
#define RTDS_MSG_RECEIVE_mUnicast(RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		(RTDS_PARAM1) = (((RTDS_mUnicast_data*)(RTDS_currentContext->currentMessage->pData))->param1); \
		RTDS_PARAM2 = ((RTDS_mUnicast_data*)(RTDS_currentContext->currentMessage->pData))->param2; \
		(RTDS_PARAM3) = (((RTDS_mUnicast_data*)(RTDS_currentContext->currentMessage->pData))->param3); \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mUnicast defined */

/* MACRO FOR SENDING MESSAGE mUnicast TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mUnicast_TO_NAME
#define RTDS_MSG_SEND_mUnicast_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mUnicast_data(); \
	(((RTDS_mUnicast_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	((RTDS_mUnicast_data*)RTDS_msgData)->param2 = RTDS_PARAM2; \
	(((RTDS_mUnicast_data*)RTDS_msgData)->param3) = (RTDS_PARAM3); \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mUnicast, sizeof(RTDS_mUnicast_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mUnicast_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mUnicast TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mUnicast_TO_ID
#define RTDS_MSG_SEND_mUnicast_TO_ID(RECEIVER, RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mUnicast_data(); \
	(((RTDS_mUnicast_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	((RTDS_mUnicast_data*)RTDS_msgData)->param2 = RTDS_PARAM2; \
	(((RTDS_mUnicast_data*)RTDS_msgData)->param3) = (RTDS_PARAM3); \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mUnicast, sizeof(RTDS_mUnicast_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mUnicast_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mUnicast TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mUnicast_TO_ENV
#define RTDS_MSG_SEND_mUnicast_TO_ENV(RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mUnicast_data(); \
	(((RTDS_mUnicast_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	((RTDS_mUnicast_data*)RTDS_msgData)->param2 = RTDS_PARAM2; \
	(((RTDS_mUnicast_data*)RTDS_msgData)->param3) = (RTDS_PARAM3); \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mUnicast, sizeof(RTDS_mUnicast_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mUnicast_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mUnicast_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mUnicast_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mUnicast_data(); \
	(((RTDS_mUnicast_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	((RTDS_mUnicast_data*)RTDS_msgData)->param2 = RTDS_PARAM2; \
	(((RTDS_mUnicast_data*)RTDS_msgData)->param3) = (RTDS_PARAM3); \
	MACRO_NAME(RTDS_message_mUnicast, sizeof(RTDS_mUnicast_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mUnicast_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mPong */

#ifndef RTDS_MSG_RECEIVE_mPong
#define RTDS_MSG_RECEIVE_mPong(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		(RTDS_PARAM1) = (((RTDS_mPong_data*)(RTDS_currentContext->currentMessage->pData))->param1); \
		(RTDS_PARAM2) = (((RTDS_mPong_data*)(RTDS_currentContext->currentMessage->pData))->param2); \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mPong defined */

/* MACRO FOR SENDING MESSAGE mPong TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mPong_TO_NAME
#define RTDS_MSG_SEND_mPong_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPong_data(); \
	(((RTDS_mPong_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPong_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mPong, sizeof(RTDS_mPong_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mPong_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mPong TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mPong_TO_ID
#define RTDS_MSG_SEND_mPong_TO_ID(RECEIVER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPong_data(); \
	(((RTDS_mPong_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPong_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mPong, sizeof(RTDS_mPong_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mPong_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mPong TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mPong_TO_ENV
#define RTDS_MSG_SEND_mPong_TO_ENV(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPong_data(); \
	(((RTDS_mPong_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPong_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mPong, sizeof(RTDS_mPong_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mPong_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mPong_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mPong_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPong_data(); \
	(((RTDS_mPong_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPong_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	MACRO_NAME(RTDS_message_mPong, sizeof(RTDS_mPong_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mPong_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mNodeHello */

#ifndef RTDS_MSG_RECEIVE_mNodeHello
#define RTDS_MSG_RECEIVE_mNodeHello(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		(RTDS_PARAM1) = (((RTDS_mNodeHello_data*)(RTDS_currentContext->currentMessage->pData))->param1); \
		(RTDS_PARAM2) = (((RTDS_mNodeHello_data*)(RTDS_currentContext->currentMessage->pData))->param2); \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mNodeHello defined */

/* MACRO FOR SENDING MESSAGE mNodeHello TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mNodeHello_TO_NAME
#define RTDS_MSG_SEND_mNodeHello_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mNodeHello_data(); \
	(((RTDS_mNodeHello_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mNodeHello_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mNodeHello, sizeof(RTDS_mNodeHello_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mNodeHello_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mNodeHello TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mNodeHello_TO_ID
#define RTDS_MSG_SEND_mNodeHello_TO_ID(RECEIVER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mNodeHello_data(); \
	(((RTDS_mNodeHello_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mNodeHello_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mNodeHello, sizeof(RTDS_mNodeHello_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mNodeHello_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mNodeHello TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mNodeHello_TO_ENV
#define RTDS_MSG_SEND_mNodeHello_TO_ENV(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mNodeHello_data(); \
	(((RTDS_mNodeHello_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mNodeHello_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mNodeHello, sizeof(RTDS_mNodeHello_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mNodeHello_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mNodeHello_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mNodeHello_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mNodeHello_data(); \
	(((RTDS_mNodeHello_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mNodeHello_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	MACRO_NAME(RTDS_message_mNodeHello, sizeof(RTDS_mNodeHello_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mNodeHello_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mHello */

#ifndef RTDS_MSG_RECEIVE_mHello
#define RTDS_MSG_RECEIVE_mHello(RTDS_PARAM1) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		RTDS_PARAM1 = ((RTDS_mHello_data*)(RTDS_currentContext->currentMessage->pData))->param1; \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mHello defined */

/* MACRO FOR SENDING MESSAGE mHello TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mHello_TO_NAME
#define RTDS_MSG_SEND_mHello_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mHello_data(); \
	((RTDS_mHello_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mHello, sizeof(RTDS_mHello_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mHello_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mHello TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mHello_TO_ID
#define RTDS_MSG_SEND_mHello_TO_ID(RECEIVER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mHello_data(); \
	((RTDS_mHello_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mHello, sizeof(RTDS_mHello_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mHello_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mHello TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mHello_TO_ENV
#define RTDS_MSG_SEND_mHello_TO_ENV(RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mHello_data(); \
	((RTDS_mHello_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mHello, sizeof(RTDS_mHello_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mHello_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mHello_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mHello_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mHello_data(); \
	((RTDS_mHello_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	MACRO_NAME(RTDS_message_mHello, sizeof(RTDS_mHello_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mHello_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mBroadcast */

#ifndef RTDS_MSG_RECEIVE_mBroadcast
#define RTDS_MSG_RECEIVE_mBroadcast(RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		(RTDS_PARAM1) = (((RTDS_mBroadcast_data*)(RTDS_currentContext->currentMessage->pData))->param1); \
		RTDS_PARAM2 = ((RTDS_mBroadcast_data*)(RTDS_currentContext->currentMessage->pData))->param2; \
		(RTDS_PARAM3) = (((RTDS_mBroadcast_data*)(RTDS_currentContext->currentMessage->pData))->param3); \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mBroadcast defined */

/* MACRO FOR SENDING MESSAGE mBroadcast TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mBroadcast_TO_NAME
#define RTDS_MSG_SEND_mBroadcast_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mBroadcast_data(); \
	(((RTDS_mBroadcast_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	((RTDS_mBroadcast_data*)RTDS_msgData)->param2 = RTDS_PARAM2; \
	(((RTDS_mBroadcast_data*)RTDS_msgData)->param3) = (RTDS_PARAM3); \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mBroadcast, sizeof(RTDS_mBroadcast_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mBroadcast_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mBroadcast TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mBroadcast_TO_ID
#define RTDS_MSG_SEND_mBroadcast_TO_ID(RECEIVER, RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mBroadcast_data(); \
	(((RTDS_mBroadcast_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	((RTDS_mBroadcast_data*)RTDS_msgData)->param2 = RTDS_PARAM2; \
	(((RTDS_mBroadcast_data*)RTDS_msgData)->param3) = (RTDS_PARAM3); \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mBroadcast, sizeof(RTDS_mBroadcast_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mBroadcast_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mBroadcast TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mBroadcast_TO_ENV
#define RTDS_MSG_SEND_mBroadcast_TO_ENV(RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mBroadcast_data(); \
	(((RTDS_mBroadcast_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	((RTDS_mBroadcast_data*)RTDS_msgData)->param2 = RTDS_PARAM2; \
	(((RTDS_mBroadcast_data*)RTDS_msgData)->param3) = (RTDS_PARAM3); \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mBroadcast, sizeof(RTDS_mBroadcast_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mBroadcast_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mBroadcast_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mBroadcast_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1, RTDS_PARAM2, RTDS_PARAM3) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mBroadcast_data(); \
	(((RTDS_mBroadcast_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	((RTDS_mBroadcast_data*)RTDS_msgData)->param2 = RTDS_PARAM2; \
	(((RTDS_mBroadcast_data*)RTDS_msgData)->param3) = (RTDS_PARAM3); \
	MACRO_NAME(RTDS_message_mBroadcast, sizeof(RTDS_mBroadcast_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mBroadcast_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mRecruit */

#ifndef RTDS_MSG_RECEIVE_mRecruit
#define RTDS_MSG_RECEIVE_mRecruit(RTDS_PARAM1) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		(RTDS_PARAM1) = (((RTDS_mRecruit_data*)(RTDS_currentContext->currentMessage->pData))->param1); \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mRecruit defined */

/* MACRO FOR SENDING MESSAGE mRecruit TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mRecruit_TO_NAME
#define RTDS_MSG_SEND_mRecruit_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mRecruit_data(); \
	(((RTDS_mRecruit_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mRecruit, sizeof(RTDS_mRecruit_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mRecruit_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mRecruit TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mRecruit_TO_ID
#define RTDS_MSG_SEND_mRecruit_TO_ID(RECEIVER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mRecruit_data(); \
	(((RTDS_mRecruit_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mRecruit, sizeof(RTDS_mRecruit_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mRecruit_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mRecruit TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mRecruit_TO_ENV
#define RTDS_MSG_SEND_mRecruit_TO_ENV(RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mRecruit_data(); \
	(((RTDS_mRecruit_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mRecruit, sizeof(RTDS_mRecruit_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mRecruit_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mRecruit_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mRecruit_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mRecruit_data(); \
	(((RTDS_mRecruit_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	MACRO_NAME(RTDS_message_mRecruit, sizeof(RTDS_mRecruit_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mRecruit_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mRecruitResp */

#ifndef RTDS_MSG_RECEIVE_mRecruitResp
#define RTDS_MSG_RECEIVE_mRecruitResp(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		(RTDS_PARAM1) = (((RTDS_mRecruitResp_data*)(RTDS_currentContext->currentMessage->pData))->param1); \
		(RTDS_PARAM2) = (((RTDS_mRecruitResp_data*)(RTDS_currentContext->currentMessage->pData))->param2); \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mRecruitResp defined */

/* MACRO FOR SENDING MESSAGE mRecruitResp TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mRecruitResp_TO_NAME
#define RTDS_MSG_SEND_mRecruitResp_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mRecruitResp_data(); \
	(((RTDS_mRecruitResp_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mRecruitResp_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mRecruitResp, sizeof(RTDS_mRecruitResp_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mRecruitResp_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mRecruitResp TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mRecruitResp_TO_ID
#define RTDS_MSG_SEND_mRecruitResp_TO_ID(RECEIVER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mRecruitResp_data(); \
	(((RTDS_mRecruitResp_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mRecruitResp_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mRecruitResp, sizeof(RTDS_mRecruitResp_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mRecruitResp_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mRecruitResp TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mRecruitResp_TO_ENV
#define RTDS_MSG_SEND_mRecruitResp_TO_ENV(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mRecruitResp_data(); \
	(((RTDS_mRecruitResp_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mRecruitResp_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mRecruitResp, sizeof(RTDS_mRecruitResp_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mRecruitResp_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mRecruitResp_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mRecruitResp_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mRecruitResp_data(); \
	(((RTDS_mRecruitResp_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mRecruitResp_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	MACRO_NAME(RTDS_message_mRecruitResp, sizeof(RTDS_mRecruitResp_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mRecruitResp_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mSetSelfId */

#ifndef RTDS_MSG_RECEIVE_mSetSelfId
#define RTDS_MSG_RECEIVE_mSetSelfId(RTDS_PARAM1) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		(RTDS_PARAM1) = (((RTDS_mSetSelfId_data*)(RTDS_currentContext->currentMessage->pData))->param1); \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mSetSelfId defined */

/* MACRO FOR SENDING MESSAGE mSetSelfId TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mSetSelfId_TO_NAME
#define RTDS_MSG_SEND_mSetSelfId_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mSetSelfId_data(); \
	(((RTDS_mSetSelfId_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mSetSelfId, sizeof(RTDS_mSetSelfId_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mSetSelfId_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mSetSelfId TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mSetSelfId_TO_ID
#define RTDS_MSG_SEND_mSetSelfId_TO_ID(RECEIVER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mSetSelfId_data(); \
	(((RTDS_mSetSelfId_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mSetSelfId, sizeof(RTDS_mSetSelfId_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mSetSelfId_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mSetSelfId TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mSetSelfId_TO_ENV
#define RTDS_MSG_SEND_mSetSelfId_TO_ENV(RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mSetSelfId_data(); \
	(((RTDS_mSetSelfId_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mSetSelfId, sizeof(RTDS_mSetSelfId_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mSetSelfId_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mSetSelfId_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mSetSelfId_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mSetSelfId_data(); \
	(((RTDS_mSetSelfId_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	MACRO_NAME(RTDS_message_mSetSelfId, sizeof(RTDS_mSetSelfId_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mSetSelfId_TO_ENV defined */

/* MACRO FOR RECEPTION OF MESSAGE mPoll */

#ifndef RTDS_MSG_RECEIVE_mPoll
#define RTDS_MSG_RECEIVE_mPoll(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		(RTDS_PARAM1) = (((RTDS_mPoll_data*)(RTDS_currentContext->currentMessage->pData))->param1); \
		(RTDS_PARAM2) = (((RTDS_mPoll_data*)(RTDS_currentContext->currentMessage->pData))->param2); \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_mPoll defined */

/* MACRO FOR SENDING MESSAGE mPoll TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_mPoll_TO_NAME
#define RTDS_MSG_SEND_mPoll_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPoll_data(); \
	(((RTDS_mPoll_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPoll_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_mPoll, sizeof(RTDS_mPoll_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_mPoll_TO_NAME defined */

/* MACRO FOR SENDING MESSAGE mPoll TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_mPoll_TO_ID
#define RTDS_MSG_SEND_mPoll_TO_ID(RECEIVER, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPoll_data(); \
	(((RTDS_mPoll_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPoll_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_mPoll, sizeof(RTDS_mPoll_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_mPoll_TO_ID defined */

/* MACROS FOR SENDING MESSAGE mPoll TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_mPoll_TO_ENV
#define RTDS_MSG_SEND_mPoll_TO_ENV(RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPoll_data(); \
	(((RTDS_mPoll_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPoll_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_mPoll, sizeof(RTDS_mPoll_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mPoll_TO_ENV defined */

#ifndef RTDS_MSG_SEND_mPoll_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_mPoll_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1, RTDS_PARAM2) \
	{ \
	RTDS_msgData = (unsigned char *) new RTDS_mPoll_data(); \
	(((RTDS_mPoll_data*)RTDS_msgData)->param1) = (RTDS_PARAM1); \
	(((RTDS_mPoll_data*)RTDS_msgData)->param2) = (RTDS_PARAM2); \
	MACRO_NAME(RTDS_message_mPoll, sizeof(RTDS_mPoll_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_mPoll_TO_ENV defined */



#endif /* defined(_RTDS_MESSAGES_H_) */

