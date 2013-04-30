
#include "RTDS_SDLTIMER.hpp"

#include <boost/bind.hpp>

namespace RTDS
{
	
	void
	SDLTimer::eventAction(const boost::system::error_code& error)
	{
		if (!error)
		{
			RTDS::MsgHeader* msg = new RTDS::MsgHeader(
					msgID, rcv.getPort(), 0, 0);
			msg->sequenceNumber = 0;
			
			rcv.msgQSend(rcv.getPort(), msg);
		}
	}
	
	void SDLTimer::scheduleIn(unsigned long delay)
	{
		timer.expires_from_now(boost::posix_time::millisec(delay));
		timer.async_wait(bind(&SDLTimer::eventAction, this,
		                      boost::asio::placeholders::error));
	}
	
}
