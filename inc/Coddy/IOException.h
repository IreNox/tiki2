////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_IOEXCEPTION_H
#define CLODDY_CORE_IO_IOEXCEPTION_H

#include "CodeX/System_Native.h"

// Include referenced enumerations.

#include "Cloddy/IOError.h"

// Include referenced classes.

#include "CodeX/CoreException.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::Core::IO::IOException.

namespace Cloddy { namespace Core { namespace IO
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::CoreException;
  
  /*!
   * @brief  An unexpected I/O error has occurred.
   */
  class IOException : public CoreException
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The well-known error that has caused this I/O exception.
     * 
     * @return The error code.
     */
    IOError GetError();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  A path string is not valid (eg. it contains invalid characters).
     * 
     * @param source The error source (see ErrorInfo::ErrorSource).
     * @param path The path string.
     * 
     * @return The ready-to-throw exception.
     */
    static IOException BadPath(String source, String path);
    
    /*!
     * @brief  An I/O error has occured during a file operation.
     * 
     * @param source The error source (see ErrorInfo::ErrorSource).
     * @param path The file path.
     * 
     * @return The ready-to-throw exception.
     */
    static IOException FileError(String source, Path* path);
    
    /*!
     * @brief  An I/O error has occured during a file operation.
     * 
     * @param source The error source (see ErrorInfo::ErrorSource).
     * @param path The file path.
     * @param osError The OS error code.
     * 
     * @return The ready-to-throw exception.
     */
    static IOException FileError(String source, Path* path, int32 osError);
    
    /*!
     * @brief  An I/O error has occured during a file operation.
     * 
     * @param source The error source (see ErrorInfo::ErrorSource).
     * @param path The file path.
     * @param error The well-known error code.
     * 
     * @return The ready-to-throw exception.
     */
    static IOException FileError(String source, Path* path, IOError error);
    
    /*!
     * @brief  An unexpected IO error has occurred while accessing a file.
     * 
     * @param source The error source (see ErrorInfo::ErrorSource).
     * @param filePath Path to the file being accessed.
     * @param message The error message.
     * 
     * @return The ready-to-throw exception.
     */
    static IOException FileError(String source, Path* filePath, String message);
    
    /*!
     * @brief  An unexpected IO error has occurred while accessing a network socket.
     * 
     * @param source The error source (see ErrorInfo::ErrorSource).
     * @param message The error message.
     * 
     * @return The ready-to-throw exception.
     */
    static IOException SocketError(String source, String message);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The well-known error that has caused this I/O exception.
     */
    IOError error;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of IOException.
     * 
     * @param source The error source (see ErrorInfo::ErrorSource).
     * @param error The well-known error code.
     * @param message The error message.
     */
    IOException(String source, IOError error, String message);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Translates the given OS error code into a well-known error.
     * 
     * @param errorCode The OS error code.
     * 
     * @return The well-known error.
     */
    static IOError GetIOError(int32 errorCode);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IOException> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x121AC796;
    
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
      if ((ptr = CoreException::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("D38ABC7D-67BD-4265-AF3A-FE4AA55A5042")
    
    // Nothing to do here.
    
    NATIVE_BLOCK_END   ("D38ABC7D-67BD-4265-AF3A-FE4AA55A5042")
  };
  
} } } 

#endif
