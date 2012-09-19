////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_LOCALFILESYSTEM_H
#define CLODDY_CORE_IO_FILES_LOCALFILESYSTEM_H

#include "CodeX/System_Native.h"

// Include referenced enumerations.

#include "Cloddy/FileHint.h"

// Include referenced interfaces.

#include "Cloddy/IFileSystem.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class IFile; } } } }
namespace Cloddy { namespace Core { namespace IO { class IAsyncIO; } } }
namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace Logging { class LoggingHelper; } } }

// Declare class ::Cloddy::Core::IO::Files::LocalFileSystem.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IAsyncIO;
  using Cloddy::Core::Logging::ILogger;
  
  // Use referenced classes.
  
  using Cloddy::Core::Logging::LoggingHelper;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  An implementation of the IFileSystem interface for the local filesystem.
   */
  class LocalFileSystem : public Disposable, public virtual IFileSystem
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Singleton instance of this class.
     */
    static const StaticPtr<IFileSystem> Instance;
    
    virtual Ptr<Path> GetDirectory();
    
    virtual void SetDirectory(Path* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IFile> Create(Path* path, int64 length, FileHint hint);
    
    virtual void Create(Path* path);
    
    virtual Ptr<IAsyncIO> CreateAsyncIO();
    
    virtual void Delete(Path* path);
    
    virtual bool DirectoryExists(Path* path);
    
    virtual bool FileExists(Path* path);
    
    virtual Ptr<Path> GetCanonicalPath(Path* path);
    
    virtual Ptr<IFile> Open(Path* path, bool readOnly, FileHint hint);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The logger object of this class.
     */
    static const StaticPtr<ILogger> Logger;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of LocalFileSystem.
     */
    LocalFileSystem();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Checks if the given path string contains invalid characters.
     * 
     * @param path The path string.
     * 
     * @return \c true  if the path string is valid,\c false  if it contains at least one invalid 
     * character.
     */
    static bool CheckInvalidPathChars(String path);
    
    /*!
     * @brief  Checks if the given file hint value is supported by the underlying platform.
     * 
     * @param fileHint The requested file hint.
     * 
     * @return The file hint that is supported by the underlying platform.
     */
    FileHint CheckFileHint(FileHint fileHint);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field Instance.
     */
    static Object* StaticInitializer_Instance();
    
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
    public: typedef Ptr<LocalFileSystem> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3327BD0E;
    
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
      if ((ptr = IFileSystem::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("111859A1-AFE6-403E-972F-C57620D2F975")
    
#if defined(CODEX_PLATFORM_WINCE)

    /*!
     * @brief The current directory.
     */
    Ptr<Path> currentDirectory;

#else

  // Nothing to do here.

#endif
    
    NATIVE_BLOCK_END   ("111859A1-AFE6-403E-972F-C57620D2F975")
  };
  
} } } } 

#endif
