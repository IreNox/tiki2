#ifndef DatasetLengthMessage_h__
#define DatasetLengthMessage_h__

#include "Cloddy/INetworkMessage.h"
#include "CodeX/System.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{

  using namespace CodeX::System;

  class DatasetLengthMessage : public INetworkMessage
  {
  public:

    /*!
     * @brief Deserializes a byte array into this message.
     * 
     * @param buffer Buffer to deserialize the message from.
     * 
     * @return <b>[not-null]</b> Deserialized instance.
     */
    static Ptr<INetworkMessage> FromBytes(Array<uint8> buffer);

    /*!
     * @brief Creates a message meant to request the length of the specified dataset file.
     * 
     * @param fileName Name of the datasetFile.
     * 
     * @return <b>[not-null]</b> Instance of this message meant to request the length of the specified file..
     */
    static Ptr<INetworkMessage> RequestLength(String fileName);

    /*!
     * @brief Creates a message meant to deliver the length of the specified dataset file.
     * 
     * @param fileName Name of the datasetFile.
     * @param length Length of the file.
     * 
     * @return <b>[not-null]</b> Instance of this message meant to deliver the length of the specified file..
     */
    static Ptr<INetworkMessage> SendLength(String fileName, uint64 length);

    /*!
     * @brief Indicates whether this message requests or delivers the length of the file.
     * 
     * @return True if it is a request, otherwise false.
     */
    bool IsRequest();

    /*!
     * @brief Gets the length of the file.
     * 
     * @return The length of the file.
     */
    uint64 GetLength();

    /*!
     * @brief Gets the file name of the dataset.
     * 
     * @return The file name of the dataset.
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
    DatasetLengthMessage();

    bool request;
    uint64 length;
    String fileName;

  };

}}}}

#endif // DatasetLengthMessage_h__