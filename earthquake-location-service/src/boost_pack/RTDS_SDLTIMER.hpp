#ifndef RTDS_SDLTIMER_H_INCLUDED
#define RTDS_SDLTIMER_H_INCLUDED

#include "RTDS_SDLPROCESS.hpp"

#include <boost/asio.hpp>

namespace RTDS
{
	
	/**@brief Class that implements the SDL timer concept for RTDS.
	 */
	class SDLTimer
	{
	protected:
		typedef boost::asio::basic_deadline_timer<boost::posix_time::ptime> timer_t;
		
		SDLProcess& rcv;
		int msgID;
		timer_t timer;
		
		void eventAction(const boost::system::error_code& error);
		
	public:
		
		/**@brief Initializing constructor.
		 */
		SDLTimer(SDLProcess& receiver, int messageID);
		
		/**@brief Returns the message ID of the message this timer
		 * sends when triggered.
		 */
		int getMessageID() const;
		
		/**@brief Removes the timer from its schedule.
		 */
		void removeFromSchedule();
		
		/**@brief Schedules the timer in NOW + delay in ms.
		 */
		void scheduleIn(unsigned long delay);
		
	};
	
	
	/* ******************************************** INLINE IMPLEMENTATION */
	
	inline
	SDLTimer::SDLTimer(SDLProcess& receiver, int messageID)
	:	rcv(receiver),
		msgID(messageID),
		timer(receiver.ioService)
	{}
	
	inline int
	SDLTimer::getMessageID() const
	{
		return msgID;
	}
	
	inline void
	SDLTimer::removeFromSchedule()
	{
		timer.cancel();
	}
	
}

#endif
