#ifndef DataRequestMessage_h__
#define DataRequestMessage_h__

#include "Cloddy/INetworkMessage.h"
#include "CodeX/System.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{

  using namespace CodeX::System;

  class DataRequestMessage : public INetworkMessage
  {
  public:

    /*!
     * @brief Creates a data request message.
     * 
     * @param fileName Name of the dataset file.
     * @param offset Offset of the file.
     * @param bytestoTransfer Number of bytes to transfer.
     */
    DataRequestMessage(String fileName, uint64 offset, uint32 bytesToTransfer);

    /*!
     * @brief Deserializes this message from a byte array.
     * 
     * @param buffer Byte array to construct the message from.
     */
    DataRequestMessage(Array<uint8> buffer);

    /*!
     * @brief Gets the number of bytes to transfer
     * 
     * @return Number of bytes to transfer.
     */
    int GetNoBytesToTransfer();

    /*!
     * @brief Gets the offset of the file.
     * 
     * @return Offset of the file.
     */
    uint64 GetOffset();

    /*!
     * @brief Gets the name of the dataset file.
     * 
     * @return Name of the dataset file.
     */
    String GetFileName();

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

    int bytesToTransfer;
    uint64 offset;
    String fileName;
  };

}}}}

#endif // DataRequestMessage_h__