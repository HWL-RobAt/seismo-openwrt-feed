
#include "RTDS_MSGQUEUE.h"
#include <string>
#include <boost/thread/thread.hpp>

namespace RTDS
{
  using namespace boost;
  
  /* ********************************************************* message header */
  /* PUBLIC ***************************************************************** */
  MsgHeader::MsgHeader(int mID, MessageQueue::qWriter& sendQ, int len,
                       void* data)
  : messageNumber(mID),
    dataLength(len),
    pData(data),
    sender(sendQ)
  {}
}

