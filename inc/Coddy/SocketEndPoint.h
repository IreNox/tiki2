////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SOCKETS_SOCKETENDPOINT_H
#define CLODDY_CORE_IO_SOCKETS_SOCKETENDPOINT_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IEndPoint.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IConnection; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Sockets { class IServer; } } } }

// Declare class ::Cloddy::Core::IO::Sockets::SocketEndPoint.

namespace Cloddy { namespace Core { namespace IO { namespace Sockets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Represents a socket address for TCP/IP.
   */
  class SocketEndPoint : public virtual IEndPoint
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The hostname or IP address.
     * 
     * @return <b>[not-null]</b>  The hostname or IP address.
     */
    String GetHostname();
    
    /*!
     * @brief  The port number.
     * 
     * @return <b>[0..65535]</b>  The port number.
     */
    int32 GetPortNumber();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SocketEndPoint.
     * 
     * @param hostname <b>[not-null]</b>  The hostname or IP address.
     * @param portNumber <b>[0..65535]</b>  The port number.
     */
    SocketEndPoint(String hostname, int32 portNumber);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IServer> CreateServer();
    
    virtual Ptr<IConnection> OpenConnection(int32 timeout);
    
    virtual String ToString();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The hostname or IP address.
     */
    String hostname;
    
    /*!
     * @brief  The port number.
     */
    int32 portNumber;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SocketEndPoint> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1A82C6DF;
    
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
      if ((ptr = IEndPoint::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
