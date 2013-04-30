/***************************************************************************//**
 * @file RTDS_LOGGER.h
 * @author Toralf Niebuhr, Dorian Weber
 * @brief Defines macros that implement the logger interface.
 *
 * This file is in `RTDS\ccg`, it is identical for `boost` and `odemx`.
 ******************************************************************************/

#ifndef RTDS_LOGGER_H_INCLUDED
#define RTDS_LOGGER_H_INCLUDED

namespace RTDS {

struct MsgHeader;

/**@brief Virtual interface class to inherit real world loggers from.
 */
class Logger {
public:
    typedef void const * ID;

    virtual void logSetTimer(ID process, int timer, const char* timerName,
	    long long currentTime, int duration) {
    }

    virtual void logResetTimer(ID process, int timer,
	    const char* timerName, long long currentTime) {
    }
		
    virtual void logFireTimer(ID process, int timer, long long currentTime) {
    }

    virtual void logSend(ID sender, ID destination, long long currentTime,
	    const char* messageType, const MsgHeader* messageContent, int sequenceNumber) {
    }

    virtual void logReceive(ID sender, ID receiver, int sequenceNumber,
	    long long currentTime) {
    }

    virtual void logStateChange(ID process, const char* newState,
	    long long currentTime) {
    }

    virtual void logProcessCreation(ID process, const char* processName, ID context) {
    }
};

/** default logger */
extern Logger emptyLogger;

}

/* Macros used in order to (optionally) speed up execution of the generated
   program, if logging is not used at all. */

#ifdef NOLOGGING

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
	    MESSAGE_PTR->SEQUENCE = ++SEQUENCE; \
	    logger.logSend(SRC_ID, DEST_ID, CURRENT_TIME, MESSAGE_TYPE, \
		    MESSAGE_PTR, SEQUENCE); \
	} while (0)

#define RTDS_LOG_MESSAGE_RECEIVE(SRC_ID, DEST_ID, SEQUENCE, CURRENT_TIME) \
	if (SEQUENCE) \
	{\
	    logger.logReceive(SRC_ID, DEST_ID, SEQUENCE, CURRENT_TIME); \
	}\
	else \
	{\
	    logger.logFireTimer(DEST_ID, currentMessage->messageNumber, CURRENT_TIME);\
	}

/* ***************************************************** FINITE STATE MACHINE */

#define RTDS_LOG_STATE_CHANGE(PID, NEXT_STATE, CURRENT_TIME) \
	logger.logStateChange(PID, NEXT_STATE, CURRENT_TIME)

#define RTDS_LOG_PROCESS_CREATION(PID, PROCESS_NAME, CONTEXT_ID) \
	logger.logProcessCreation(PID, PROCESS_NAME, CONTEXT_ID)

#endif // NOLOGGING

#endif // RTDS_LOGGER_H_INCLUDED
