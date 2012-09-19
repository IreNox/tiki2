////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_LOCALFILE_H
#define CLODDY_CORE_IO_FILES_LOCALFILE_H

#include "CodeX/System_Native.h"

// Include referenced classes.

#include "Cloddy/FileBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Logging { class LoggingHelper; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::IO::Files::LocalFile.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Logging::ILogger;
  
  // Use referenced classes.
  
  using Cloddy::Core::Logging::LoggingHelper;
  using CodeX::System::ByteBuffer;
  
  class LocalFile : public FileBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Flush();
    
    virtual Ptr<ByteBuffer> Map();
    
    virtual void Unmap();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Asserts that the given ByteBuffer has less than <c>2^31</c> remaining bytes.
     * 
     * @param buffer The byte buffer.
     */
    static void AssertLessThan2GbRemaining(ByteBuffer* buffer);
    
    virtual void DisposeManaged();
    
    virtual void DisposeUnmanaged();
    
    virtual void SetFileLength(int64 length);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The logger object of this class.
     */
    static const StaticPtr<ILogger> Logger;
    
    /*!
     * @brief  The currently mapped file data.
     */
    Ptr<ByteBuffer> mapped;
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field Logger.
     */
    static Object* StaticInitializer_Logger();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LocalFile> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x181A0329;
    
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
      if ((ptr = FileBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("C72ED4F5-670E-42C0-8014-ABFE0EAE1F07")
    
    friend class LocalFileAsyncIO;

#if defined(CODEX_PLATFORM_WINDOWS) || defined(CODEX_PLATFORM_WINCE)

    /*!
     * @brief The native file handle.
     */
    void* hFile;

    /*!
     * @brief The file mapping object.
     */
    void* hFileMapping;

    /*!
     * @brief The mapped file view.
     */
    void* hFileView;

#elif defined(CODEX_PLATFORM_LINUX) || defined(CODEX_PLATFORM_MAC)

    /*!
     * @brief The native file handle.
     */
    int hFile;

#else

#error Unsupported platform!

#endif
    
    NATIVE_BLOCK_END   ("C72ED4F5-670E-42C0-8014-ABFE0EAE1F07")
  };
  
} } } } 

#endif
