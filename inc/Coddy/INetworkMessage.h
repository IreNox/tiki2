#ifndef INETWORKMESSAGE_H__
#define INETWORKMESSAGE_H__

#include "CodeX/System.h"
#include "Cloddy_Core.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{

  using namespace Cloddy::Core::Collections;
  using namespace CodeX;

  struct INetworkMessage : public Object
  {
    /*!
     * @brief Gets the type of the message.
     * 
     * @return Integer representing a NetworkMessageType.
     */
    virtual int GetType() = 0;

    /*!
     * @brief Serializes the message into its byte representation
     * 
     * @return <b>[not-null]</b> The byte representation of the message.
     */
    virtual Array<uint8> GetBytes() = 0;
  };

}}}}

#endif // INETWORKMESSAGE_H__