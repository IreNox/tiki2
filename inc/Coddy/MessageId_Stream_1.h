////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_STREAMING_MESSAGEID_STREAM_1_H
#define CLODDY_STREAMING_MESSAGEID_STREAM_1_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Streaming::MessageId_Stream_1.

namespace Cloddy { namespace Streaming
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  enum MessageId_Stream_1
  {
    /*!
     * @brief  No network message.
     */
    MessageId_Stream_1_None = 0,
    
    /*!
     * @brief  Network message 'Close' (client =>server).
     * 
     * Payload:none 
     */
    MessageId_Stream_1_Close = 1
  };
  
} } 

#endif
