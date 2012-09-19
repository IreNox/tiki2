#ifndef NETWORKMESSAGETYPE_H__
#define NETWORKMESSAGETYPE_H__

namespace Cloddy { namespace API { namespace Network
{

  enum NetworkMessageType
  {
    NetworkMessageType_DataRequestMessage = 1,
    NetworkMessageType_DataMessage = 2,
    NetworkMessageType_DatasetLengthMessage = 3,
  };

}}}

#endif // NETWORKMESSAGETYPE_H__