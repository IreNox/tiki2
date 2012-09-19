////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_HANDLERS_ILOGMESSAGEHANDLER_H
#define CLODDY_CORE_LOGGING_HANDLERS_ILOGMESSAGEHANDLER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }

// Declare interface ::Cloddy::Core::Logging::Handlers::ILogMessageHandler.

namespace Cloddy { namespace Core { namespace Logging { namespace Handlers
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Core::Logging;
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that handle log messages.
   */
  class NO_VTABLE ILogMessageHandler : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Handles the given log message.
     * 
     * @param source <b>[not-null]</b>  The ILogger that has been used to emit the log message.
     * @param logSeverity The LogSeverity of the log message.
     * @param logMessage <b>[not-null]</b>  The log message
     */
    virtual void HandleLogMessage(ILogger* source, LogSeverity logSeverity, String logMessage) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ILogMessageHandler> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x39CE1B4B;
    
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
