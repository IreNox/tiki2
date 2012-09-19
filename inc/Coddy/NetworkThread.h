#ifndef NETWORKTHREAD_H__
#define NETWORKTHREAD_H__

#include "Cloddy_Core.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{

  using namespace CodeX;
  using namespace Cloddy::Core::Threading;

  class NetworkConnection;

  class NetworkThread : public ThreadMainBase
  {
  public:

    NetworkThread(NetworkConnection *connection, bool send);

    virtual void Run(IThreadContext *arg);

  private:

    Ptr<NetworkConnection> connection;
    bool send;
  };

}}}}

#endif // NETWORKTHREAD_H__