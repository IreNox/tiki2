#ifndef NETWORKMESSAGEFACTORY_H__
#define NETWORKMESSAGEFACTORY_H__

#include "CodeX/System.h"
#include "Cloddy/INetworkMessage.h"
#include "Cloddy/NetworkMessageType.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{

  class NetworkMessageFactory
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
     static Ptr<INetworkMessage> FromBytes(NetworkMessageType type, Array<uint8> buffer);
  };

}}}}

#endif // NETWORKMESSAGEFACTORY_H__