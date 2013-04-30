
#ifndef RTDS_ODEMX_H_INCLUDED
#define RTDS_ODEMX_H_INCLUDED

namespace RTDS
{
  struct SDLBlock;
}

#include <vector>
#include "RTDS_SDLPROCESS.h"
#include "RTDS_MSGQUEUE.h"
#include "RTDS_LOGGER.h"

namespace RTDS
{
  /**@brief Base structure for generated SDL blocks.
   */
  struct SDLBlock
  {
  protected:
    SDLBlock* cover;
    std::vector<MessageQueue::qWriter*> context;
    Logger& logger;
    
    /**@brief Registers a message queue for call-by-name functionality.
     */
    void embed(MessageQueue::qWriter& writer, unsigned id);
    
  public:
    
    /**@brief Constructor.
     */
    SDLBlock(Logger& logger);
    
    /** Virtual destructor.
     */
    virtual ~SDLBlock() {}
    
    /**@brief Registers a block as being covered by this block.
     */
    void embed(SDLBlock& block);
    
    /**@brief Registers a process for call-by-name functionality.
     */
    void embed(SDLProcess& process, unsigned id);
    
    /**@brief Returns the message queue from a process that is specified by an
     *        ID.
     */
    MessageQueue::qWriter* getMsgQWriterByID(unsigned id) const;
    
    /**@brief Activates all child blocks and processes.
     */
    virtual void activate() = 0;
  };
  
}

#endif
