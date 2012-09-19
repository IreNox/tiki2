#ifndef NETWORKCONNECTION_H__
#define NETWORKCONNECTION_H__

#include <WinSock2.h>
#include "Cloddy/NetworkThread.h"
#include "Cloddy/NetworkBuffer.h"
#include "CodeX/System.h"
#include "CodeX/Monitor.h"
#include "Cloddy_Core.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{
  using namespace CodeX;
  using namespace CodeX::System;
  using namespace Cloddy::Core::Threading;

  class NetworkConnection : public Object
  {
    friend class NetworkThread;

  public:

    /*!
     * @brief Maximum size read from or written to the network.
     */
    static const uint32 MaxDataSize = 1 << 21;


    NetworkConnection(SOCKET socket);
    NetworkConnection(String host, int port);

    /*!
     * @brief The buffer that handles serialization and deserialization.
     * 
     * @return <b>[not-null]</b> The underlying buffer object.
     */
    Ptr<NetworkBuffer> Buffer();

    /*!
     * @brief Starts the receive and send thread.
     */
    void Start();

    /*!
     * @brief Stops the receive and send thread.
     */
    void Stop();

    /*!
     * @brief Closes the network connection.
     * After callign this function, the connection can#t be used anymore!
     */
    void Close();

    /*!
     * @brief Indicates if the connection has been closed (renders it unusable)
     * 
     * @return True if the connection has been closed, false otherwise.
     */
    bool IsClosed();

    /*!
     * @brief Indicates if the connection is running.
     * 
     * @return True if the connectionis running, false otherwise.
     */
    bool IsRunning();
    
  private:

    /*!
     * @brief Initializes the NetworkConnection.
     */
    void Initialize();

    /*!
     * @brief Function that receives the data from the network.
     */
    void ReceiveMethod();

    /*!
     * @brief Function that sends data through the network.
     */
    void SendMethod();

    /*!
     * @brief Stops the receive and send threads.
     */
    void StopThreads();

    bool closed;
    bool running;
    SOCKET socket;

    Monitor monitor;
    Ptr<Thread> receiveThread;
    Ptr<Thread> sendThread;

    Ptr<NetworkBuffer> buffer;

  };

}}}}

#endif // NETWORKCONNECTION_H__