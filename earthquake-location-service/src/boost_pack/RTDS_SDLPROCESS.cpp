
#include "RTDS_SDLPROCESS.hpp"
#include "RTDS_SDLTIMER.hpp"

#include <string>
#include <list>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

namespace RTDS
{
	boost::asio::io_service SDLProcess::ioService;
	
	
	SDLTimer&
	SDLProcess::getTimerByID(int id)
	{
		SDLTimer* newTimer;
		
		if (timer.size() <= id)
		{
			timer.resize(id+1);
			goto create_new_timer;
		}
		
		if (!(newTimer = timer[id]))
		{
		create_new_timer:
			newTimer = timer[id] =
				new SDLTimer(*this, id);
		}
		
		return *newTimer;
	}
	
	unsigned long long
	SDLProcess::getCurrentTime()
	{
		unsigned long long currentMilliSec;
		struct timeval cur;
		
		gettimeofday(&cur, NULL);
		
		currentMilliSec = ((cur.tv_sec) * 1000ULL);
		currentMilliSec += cur.tv_usec / 1000ULL;
		
		return currentMilliSec;
	}
	
	void
	SDLProcess::activate()
	{
	    isRunning = new boost::asio::io_service::work(ioService);
	    boost::thread thread(boost::bind(&SDLProcess::main, this));
	    boost::thread _workThread_t(boost::bind(&boost::asio::io_service::run, &ioService));
	}
	
}
