////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SOCKETS_SOCKETCONNECTION_H
#define CLODDY_CORE_IO_SOCKETS_SOCKETCONNECTION_H

#include "CodeX/System_Native.h"

// Include referenced interfaces.

#include "Cloddy/IConnection.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IEndPoint; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class SocketEndPoint; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::IO::Sockets::SocketConnection.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  An implementation of the IConnection interface for TCP/IP.
   */
  class SocketConnection : public Disposable, public virtual IConnection
  {
    // Declare friend classes.
    
    friend class SocketEndPoint;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IEndPoint> GetEndPoint();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual bool Receive(ByteBuffer* buffer);
    
    virtual bool Send(ByteBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeUnmanaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The remote socket endpoint.
     */
    Ptr<SocketEndPoint> endPoint;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SocketConnection.
     * 
     * @param endPoint The remote socket endpoint.
     * @param timeout Timeout,in milliseconds.
     */
    SocketConnection(SocketEndPoint* endPoint, int32 timeout);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SocketConnection> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF6F77630;
    
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
      if ((ptr = IConnection::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("0F21A329-F214-44AA-BF94-52DBC6111D0F")
    
    // TODO: Implement!
    
    NATIVE_BLOCK_END   ("0F21A329-F214-44AA-BF94-52DBC6111D0F")
  };
  
} } } } 

#endif
