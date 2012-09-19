////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_STREAMING_NETWORKMESSAGE_H
#define CLODDY_STREAMING_NETWORKMESSAGE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IConnection; } } } }

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Streaming::NetworkMessage.

namespace Cloddy { namespace Streaming
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Sockets::IConnection;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  class NetworkMessage : public Disposable
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of NetworkMessage.
     * 
     * @param maximumMessageLength <b>[>0]</b>  The maximum message length,in bytes.
     */
    NetworkMessage(int32 maximumMessageLength);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Prepares a new network message for sending.
     * 
     * @param messageId <b>[>0]</b>  The message ID.
     */
    void Prepare(int32 messageId);
    
    bool ReadBool();
    
    int32 ReadInt16();
    
    int32 ReadInt24();
    
    int32 ReadInt32();
    
    int64 ReadInt64();
    
    int32 ReadInt8();
    
    String ReadString();
    
    /*!
     * @brief  Receives a network message from the given connection.
     * 
     * @param connection <b>[not-null]</b>  The connection.
     * 
     * @return The message ID or \c 0  if no message has been received.
     */
    int32 Receive(IConnection* connection);
    
    /*!
     * @brief  Sends the currently buffered network message over the given connection.
     * 
     * @param connection <b>[not-null]</b>  The connection.
     */
    void Send(IConnection* connection);
    
    void WriteBool(bool value);
    
    void WriteInt16(int32 value);
    
    void WriteInt24(int32 value);
    
    void WriteInt32(int32 value);
    
    void WriteInt64(int64 value);
    
    void WriteInt8(int32 value);
    
    /*!
     * @brief  Appends the given value to the network message.
     * 
     * @param value <b>[not-null]</b>  The value to append.
     */
    void WriteString(String value);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Length of each message header,in bytes.
     */
    static const int32 HeaderLength = 5;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    Ptr<ByteBuffer> buffer;
    
    int32 maximumMessageLength;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<NetworkMessage> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4F5CB3BB;
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    protected: virtual void* TryCast(int typeId)
    {
      if (typeId == TypeId) return (void*) this;
      void* ptr;
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
