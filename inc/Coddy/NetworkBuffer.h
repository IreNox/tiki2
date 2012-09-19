#ifndef NETWORKBUFFER_H__
#define NETWORKBUFFER_H__

#include "CodeX/System.h"
#include "CodeX/Monitor.h"
#include "Cloddy/INetworkMessage.h"
#include "Cloddy_Core.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{

  using namespace CodeX;
  using namespace CodeX::System;
  using namespace Cloddy::Core::Collections;

  class NetworkBuffer : public Object
  {
  public:

    /*!
     * @brief Default constructor.
     */
    NetworkBuffer();

    /*!
     * @brief Retrieves the next available message.
     * 
     * @return The next message if available, otherwise null.
     */
    Ptr<INetworkMessage> GetNextMessage(bool block = false);

    /*!
     * @brief Fetches the buffer that is avilable to be sent.
     * 
     * @param buffer Byte array that should be sent with the length of count or less.
     * @param count Number of bytes to be sent.
     * 
     * @return Length of the buffer.
     */
    uint32 GetSendBuffer(Array<uint8> buffer, uint32 count);

    /*!
     * @brief Fills the receive buffer and tries to deserialize a message from it.
     * 
     * @param buffer Data to add to the receive buffer.
     * @param count Count of the data to add.
     */
    void ReceiveBytes(Array<uint8> buffer, uint32 count);

    /*!
     * @brief Adds the specified message to the send buffer.
     * 
     * @param message Message to send.
     */
    void SendMessage(Ptr<INetworkMessage> message);

    /*!
     * @brief Indicates if a message is available.
     * 
     * @return True if a message is available, false otherwise.
     */
    bool IsMessageAvailable();
 
    /*!
     * @brief Indicates if is available to be sent.
     * 
     * @return True if data is available, false otherwise.
     */
    bool IsSendDataAvailable();

  private:

    /*!
     * @brief Serialized the specified message into its byte representation
     * and adds it to the send buffer.
     * 
     * @param message The message to serialize.
     */
    void SerializeMessage(Ptr<INetworkMessage> message);

    /*!
     * @brief Tries to deserialize a message from the receive buffer.
     * If successful it removes the corresponding bytes from the buffer and adds the message to the message list.
     */
    void TryDeserialize();

    Monitor receiveMonitor;
    Monitor sendMonitor;

    bool sendDataAvailable;
    bool messageAvailable;


    // Prm = Primitive (all values types like int or double)
    ArrayList<Prm<uint8>> sendBuffer;
    ArrayList<Prm<uint8>> receiveBuffer;

    // Ref = References (everything else)
    ArrayList<Ref<INetworkMessage>> messages;
  };

}}}}

#endif // NETWORKBUFFER_H__