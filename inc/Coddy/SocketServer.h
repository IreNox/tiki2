////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SOCKETS_SOCKETSERVER_H
#define CLODDY_CORE_IO_SOCKETS_SOCKETSERVER_H

#include "CodeX/System_Native.h"

// Include referenced interfaces.

#include "Cloddy/IServer.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IConnection; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IEndPoint; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class SocketEndPoint; } } } }

// Declare class ::Cloddy::Core::IO::Sockets::SocketServer.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  An implementation of the IServer interface for TCP/IP.
   */
  class SocketServer : public Disposable, public virtual IServer
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
    
    virtual Ptr<IConnection> Accept(int32 timeout);
    
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
     * @brief  The local socket endpoint.
     */
    Ptr<SocketEndPoint> endPoint;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SocketServer.
     * 
     * @param endPoint The local socket endpoint.
     */
    SocketServer(SocketEndPoint* endPoint);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SocketServer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x468DDF4D;
    
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
      if ((ptr = IServer::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("5F307D1F-7253-46EA-89AE-20A78258234A")
    
    // TODO: Implement!
    
    NATIVE_BLOCK_END   ("5F307D1F-7253-46EA-89AE-20A78258234A")
  };
  
} } } } 

#endif
