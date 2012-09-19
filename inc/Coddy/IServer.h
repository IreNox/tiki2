////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SOCKETS_ISERVER_H
#define CLODDY_CORE_IO_SOCKETS_ISERVER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IConnection; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IEndPoint; } } } }

// Declare interface ::Cloddy::Core::IO::Sockets::IServer.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Base interface for classes that act as network servers.
   */
  class NO_VTABLE IServer : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the network endpoint address of this server.
     * 
     * @return <b>[not-null]</b>  The network endpoint address.
     */
    virtual Ptr<IEndPoint> GetEndPoint() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Accepts a new client connection to this server.
     * 
     * @param timeout <b>[>0]</b>  Timeout in milliseconds.
     * 
     * @return The accepted IConnection or \c null  if the socket has been closed.
     * 
     * @exception IOException If an unexpected error or timeout occurs (see IOException::GetError).
     */
    virtual Ptr<IConnection> Accept(int32 timeout) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IServer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x659960ED;
    
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
