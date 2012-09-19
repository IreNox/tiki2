#ifndef NETWORKMESSAGESERIALIZER_H__
#define NETWORKMESSAGESERIALIZER_H__

#include "CodeX/System.h"
#include "Cloddy_Core.h"
#include "Cloddy/INetworkMessage.h"
#include "Cloddy/NetworkMessageHeader.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{

  using namespace Cloddy::Core::Collections;
  using namespace CodeX;

  class NetworkMessageSerializer
  {
  public:
    
    /*!
     * @brief  Deserializes a buffer into the corresponding network message.
     * 
     * @param header The header of the message.
     * @param buffer Byte array starting after the header with the length of header.MessageSize
     * 
     * @return <b>[not-null]</b> The deserialized message.
     */
    static Ptr<INetworkMessage> DeserializeMessage(NetworkMessageHeader header, Array<uint8> buffer );
 
    /*!
     * @brief  Serializes a network message into a byte array.
     * 
     * @param message <b>[not-null]</b> The message to serialize.
     * 
     * @return <b>[not-null]</b> > The message as a byebyte array.
     */
   static Array<uint8> SerializeMessage(Ptr<INetworkMessage> message);

  private:

    /*!
     * @brief  Deserializes a buffer into the corresponding network message.
     * 
     * @param header The header of the message.
     * @param buffer Byte array starting after the header with the length of header.MessageSize
     * 
     * @return <b>[not-null]</b> The deserialized message.
     */
     static Ptr<INetworkMessage> DeserializeMessageUncompressed(NetworkMessageHeader header, Array<uint8> buffer);
     
    /*!
     * @brief  Serializes a network message into a byte array.
     * 
     * @param message <b>[not-null]</b> The message to serialize.
     * 
     * @return <b>[not-null]</b> > The message as a byebyte array.
     */
     static Array<uint8> SerializeMessageUncompressed(Ptr<INetworkMessage> message);
  };

}}}}
#endif // NETWORKMESSAGESERIALIZER_H__