#ifndef NETWORKMESSAGEHEADER_H__
#define NETWORKMESSAGEHEADER_H__

#include "CodeX/System.h"
#include "Cloddy/NetworkMessageType.h"

namespace Cloddy { namespace API { namespace Network
{

  using namespace CodeX;

  struct NetworkMessageHeader
  {
    bool Compressed;
    NetworkMessageType Type;
    int32 MessageSize;

    NetworkMessageHeader();
    NetworkMessageHeader(int64 buffer);

    int64 GetBytes();

  };

}}}

#endif // NETWORKMESSAGEHEADER_H__