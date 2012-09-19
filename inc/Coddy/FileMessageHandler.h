////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_LOGGING_HANDLERS_FILEMESSAGEHANDLER_H
#define CLODDY_CORE_LOGGING_HANDLERS_FILEMESSAGEHANDLER_H

#include "CodeX/System_Native.h"

// Include referenced enumerations.

#include "Cloddy/LogSeverity.h"

// Include referenced classes.

#include "Cloddy/FormattedMessageHandler.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { namespace Formats { class ILogMessageFormat; } } } }

// Declare class ::Cloddy::Core::Logging::Handlers::FileMessageHandler.

namespace Cloddy { namespace Core { namespace Logging { namespace Handlers
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Core::Logging;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Logging::Formats::ILogMessageFormat;
  
  /*!
   * @brief  An implementation of the ILogMessageHandler interface that writes log messages to a 
   *         file.
   */
  class FileMessageHandler : public FormattedMessageHandler
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of FileMessageHandler.
     * 
     * @param filePath <b>[not-null]</b>  Path to the log file.
     * @param format <b>[not-null]</b>  The log message format to use.
     * @param append \c true  to append new log message to an existing log file,\c false  to 
     * overwrite an existing log file.
     */
    FileMessageHandler(String filePath, ILogMessageFormat* format, bool append);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeUnmanaged();
    
    virtual void EmitLogMessage(String msg, LogSeverity severity);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FileMessageHandler> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x428ACFE2;
    
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
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("68B10832-8140-409F-8EDC-2EEBC1D91C82")
    
  private:

    /*!
     * @brief The log file.
     */
    void* pFile;
    
    NATIVE_BLOCK_END   ("68B10832-8140-409F-8EDC-2EEBC1D91C82")
  };
  
} } } } 

#endif
