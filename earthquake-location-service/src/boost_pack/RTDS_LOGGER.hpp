/***************************************************************************//**
 * @file RTDS_LOGGER.h
 * @author Toralf Niebuhr, Dorian Weber
 * @brief Defines macros that implement the logger interface.
 *
 * This file is in 'RTDS/ccg', it is identical for `boost` and `odemx`.
 ******************************************************************************/

#ifndef RTDS_LOGGER_H_INCLUDED
#define RTDS_LOGGER_H_INCLUDED

#include "RTDS_Common.h"

namespace RTDS
{
	
	struct MsgHeader;
	
	/**@brief Virtual interface class to inherit real world loggers from.
	 */
	struct Logger
	{
		/**@brief Virtual destructor.
		 */
		virtual ~Logger() {}
		
		/**@brief Called whenever a timer is set.
		 * 
		 * @param[in] process      pid
		 * @param[in] timer        timer id
		 * @param[in] timerName    timer name
		 * @param[in] currentTime  current time
		 * @param[in] duration     set duration for the timer
		 */
		virtual void logSetTimer(RTDS_PID process, int timer,
		                         const char* timerName,
		                         unsigned long long currentTime,
		                         unsigned long long duration)
		{}
		
		/**@brief Called when a timer has been reset (without firing).
		 * 
		 * @param[in] process      pid
		 * @param[in] timer        timer id
		 * @param[in] timerName    timer name
		 * @param[in] currentTime  current time
		 */
		virtual void logResetTimer(RTDS_PID process, int timer,
		                           const char* timerName,
		                           unsigned long long currentTime)
		{}
		
		/**@brief Called whenever a timer fires (its duration expires).
		 * 
		 * @param[in] process      pid
		 * @param[in] timer        timer id
		 * @param[in] currentTime  current time
		 */
		virtual void logFireTimer(RTDS_PID process, int timer,
		                          unsigned long long currentTime)
		{}
		
		/**@brief Called when a message is send.
		 * 
		 * @param[in] sender          sender pid
		 * @param[in] destination     receiver pid
		 * @param[in] currentTime     current time index
		 * @param[in] messageType     name of the message
		 * @param[in] messageContent  wrapped content of the message
		 * @param[in] sequenceNumber  sequence number
		 */
		virtual void logSend(RTDS_PID sender, RTDS_PID destination,
		                     unsigned long long currentTime,
		                     const char* messageType,
		                     const MsgHeader* messageContent,
		                     int sequenceNumber)
		{}
		
		/**@brief Called whenever a message has been received.
		 * 
		 * @param[in] sender          process id of the sender
		 * @param[in] receiver        process id of the receiver
		 * @param[in] sequenceNumber  sequence number
		 * @param[in] currentTime     current time
		 */
		virtual void logReceive(RTDS_PID sender, RTDS_PID receiver,
		                        int sequenceNumber,
		                        unsigned long long currentTime)
		{}
		
		/**@brief Called in case of a state change.
		 * 
		 * @param[in] process      pid
		 * @param[in] newState     next state
		 * @param[in] currentTime  current time
		 */
		virtual void logStateChange(RTDS_PID process,
		                            const char* newState,
		                            unsigned long long currentTime)
		{}
		
		/**@brief Called during process initialization.
		 * 
		 * @param[in] process      pid of the created process
		 * @param[in] processName  process name
		 * @param[in] context      pid of the creator
		 */
		virtual void logProcessCreation(RTDS_PID process,
		                                const char* processName,
		                                RTDS_PID context)
		{}
	};
	
	/**@brief Default logger that does nothing. */
	extern Logger emptyLogger;
}

/* Macros used in order to (optionally) speed up execution of the generated
 * program, if logging is not used at all. */

#ifdef RTDS_NOLOG

#define RTDS_LOG_SET_TIMER(PID, TIMER_ID, TIMER_NAME, CURRENT_TIME, DURATION)
#define RTDS_LOG_RESET_TIMER(PID, TIMER_ID, TIMER_NAME, CURRENT_TIME)
#define RTDS_LOG_FIRE_TIMER(PID, TIMER_ID, CURRENT_TIME)
#define RTDS_LOG_MESSAGE_SEND(SRC_ID, DEST_ID, CURRENT_TIME, MESSAGE_TYPE, \
	MESSAGE_CONTENT, SEQUENCE)
#define RTDS_LOG_MESSAGE_RECEIVE(SRC_ID, DEST_ID, SEQUENCE, CURRENT_TIME)
#define RTDS_LOG_STATE_CHANGE(PID, NEXT_STATE, CURRENT_TIME)
#define RTDS_LOG_PROCESS_CREATION(PID, PROCESS_NAME, CONTEXT_ID)

#else

/* ******************************************************************** TIMER */

#define RTDS_LOG_SET_TIMER(PID, TIMER_ID, TIMER_NAME, CURRENT_TIME, DURATION) \
	logger.logSetTimer(PID, TIMER_ID, TIMER_NAME, CURRENT_TIME, DURATION)

#define RTDS_LOG_RESET_TIMER(PID, TIMER_ID, TIMER_NAME, CURRENT_TIME) \
	logger.logResetTimer(PID, TIMER_ID, TIMER_NAME, CURRENT_TIME)

#define RTDS_LOG_FIRE_TIMER(PID, TIMER_ID, CURRENT_TIME) \
	logger.logFireTimer(PID, TIMER_ID, CURRENT_TIME)


/* ****************************************************************** MESSAGE */

#define RTDS_LOG_MESSAGE_SEND(SRC_ID, DEST_ID, CURRENT_TIME, MESSAGE_TYPE, \
                              MESSAGE_PTR, SEQUENCE) \
	do { \
		MESSAGE_PTR->SEQUENCE = ++SEQUENCE;                         \
		logger.logSend(SRC_ID, DEST_ID, CURRENT_TIME, MESSAGE_TYPE, \
		               MESSAGE_PTR, SEQUENCE);                      \
	} while (0)

#define RTDS_LOG_MESSAGE_RECEIVE(SRC_ID, DEST_ID, SEQUENCE, CURRENT_TIME)   \
	do { \
		if (SEQUENCE) {                                             \
			logger.logReceive(SRC_ID, DEST_ID, SEQUENCE,        \
			                  CURRENT_TIME);                    \
		} else {                                                    \
			logger.logFireTimer(DEST_ID,                        \
			                    currentMessage->messageNumber,  \
					    CURRENT_TIME);                  \
		}                                                           \
	} while (0)


/* ***************************************************** FINITE STATE MACHINE */

#define RTDS_LOG_STATE_CHANGE(PID, NEXT_STATE, CURRENT_TIME) \
	logger.logStateChange(PID, NEXT_STATE, CURRENT_TIME)

#define RTDS_LOG_PROCESS_CREATION(PID, PROCESS_NAME, CONTEXT_ID) \
	logger.logProcessCreation(PID, PROCESS_NAME, CONTEXT_ID)


#endif	/* RTDS_NOLOG */
#endif	/* RTDS_LOGGER_H_INCLUDED */
