#ifndef RTDS_SDLPROCESS_H_INCLUDED
#define RTDS_SDLPROCESS_H_INCLUDED

#include <boost/asio.hpp>
#include <list>
#include <sys/time.h>
#include <memory>

#include "RTDS_MSGQUEUE.hpp"
#include "RTDS_LOGGER.hpp"

namespace RTDS
{
	/* forward declarations */
	struct SDLBlock;
	class SDLTimer;
	
	/**@brief Base class for all RTDS generated processes.
	 */
	class SDLProcess
	{
	protected:
		friend struct SDLBlock;
		
		std::vector<SDLTimer*> timer;
		SDLBlock* cover;
		MessageQueue::qWriter *offspring, *parent;
		MessageQueue msgQueue, saveQueue;
		int sequenceNumber;
		boost::asio::io_service::work* isRunning;
		
		/**@brief Sets the \p parent field to the creator process and
		 * returns the port to the given process.
		 * 
		 * @param[in] process  created process
		 * @param[in] parent   creator process
		 * 
		 * @return port of \p process
		 */
		static MessageQueue::qWriter*
		setParent(SDLProcess* process, MessageQueue::qWriter* parent);
		
		/**@brief Grabs the next message from the message queue or goes
		 * to sleep while there isn't any.
		 */
		MsgHeader* msgQRead();
		
		/**@brief Selects the timer from the timer list given its ID.
		 */
		SDLTimer& getTimerByID(int id);
		
	public:
		static boost::asio::io_service ioService;
		
		int sdlState;
		MsgHeader* currentMessage;
		Logger& logger;
		
		
		/**@brief Constructor for an SDL process.
		 */
		SDLProcess(Logger& logger);
		
		/**@brief Virtual destructor.
		 */
		virtual ~SDLProcess()
		{}
		
		
		/**@brief Returns the input port of this message queue.
		 */
		MessageQueue::qWriter& getPort();
		
		/**@brief Sends a message from this process to another one.
		 */
		void msgQSend(MessageQueue::qWriter& receiver,
			      MsgHeader* message);
		
		/**@brief Activates the main function of this process.
		 */
		void activate();
		
		/**@brief Main function.
		 */
		virtual int main() = 0;
		
		/**@brief Determine current real time in milliseconds.
		 * @return the number of milliseconds since the epoch
		 */
		static unsigned long long getCurrentTime();
	};
	
	
	/* ******************************************** INLINE IMPLEMENTATION */
	
	inline MessageQueue::qWriter*
	SDLProcess::setParent(SDLProcess* process,
	                      MessageQueue::qWriter* parent)
	{
		process->parent = parent;
		return process->msgQueue.writer;
	}
	
	
	inline
	SDLProcess::SDLProcess(Logger& _logger)
	:	cover(NULL),
		offspring(NULL),
		parent(NULL),
		sequenceNumber(0),
		sdlState(0),
		currentMessage(NULL),
		logger(_logger)
	{}
	
	inline void
	SDLProcess::msgQSend(MessageQueue::qWriter& receiver,
	                     MsgHeader* message)
	{
		receiver.put(message);
	}
	
	inline MsgHeader*
	SDLProcess::msgQRead()
	{
		return msgQueue.reader->get();
	}
	
	inline MessageQueue::qWriter&
	SDLProcess::getPort()
	{
		return *msgQueue.writer;
	}
	
}

#endif
