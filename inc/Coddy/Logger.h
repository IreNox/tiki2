////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_LOGGER_H
#define CLODDY_CORE_LOGGING_LOGGER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Include referenced interfaces.

#include "Cloddy/ILogger.h"

// Include referenced classes.

#include "Cloddy/LogMessageSource.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { class ILoggerCategory; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Logging { class LoggerCategory; } } }
namespace CodeX { namespace System { class ErrorInfo; } }

// Declare class ::Cloddy::Core::Logging::Logger.

namespace Cloddy { namespace Core { namespace Logging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::ErrorInfo;
  
  /*!
   * @brief  Default implementation of the ILogger interface.
   */
  class Logger : public LogMessageSource, public virtual ILogger
  {
    // Declare friend classes.
    
    friend class LoggerCategory;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<ILoggerCategory> GetCategory();
    
    virtual String GetFullName();
    
    virtual String GetName();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Common(String message);
    
    virtual void Debug(String message);
    
    virtual void Error(String message);
    
    virtual void Fatal(String message);
    
    virtual void Info(String message);
    
    virtual bool IsCommonEnabled();
    
    virtual bool IsDebugEnabled();
    
    virtual bool IsEnabled(LogSeverity severity);
    
    virtual bool IsErrorEnabled();
    
    virtual bool IsFatalEnabled();
    
    virtual bool IsInfoEnabled();
    
    virtual bool IsTraceEnabled();
    
    virtual bool IsWarningEnabled();
    
    virtual void Message(LogSeverity severity, String message);
    
    virtual void ReportError(ErrorInfo* errorInfo);
    
    virtual void Trace(String message);
    
    virtual void Warning(String message);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void OnSeverityChanged(bool updateDescendants, bool updateAncestors);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The logger category of this logger.
     */
    Ptr<LoggerCategory> category;
    
    /*!
     * @brief  The cached full name of this logger.
     */
    String fullName;
    
    /*!
     * @brief  The name of this logger.
     */
    String name;
    
    /*!
     * @brief  Points to the next logger in the linked list of loggers in #category.
     */
    Ptr<Logger> nextSibling;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Logger.
     * 
     * @param name The name of this logger.
     * @param category The logger category of this logger.
     * @param severity The current log message severity.
     * @param nextSibling Points to the next logger in the linked list of loggers in .
     */
    Logger(String name, LoggerCategory* category, LogSeverity severity, Logger* nextSibling);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Logger> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x53D08638;
    
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
      if ((ptr = LogMessageSource::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ILogger::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
