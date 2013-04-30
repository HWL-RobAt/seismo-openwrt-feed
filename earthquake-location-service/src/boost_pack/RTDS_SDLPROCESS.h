
#ifndef RTDS_SDLPROCESS_H_INCLUDED
#define RTDS_SDLPROCESS_H_INCLUDED

namespace RTDS {
  class SDLProcess;
}

#include "RTDS_SDLBLOCK.h"
#include "RTDS_MSGQUEUE.h"
#include "RTDS_SDLTIMER.h"
#include "RTDS_LOGGER.h"
#include <boost/asio.hpp>
#include <list>
#include <sys/time.h>
#include <memory>

namespace RTDS {

/**@brief Base class for all RTDS generated processes.
 */
class SDLProcess {
protected:
    friend struct SDLBlock;
    friend class SDLTimer;
    
    std::list<SDLTimer*> timer;
    SDLBlock* cover;
    MessageQueue::qWriter *offspring,
               *parent;
    MessageQueue msgQueue, saveQueue;
    void* RTDS_msgData;
    boost::asio::io_service::work* isRunning;
    Logger& logger;
    int sequenceNumber;
    
    /**@brief Sends a message from this process to another one.
     */
    void msgQSend(MessageQueue::qWriter* receiver, MsgHeader* message);
    
    /**@brief Grabs the next message from the message queue or goes to sleep
     *        while there isn't any.
     */
    MsgHeader* msgQRead();
    
    /**@brief Initializes a process that has been created by another one.
     */
    static void initProcess(SDLProcess* process, SDLBlock* cover, MessageQueue::qWriter* parent,
                            MessageQueue::qWriter*& offspring);
    
    /**@brief Returns a reference to a timer that sends messages from the passed
     *        ID.
     */
    /*static time_t getCurrentTime()
    {
       time_t rawtime;
       time(&rawtime);
       return rawtime;
    }*/
	
public:
    static boost::asio::io_service ioService;
    
    int sdlState,
        RTDS_sdlStatePrev;
    SDLProcess* RTDS_currentContext;
    
    MsgHeader* currentMessage;
    
    /**@brief Constructor for an SDL process.
     */
    SDLProcess(Logger& logger);
    
    /**@brief Virtual destructor.
     */
    virtual ~SDLProcess() {}
    
    /**@brief Activates the main function of this process.
     */
    void activate();
    
    /**@brief Main function.
     */
    virtual int main() = 0;
    
    /**@brief Selects the timer from the timer list given its id
     */
    SDLTimer& getTimerByID(int id, const char* ignoredTimerName);

    /** Determine current real time in milliseconds.
     *  @return the number of milliseconds since the epoch
     */
    long long getCurrentTime() {
	struct timeval cur;
	gettimeofday(&cur, NULL);

	long long currentMilliSec;
	currentMilliSec = (long long)(cur.tv_sec) * 1000;
	currentMilliSec += cur.tv_usec / 1000;
	return currentMilliSec;
    }
};

}

/* needed for RTDS to pass the correct structure to procedures */
typedef RTDS::SDLProcess RTDS_GlobalProcessInfo;

#endif
