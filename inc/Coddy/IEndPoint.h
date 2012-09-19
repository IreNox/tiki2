////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SOCKETS_IENDPOINT_H
#define CLODDY_CORE_IO_SOCKETS_IENDPOINT_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IConnection; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IServer; } } } }

// Declare interface ::Cloddy::Core::IO::Sockets::IEndPoint.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent network addresses resp. endpoints.
   */
  class NO_VTABLE IEndPoint : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new network server that listens on this endpoint.
     * 
     * @return <b>[not-null]</b>  The created network server.
     * 
     * @exception IOException If an unexpected error occurs..
     */
    virtual Ptr<IServer> CreateServer() = 0;
    
    /*!
     * @brief  Opens a new network connection to this endpoint.
     * 
     * @param timeout <b>[>=0]</b>  The timeout in milliseconds or \c 0  to disable timout.
     * 
     * @return The created network connection or \c null  if the timeout has elapsed.
     * 
     * @exception IOException If an unexpected error or timeout occurs (see IOException::GetError).
     */
    virtual Ptr<IConnection> OpenConnection(int32 timeout) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IEndPoint> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4FBEAE5F;
    
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
      return (void*) 0;
    }
  };
} } } } 

#endif
