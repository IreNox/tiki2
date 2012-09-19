#ifndef DataMessage_h__
#define DataMessage_h__

#include "Cloddy/INetworkMessage.h"
#include "CodeX/System.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{

  using namespace CodeX::System;

  class DataMessage : public INetworkMessage
  {
  public:

    /*!
     * @brief Creates the message specifying the data.
     * 
     * @param buffer Byte array representing the data.
     */
    DataMessage(Array<uint8> buffer);

    /*!
     * @brief Data of the file.
     * 
     * @return Byte array of the data.
     */
    Array<uint8> GetData();

    /*!
     * @brief Gets the type of the message.
     * 
     * @return Integer representing a NetworkMessageType.
     */
    virtual int GetType();

    /*!
     * @brief Serializes the message into its byte representation
     * 
     * @return <b>[not-null]</b> The byte representation of the message.
     */
    virtual Array<uint8> GetBytes();

  private:

    Array<uint8> data;
  };

}}}}

#endif // DataMessage_h__