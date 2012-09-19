////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_STREAMING_MESSAGEID_BROWSE_1_H
#define CLODDY_STREAMING_MESSAGEID_BROWSE_1_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Streaming::MessageId_Browse_1.

namespace Cloddy { namespace Streaming
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  enum MessageId_Browse_1
  {
    /*!
     * @brief  No network message.
     */
    MessageId_Browse_1_None = 0,
    
    /*!
     * @brief  Network message 'List' (client =>server).
     * 
     * Response:
     *   - #MessageId_Browse_1_ResponseList
     * Payload:none 
     */
    MessageId_Browse_1_RequestList = 1,
    
    /*!
     * @brief  Network message 'ResponseList' (server =>client)
     * 
     * Payload:
     *   - bool :Is this the last dataset in the list?
     *   - int32 :dataset handle
     *   - string :dataset descriptio.
     */
    MessageId_Browse_1_ResponseList = 2,
    
    /*!
     * @brief  Network message 'RequestOpen' (client =>server).
     * 
     * Response:
     *   - #MessageId_Browse_1_ResponseOpen
     * Payload:
     *   - int32 :dataset handle
     */
    MessageId_Browse_1_RequestOpen = 2,
    
    /*!
     * @brief  Network message 'ResponseOpen' (server =>client).
     * 
     * Payload:
     *   - int8 :dataset map type (0 :=rect,1 :=cube)
     *   - int32 :dataset width
     *   - int32 :dataset height
     */
    MessageId_Browse_1_ResponseOpen = 3
  };
  
} } 

#endif
