
#ifndef RTDS_MSGQUEUE_H_INCLUDED
#define RTDS_MSGQUEUE_H_INCLUDED

#include <list>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>

namespace RTDS
{
  typedef boost::mutex mutexType;
  
  /**@brief Represents a message queue for SDL processes.
   */
  template <typename ElemType>
  class MessageQueueT
  {
  private:
    typedef std::list<ElemType> queueType;
    
    queueType queue;
    mutexType mutex;
    boost::condition cond_empty;
    
  public:
    
    /**@brief Allows thread safe queue read access.
     */
    class qReader
    {
    private:
      queueType& queue;
      mutexType& mutex;
      boost::condition& cond_empty;
      
    public:
      qReader(queueType& q, mutexType& m, boost::condition& c_empty)
      : queue(q), mutex(m), cond_empty(c_empty)
      {}
      
      ElemType get();
    };
    
    /**@brief Allows thread safe queue write access.
     */
    class qWriter
    {
    private:
      queueType& queue;
      mutexType& mutex;
      boost::condition& cond_empty;
      
    public:
      qWriter(queueType& q, mutexType& m, boost::condition& c_empty)
      : queue(q), mutex(m), cond_empty(c_empty)
      {}
      
      void put(ElemType message);
    };
    
    qWriter* writer;
    qReader* reader;
    
    /* ******************************************************* create/destroy */
    
    /**@brief Initializing constructor.
     */
    MessageQueueT()
    : writer(new qWriter(queue, mutex, cond_empty)),
      reader(new qReader(queue, mutex, cond_empty))
    {}
    
    /**@brief Destructor.
     */
    ~MessageQueueT()
    {
      mutexType::scoped_lock lock(mutex);
      delete reader;
      delete writer;
    }
    
    /* ************************************************************** methods */
    
    /**@brief Appends another message queue to this one and clears it.
     */
    void splice(MessageQueueT<ElemType>& that)
    {
      mutexType::scoped_lock lock(mutex);
      queue.splice(queue.end(), that.queue);
    }
  };
  
  class MsgHeader;
  typedef MessageQueueT<MsgHeader*> MessageQueue;
  
  /**@brief This structure defines our generic message data format.
   */
  struct MsgHeader
  {
    int messageNumber,
        dataLength;
    void* pData;
    MessageQueue::qWriter& sender;
    int sequenceNumber;
    
    /**@brief Initializing constructor.
     */
    MsgHeader(int msgID, MessageQueue::qWriter& sender, int length, void* data);
  };
  
  /* **************************************************************** qReader */
  /* PUBLIC ***************************************************************** */
  
  template <typename ElemType>
  ElemType MessageQueueT<ElemType>::qReader::get()
  {
    mutexType::scoped_lock lock(mutex);
    
    while (queue.empty())
      cond_empty.wait(lock);
    
    ElemType ret = queue.front();
    queue.pop_front();
    return ret;
  }
  
  /* **************************************************************** qWriter */
  /* PUBLIC ***************************************************************** */
  
  template <typename ElemType>
  void MessageQueueT<ElemType>::qWriter::put(ElemType message)
  {
    mutexType::scoped_lock lock(mutex);
    
    queue.push_back(message);
    
    cond_empty.notify_one();
  }
}

typedef RTDS::MessageQueue::qWriter* RTDS_QueueId;

#endif
