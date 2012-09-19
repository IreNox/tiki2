////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_HANDLERS_CONSOLEMESSAGEHANDLER_H
#define CLODDY_CORE_LOGGING_HANDLERS_CONSOLEMESSAGEHANDLER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/ConsoleStream.h"
#include "Cloddy/LogSeverity.h"
#include "Cloddy/SimpleColor.h"

// Include referenced classes.

#include "Cloddy/FormattedMessageHandler.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { namespace Formats { class ILogMessageFormat; } } } }

// Declare class ::Cloddy::Core::Logging::Handlers::ConsoleMessageHandler.

namespace Cloddy { namespace Core { namespace Logging { namespace Handlers
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Core::Logging;
  using namespace Cloddy::Core::System;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Logging::Formats::ILogMessageFormat;
  
  /*!
   * @brief  An implementation of the ILogMessageHandler interface that writes log messages to the 
   *         standard output stream (ie. the console).
   */
  class ConsoleMessageHandler : public FormattedMessageHandler
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Use configured foreground and background colors when writing to the standard output 
     *         stream?
     * 
     * The default value is \c true .
     * 
     * @return \c true  to use colors,\c false  to use no colors.
     * 
     * @see #SetColors
     */
    bool GetUseColors();
    
    /*!
     * @brief  Use configured foreground and background colors when writing to the standard output 
     *         stream?
     * 
     * The default value is \c true .
     * 
     * @param value \c true  to use colors,\c false  to use no colors.
     * 
     * @see #SetColors
     */
    void SetUseColors(bool value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ConsoleMessageHandler.
     * 
     * @param format <b>[not-null]</b>  The log message format to use.
     */
    ConsoleMessageHandler(ILogMessageFormat* format);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Restores the default settings of this console message handler.
     * 
     */
    void RestoreDefaults();
    
    /*!
     * @brief  Sets the colors to use when writing to the standard output stream.
     * 
     * @param severity The log severity for which to set the colors.
     * @param foreground The foreground color.
     * @param background The background color.
     * 
     * @return <b>[not-null]</b>  this
     * 
     * @see #GetUseColors
     */
    Ptr<ConsoleMessageHandler> SetColors(LogSeverity severity, SimpleColor foreground, SimpleColor background);
    
    /*!
     * @brief  Sets the output console streams for the given log severity.
     * 
     * @param severity The log severity for which to set the output streams.
     * @param streams The output console streams.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<ConsoleMessageHandler> SetStreams(LogSeverity severity, ConsoleStream streams);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void EmitLogMessage(String msg, LogSeverity severity);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Foreground colors per log severity level.
     */
    Array<SimpleColor> background;
    
    /*!
     * @brief  Foreground colors per log severity level.
     */
    Array<SimpleColor> foreground;
    
    /*!
     * @brief  Mapping from log severity level to console output streams.
     */
    Array<ConsoleStream> outputStreams;
    
    /*!
     * @brief  Use configured foreground and background colors when writing to the standard output 
     *         stream?
     */
    bool useColors;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ConsoleMessageHandler> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8106C9CD;
    
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
      if ((ptr = FormattedMessageHandler::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
