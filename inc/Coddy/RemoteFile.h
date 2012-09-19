#ifndef REMOTEFILE_H__
#define REMOTEFILE_H__

#include "CodeX/System.h"
#include "Cloddy/NetworkConnection.h"
#include "Cloddy/Cloddy_Core.h"

namespace Cloddy { namespace Core { namespace IO { namespace Files 
{

  using namespace CodeX;
  using namespace Cloddy::Core::IO::Network;

  class RemoteFile : public FileBase
  {
  public:

    /*!
     * @brief Opens a specified file from the specified network connection.
     *
     * @param network The network connection to use to open the file.
     * @param datasetName The name of the file.
     */
    RemoteFile(Ptr<NetworkConnection> connection, String fileName);

    virtual void SetFileLength(int64 length);
    virtual Ptr<ByteBuffer> Map();
    virtual void Unmap();
    virtual int32 GetByteAlignment();
    virtual void Flush();
    virtual void Read(int64 offset, ByteBuffer* buffer, IAsyncIO* asyncIO);
    virtual void Write(int64 offset, ByteBuffer* buffer, IAsyncIO* asyncIO);


  private: 

    void GetFileLength();

    String fileName;
    Ptr<NetworkConnection> connection;
    Ptr<INetworkMessage> message;
    Ptr<INetworkMessage> dataRequestMessage;
  };

}}}}
#endif // REMOTEFILE_H__