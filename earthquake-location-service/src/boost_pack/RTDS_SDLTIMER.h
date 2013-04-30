
#ifndef RTDS_SDLTIMER_H_INCLUDED
#define RTDS_SDLTIMER_H_INCLUDED

namespace RTDS
{
  class SDLTimer;
}

#include "RTDS_SDLPROCESS.h"
#include <boost/asio.hpp>

namespace RTDS
{
  typedef boost::asio::basic_deadline_timer<boost::posix_time::ptime>
          deadline_timer;

  /**@brief Class that implements the SDL timer concept for RTDS.
   */
  class SDLTimer
  {
    SDLProcess& rcv;
    int msgID;
    deadline_timer timer;
    
  public:
    
    /**@brief Constructor.
     */
    SDLTimer(SDLProcess& receiver, int messageID);
    
    /**@brief Returns the message ID of the message this timer sends when triggered.
     */
    int getMessageID() const { return msgID; }
    
    /**@brief Removes the timer from its schedule.
     */
    void removeFromSchedule();
    
    /**@brief Schedules the timer in NOW + delay in ms.
     */
    void scheduleIn(long delay);
    
    void handler(const boost::system::error_code& error);
  };
}

#endif
