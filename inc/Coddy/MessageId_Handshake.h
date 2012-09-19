////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_STREAMING_MESSAGEID_HANDSHAKE_H
#define CLODDY_STREAMING_MESSAGEID_HANDSHAKE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Streaming::MessageId_Handshake.

namespace Cloddy { namespace Streaming
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  enum MessageId_Handshake
  {
    /*!
     * @brief  No network message.
     */
    MessageId_Handshake_None = 0,
    
    /*!
     * @brief  Network message 'AskProtocol' (client =>server).
     * 
     * After establishing a network connection,the client sends this message to the server in order 
     * to negotiate which protocol version to use.
     * 
     * Response:
     *   - #MessageId_Handshake_UseProtocol
     * Payload:
     *   - int64 :magic protocol number <c>89 53 52 56 0D 0A 1A 0A</c>
     *   - int8 :maximum client protocol version (major)
     *   - int8 :maximum client protocol version (minor)
     */
    MessageId_Handshake_AskProtocol = 1,
    
    /*!
     * @brief  Network message 'UseProtocol' (server =>client).
     * 
     * The server sends this message to a client after it has decided on which protocol version to 
     * use.
     * 
     * Payload:
     *   - int8 :protocol version (major)
     *   - int8 :protocol version (minor)
     */
    MessageId_Handshake_UseProtocol = 2,
    
    /*!
     * @brief  Network message 'Ping' (server &lt; =>client).
     * 
     * The server or client can send this message at any time during a connection.
     * 
     * Response:
     *   - #MessageId_Handshake_Pong
     * Payload:
     *   - int64 :system timestamp
     */
    MessageId_Handshake_Ping = 3,
    
    /*!
     * @brief  Network message 'Pong' (server &lt; =>client).
     * 
     * The server or client sends this message after receiving a #MessageId_Handshake_Ping message.
     * 
     * Payload:
     *   - int64 :system timestamp
     */
    MessageId_Handshake_Pong = 4,
    
    /*!
     * @brief  Network message 'GoodBye' (server &lt;=>client).
     * 
     * The server or client sends this message before it shuts down.
     * 
     * Payload:none 
     */
    MessageId_Handshake_GoodBye = 5
  };
  
} } 

#endif
