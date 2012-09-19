////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_ILOGGER_H
#define CLODDY_CORE_LOGGING_ILOGGER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Include referenced interfaces.

#include "CodeX/IExceptionReporter.h"
#include "Cloddy/ILogMessageSource.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { class ILoggerCategory; } } }

// Declare interface ::Cloddy::Core::Logging::ILogger.

namespace Cloddy { namespace Core { namespace Logging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IExceptionReporter;
  
  /*!
   * @brief  Base interface for classes that are used to emit log messages.
   */
  class NO_VTABLE ILogger : public virtual ILogMessageSource, public virtual IExceptionReporter
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The category of this logger.
     * 
     * @return <b>[not-null]</b>  The logger category.
     */
    virtual Ptr<ILoggerCategory> GetCategory() = 0;
    
    /*!
     * @brief  Returns the full name of this logger.
     * 
     * @return <b>[not-null]</b>  The full name.
     */
    virtual String GetFullName() = 0;
    
    /*!
     * @brief  Returns the name of this logger.
     * 
     * @return <b>[not-null]</b>  The name.
     */
    virtual String GetName() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Emits a log messages of severity LogSeverity::LogSeverity_Common.
     * 
     * @param message The log message to emit.
     */
    virtual void Common(String message) = 0;
    
    /*!
     * @brief  Emits a log messages of severity LogSeverity::LogSeverity_Debug.
     * 
     * @param message The log message to emit.
     */
    virtual void Debug(String message) = 0;
    
    /*!
     * @brief  Emits a log messages of severity LogSeverity::LogSeverity_Error.
     * 
     * @param message The log message to emit.
     */
    virtual void Error(String message) = 0;
    
    /*!
     * @brief  Emits a log messages of severity LogSeverity::LogSeverity_Fatal.
     * 
     * @param message The log message to emit.
     */
    virtual void Fatal(String message) = 0;
    
    /*!
     * @brief  Emits a log messages of severity LogSeverity::LogSeverity_Info.
     * 
     * @param message The log message to emit.
     */
    virtual void Info(String message) = 0;
    
    /*!
     * @brief  Checks if the given log severity LogSeverity::LogSeverity_Common is enabled for this 
     *         logger.
     * 
     * @return \c true  if the log severity is enabled,\c false  if it is disabled.
     */
    virtual bool IsCommonEnabled() = 0;
    
    /*!
     * @brief  Checks if the given log severity LogSeverity::LogSeverity_Common is enabled for this 
     *         logger.
     * 
     * @return \c true  if the log severity is enabled,\c false  if it is disabled.
     */
    virtual bool IsDebugEnabled() = 0;
    
    /*!
     * @brief  Checks if the given log severity is enabled for this logger.
     * 
     * @param severity The log severity.
     * 
     * @return \c true  if the log severity is enabled,\c false  if it is disabled.
     */
    virtual bool IsEnabled(LogSeverity severity) = 0;
    
    /*!
     * @brief  Checks if the given log severity LogSeverity::LogSeverity_Common is enabled for this 
     *         logger.
     * 
     * @return \c true  if the log severity is enabled,\c false  if it is disabled.
     */
    virtual bool IsErrorEnabled() = 0;
    
    /*!
     * @brief  Checks if the given log severity LogSeverity::LogSeverity_Common is enabled for this 
     *         logger.
     * 
     * @return \c true  if the log severity is enabled,\c false  if it is disabled.
     */
    virtual bool IsFatalEnabled() = 0;
    
    /*!
     * @brief  Checks if the given log severity LogSeverity::LogSeverity_Common is enabled for this 
     *         logger.
     * 
     * @return \c true  if the log severity is enabled,\c false  if it is disabled.
     */
    virtual bool IsInfoEnabled() = 0;
    
    /*!
     * @brief  Checks if the given log severity LogSeverity::LogSeverity_Trace is enabled for this 
     *         logger.
     * 
     * @return \c true  if the log severity is enabled,\c false  if it is disabled.
     */
    virtual bool IsTraceEnabled() = 0;
    
    /*!
     * @brief  Checks if the given log severity LogSeverity::LogSeverity_Warning is enabled for 
     *         this logger.
     * 
     * @return \c true  if the log severity is enabled,\c false  if it is disabled.
     */
    virtual bool IsWarningEnabled() = 0;
    
    /*!
     * @brief  Emits a log messages of the given severity.
     * 
     * @param severity The log message severity.
     * @param message The log message to emit.
     */
    virtual void Message(LogSeverity severity, String message) = 0;
    
    /*!
     * @brief  Emits a log messages of severity LogSeverity::LogSeverity_Trace.
     * 
     * @param message The log message to emit.
     */
    virtual void Trace(String message) = 0;
    
    /*!
     * @brief  Emits a log messages of severity LogSeverity::LogSeverity_Warning.
     * 
     * @param message The log message to emit.
     */
    virtual void Warning(String message) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ILogger> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCCBD4429;
    
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
      if ((ptr = IExceptionReporter::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
