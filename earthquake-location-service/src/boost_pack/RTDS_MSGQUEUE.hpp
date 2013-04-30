#ifndef RTDS_MSGQUEUE_H_INCLUDED
#define RTDS_MSGQUEUE_H_INCLUDED

#include <list>

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

namespace RTDS
{
	/**@brief Represents a message queue for SDL processes.
	 */
	template <typename ElemType>
	class MessageQueueT
	{
	private:
		typedef std::list<ElemType> queue_t;
		typedef boost::mutex        mutex_t;
		typedef boost::condition    condition_t;
		
		queue_t queue;
		mutex_t mutex;
		condition_t cond_empty;
		
	public:
		
		/**@brief Allows thread safe queue read access.
		 */
		class qReader
		{
		private:
			queue_t& queue;
			mutex_t& mutex;
			condition_t& cond_empty;
			
		public:
			qReader(queue_t& q, mutex_t& m,
			        condition_t& c_empty);
			
			ElemType get();
		};
		
		/**@brief Allows thread safe queue write access.
		 */
		class qWriter
		{
		private:
			queue_t& queue;
			mutex_t& mutex;
			condition_t& cond_empty;
			
		public:
			qWriter(queue_t& q, mutex_t& m,
			        condition_t& c_empty);
			
			void put(ElemType message);
		};
		
		qWriter* writer;
		qReader* reader;
		
		
		/**@brief Initializing constructor.
		 */
		MessageQueueT();
		
		/**@brief Destructor.
		 */
		~MessageQueueT();
		
		
		/**@brief Appends another message queue to this one and clears it.
		 */
		void splice(MessageQueueT<ElemType>& that);
	};
	
	
	typedef MessageQueueT<struct MsgHeader*> MessageQueue;
	
	/**@brief This structure defines our generic message data format.
	 */
	struct MsgHeader
	{
		int messageNumber, dataLength;
		void* pData;
		MessageQueue::qWriter& sender;
		int sequenceNumber;
		
		/**@brief Initializing constructor.
		 */
		MsgHeader(int msgID, MessageQueue::qWriter& sender, int length,
		          void* data);
	};
	
	
	/* ******************************************** INLINE IMPLEMENTATION */
	
	template <typename ElemType>
	inline
	MessageQueueT<ElemType>::qReader::qReader(queue_t& q, mutex_t& m,
	                                          condition_t& c_empty)
	:	queue(q),
		mutex(m),
		cond_empty(c_empty)
	{}
	
	template <typename ElemType>
	ElemType
	MessageQueueT<ElemType>::qReader::get()
	{
		mutex_t::scoped_lock lock(mutex);
		
		while (queue.empty())
			cond_empty.wait(lock);
		
		ElemType ret = queue.front();
		queue.pop_front();
		return ret;
	}
	
	
	template <typename ElemType>
	inline
	MessageQueueT<ElemType>::qWriter::qWriter(queue_t& q, mutex_t& m,
	                                          condition_t& c_empty)
	:	queue(q),
		mutex(m),
		cond_empty(c_empty)
	{}
	
	template <typename ElemType>
	void
	MessageQueueT<ElemType>::qWriter::put(ElemType message)
	{
		mutex_t::scoped_lock lock(mutex);
		
		queue.push_back(message);
		
		cond_empty.notify_one();
	}
	
	
	template <typename ElemType>
	inline
	MessageQueueT<ElemType>::MessageQueueT()
	:	writer(new qWriter(queue, mutex, cond_empty)),
		reader(new qReader(queue, mutex, cond_empty))
	{}
	
	
	template <typename ElemType>
	inline
	MessageQueueT<ElemType>::~MessageQueueT()
	{
		mutex_t::scoped_lock lock(mutex);
		delete reader;
		delete writer;
	}
	
	template <typename ElemType>
	inline void
	MessageQueueT<ElemType>::splice(MessageQueueT<ElemType>& that)
	{
		mutex_t::scoped_lock lock(mutex);
		queue.splice(queue.end(), that.queue);
	}
	
	
	inline
	MsgHeader::MsgHeader(int mID, MessageQueue::qWriter& sendQ, int len,
	                     void* data)
	:	messageNumber(mID),
		dataLength(len),
		pData(data),
		sender(sendQ)
	{}
	
}

#endif
