////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_LOGMESSAGEHANDLERNODE_H
#define CLODDY_CORE_LOGGING_LOGMESSAGEHANDLERNODE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { namespace Handlers { class ILogMessageHandler; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Logging { class LogMessageSource; } } }

// Declare class ::Cloddy::Core::Logging::LogMessageHandlerNode.

namespace Cloddy { namespace Core { namespace Logging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Logging::Handlers::ILogMessageHandler;
  
  /*!
   * @brief  Node class for storing ILogMessageHandler objects in a linked list.
   */
  class LogMessageHandlerNode : public virtual Object
  {
    // Declare friend classes.
    
    friend class LogMessageSource;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The stored ILogMessageHandler object.
     */
    Ptr<ILogMessageHandler> handler;
    
    /*!
     * @brief  Pointer to the next node in the linked list.
     */
    Ptr<LogMessageHandlerNode> next;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of LogMessageHandlerNode.
     * 
     * @param handler The stored ILogMessageHandler object.
     * @param next Pointer to the next node in the linked list.
     */
    LogMessageHandlerNode(ILogMessageHandler* handler, LogMessageHandlerNode* next);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LogMessageHandlerNode> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE0E7E2B7;
    
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
  
} } } 

#endif
