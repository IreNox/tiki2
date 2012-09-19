#ifndef NETWORKMESSAGEHEADER_H__
#define NETWORKMESSAGEHEADER_H__

#include "CodeX/System.h"
#include "Cloddy/NetworkMessageType.h"
#include "Cloddy_Core.h"

namespace Cloddy { namespace Core { namespace IO { namespace Network 
{
 
#define HEADERSIZE 8

  using namespace Cloddy::Core::Collections;
  using namespace CodeX;
  
  struct NetworkMessageHeader
  {
    /*!
     * @brief Indicates if the following message is compressed.
     */
    bool Compressed;
   
    /*!
     * @brief The type of the following message..
     */
    NetworkMessageType Type;
  
    /*!
     * @brief Size of the following message.
     */
    uint32 MessageSize;


    /*!
     * @brief Default constructor of the NetworkMessageHeader.
     */
    NetworkMessageHeader();

    /*!
     * @brief  Creates the NetworkMessageHeader.
     * 
     * @param buffer Byte array with the following bytes:
     *               Byte 0-1: HeaderTag: cm (CloddyMessage)
     *               Byte 2: NetworkMessageType
     *               Byte 3: BitMask
     *                 - Bit 0: 0 = Uncompressed, 1 = Compressed
     *               Byte 4-7: Size of the Message (little Endian)
     */
    NetworkMessageHeader(Array<uint8> buffer);

    /*!
     * @brief  Constructs the bytes of the header.
     * 
     * @param buffer Byte array with the following bytes:
     *               Byte 0-1: HeaderTag: cm (CloddyMessage)
     *               Byte 2: NetworkMessageType
     *               Byte 3: BitMask
     *                 - Bit 0: 0 = Uncompressed, 1 = Compressed
     *               Byte 4-7: Size of the Message (little Endian)
     */
    Array<uint8> GetBytes();

  };

}}}}

#endif // NETWORKMESSAGEHEADER_H__