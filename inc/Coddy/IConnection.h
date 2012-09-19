////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SOCKETS_ICONNECTION_H
#define CLODDY_CORE_IO_SOCKETS_ICONNECTION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IEndPoint; } } } }

// Forward declare referenced classes.

namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::Core::IO::Sockets::IConnection.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Base interface for network connections.
   * 
   * Network connections provided by IConnection implementations are connection oriented and 
   * reliable.
   */
  class NO_VTABLE IConnection : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the network endpoint address of this connections the remote endpoint.
     * 
     * @return <b>[not-null]</b>  The network endpoint address.
     */
    virtual Ptr<IEndPoint> GetEndPoint() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Receives a sequence of bytes from this network connection.
     * 
     * The number of bytes to receive is the number of ByteBuffer::GetRemaining bytes in the 
     * given ByteBuffer.The received bytes will be written to the buffer beginning at its 
     * current ByteBuffer::GetPosition.
     * 
     * @param buffer <b>[not-null]</b>  The byte buffer where to store the received bytes.
     * 
     * @return <c>true if all requested bytes have been received,\c false  if the socket has been 
     * closed.</c>
     * 
     * @exception IOException If an unexpected error or timeout occurs (see IOException::GetError).
     */
    virtual bool Receive(ByteBuffer* buffer) = 0;
    
    /*!
     * @brief  Sends a sequence of bytes over this network connection.
     * 
     * The ByteBuffer::GetPosition and ByteBuffer::GetLimit of the given ByteBuffer depict the 
     * range of bytes in the buffer that will be sent.
     * 
     * @param buffer <b>[not-null]</b>  The byte buffer that holds the bytes to send.
     * 
     * @return \c true  if the data has been sent successfully,\c false  if the socket has been 
     * closed.
     * 
     * @exception IOException If an unexpected error or timeout occurs (see IOException::GetError).
     */
    virtual bool Send(ByteBuffer* buffer) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IConnection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x178C056C;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
