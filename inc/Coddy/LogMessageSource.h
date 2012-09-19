////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_LOGMESSAGESOURCE_H
#define CLODDY_CORE_LOGGING_LOGMESSAGESOURCE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Include referenced interfaces.

#include "Cloddy/ILogMessageSource.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { namespace Handlers { class ILogMessageHandler; } } } }
namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Logging { class Logger; } } }
namespace Cloddy { namespace Core { namespace Logging { class LogMessageHandlerNode; } } }

// Declare class ::Cloddy::Core::Logging::LogMessageSource.

namespace Cloddy { namespace Core { namespace Logging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Logging::Handlers::ILogMessageHandler;
  
  /*!
   * @brief  Abstract base class for ILogMessageSource implementations.
   */
  class LogMessageSource : public virtual ILogMessageSource
  {
    // Declare friend classes.
    
    friend class Logger;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual LogSeverity GetSeverity();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ILogMessageSource> AddHandler(ILogMessageHandler* handler);
    
    virtual void ChangeSeverity(LogSeverity severity);
    
    virtual void ChangeSeverity(LogSeverity severity, bool descendants);
    
    virtual void ChangeSeverity(LogSeverity severity, bool descendants, bool ancestors);
    
    virtual Ptr<ILogMessageSource> RemoveHandler(ILogMessageHandler* handler);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The current log message severity.
     * 
     * Subclasses must not modify this field directly (use #GetSeverity instead)!
     */
    LogSeverity severity;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of LogMessageSource.
     * 
     * @param severity The initial log message severity.
     */
    LogMessageSource(LogSeverity severity);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  This method is called each time the value of #GetSeverity has changed.
     * 
     * @param updateDescendants Update severity levels in descendant sources?
     * @param updateAncestors Update severity levels in ascendant sources?>
     */
    virtual void OnSeverityChanged(bool updateDescendants, bool updateAncestors);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Head of linked list of associated log message handlers.
     */
    Ptr<LogMessageHandlerNode> firstHandler;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Handles the given log message by forwarding it to the configured ILogMessageHandlers.
     * 
     * @param source The source ILogger object.
     * @param logSeverity The LogSeverity of the log message.
     * @param logMessage The log message.
     */
    void HandleLogMessage(ILogger* source, LogSeverity logSeverity, String logMessage);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LogMessageSource> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x43EB9F7C;
    
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
      if ((ptr = ILogMessageSource::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
