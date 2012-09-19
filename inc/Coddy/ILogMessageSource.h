////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_ILOGMESSAGESOURCE_H
#define CLODDY_CORE_LOGGING_ILOGMESSAGESOURCE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { namespace Handlers { class ILogMessageHandler; } } } }

// Declare interface ::Cloddy::Core::Logging::ILogMessageSource.

namespace Cloddy { namespace Core { namespace Logging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Logging::Handlers::ILogMessageHandler;
  
  /*!
   * @brief  Base interface for classes that generate log messages.
   */
  class NO_VTABLE ILogMessageSource : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Sets or gets the log message severity that shall be emitted for this log message 
     *         source.
     * 
     * @return The log message severity.
     */
    virtual LogSeverity GetSeverity() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds a log message handler to this log message source.
     * 
     * @param handler <b>[not-null]</b>  The handler to add.
     * 
     * @return <b>[not-null]</b>  this
     */
    virtual Ptr<ILogMessageSource> AddHandler(ILogMessageHandler* handler) = 0;
    
    /*!
     * @brief  Changes the log message severity of this log message source.
     * 
     * @param severity The new log message severity.
     */
    virtual void ChangeSeverity(LogSeverity severity) = 0;
    
    /*!
     * @brief  Changes the log message severity of this log message source.
     * 
     * @param severity The new log message severity.
     * @param descendants Also set all descendant log message sources to the given log message 
     * severity?
     */
    virtual void ChangeSeverity(LogSeverity severity, bool descendants) = 0;
    
    /*!
     * @brief  Changes the log message severity of this log message source.
     * 
     * @param severity The new log message severity.
     * @param descendants Also set all descendant log message sources to the given log message 
     * severity?
     * @param ancestors Set the log message severity of all ancestor log message sources to the 
     * given log message severity if less detailed?
     */
    virtual void ChangeSeverity(LogSeverity severity, bool descendants, bool ancestors) = 0;
    
    /*!
     * @brief  Removes the given log message handle from this log message source.
     * 
     * @param handler <b>[not-null]</b>  The handler to remove.
     * 
     * @return <b>[not-null]</b>  this
     */
    virtual Ptr<ILogMessageSource> RemoveHandler(ILogMessageHandler* handler) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ILogMessageSource> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x667DBAAB;
    
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
