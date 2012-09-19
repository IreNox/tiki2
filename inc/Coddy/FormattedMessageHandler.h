////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_HANDLERS_FORMATTEDMESSAGEHANDLER_H
#define CLODDY_CORE_LOGGING_HANDLERS_FORMATTEDMESSAGEHANDLER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Include referenced interfaces.

#include "Cloddy/ILogMessageHandler.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { namespace Formats { class ILogMessageFormat; } } } }
namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }

// Declare class ::Cloddy::Core::Logging::Handlers::FormattedMessageHandler.

namespace Cloddy { namespace Core { namespace Logging { namespace Handlers
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Core::Logging;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Logging::Formats::ILogMessageFormat;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base class for ILogMessageHandler implementations that use 
   *         an ILogMessageFormat object for formatting log messages.
   */
  class FormattedMessageHandler : public Disposable, public virtual ILogMessageHandler
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The log message format.
     * 
     * @return <b>[not-null]</b>  The log message format object.
     */
    Ptr<ILogMessageFormat> GetFormat();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void HandleLogMessage(ILogger* source, LogSeverity logSeverity, String logMessage);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of FormattedMessageHandler.
     * 
     * @param format <b>[not-null]</b>  The log message format to use.
     */
    FormattedMessageHandler(ILogMessageFormat* format);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DisposeManaged();
    
    /*!
     * @brief  Emits the given formatted log message.
     * 
     * @param msg The formatted log message.
     * @param severity The log message severity.
     */
    virtual void EmitLogMessage(String msg, LogSeverity severity) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The log message format.
     */
    Ptr<ILogMessageFormat> format;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FormattedMessageHandler> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDD37E6C2;
    
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
      if ((ptr = ILogMessageHandler::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
