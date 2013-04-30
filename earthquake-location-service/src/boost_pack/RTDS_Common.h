/***************************************************************************//**
 * @file RTDS_Common.h
 * @author Dorian Weber
 * @date 16.11.2011
 * @brief This file exists, because RTDS defines such a file under ccg/Common/
 * which breaks our framework here. Since that directory is included after this
 * one, we can shadow its PragmaDev version.
 ******************************************************************************/

#ifndef RTDS_COMMON_H_INCLUDED
#define RTDS_COMMON_H_INCLUDED

namespace RTDS
{
	class SDLProcess;
	class SDLTimer;
}

#include "RTDS_MSGQUEUE.hpp"

typedef RTDS::SDLProcess             RTDS_GlobalProcessInfo;
typedef RTDS::SDLProcess*            RTDS_RtosTaskId;
typedef RTDS::SDLTimer*              RTDS_TimerState;
typedef RTDS::MessageQueue::qWriter* RTDS_RtosQueueId;

typedef RTDS_RtosQueueId             RTDS_QueueId;
typedef RTDS_RtosQueueId             RTDS_PID;


#endif	/* RTDS_COMMON_H_INCLUDED */
