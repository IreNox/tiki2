#ifndef NETWORKMESSAGETYPE_H__
#define NETWORKMESSAGETYPE_H__

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{

  enum NetworkMessageType
  {
    NetworkMessageType_None = 0,
    NetworkMessageType_DataRequestMessage = 1,
    NetworkMessageType_DataMessage = 2,
    NetworkMessageType_DatasetLengthMessage = 3,
  };

}}}}

#endif // NETWORKMESSAGETYPE_H__