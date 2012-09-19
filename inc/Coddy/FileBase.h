////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_FILEBASE_H
#define CLODDY_CORE_IO_FILES_FILEBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IFile.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { class IAsyncIO; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Streams { class IDataStream; } } } }
namespace Cloddy { namespace Core { namespace Logging { class ILogger; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class LocalFile; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class LocalFile_Async; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class LocalFile_Sync; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class LocalFileAsyncIO; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace Logging { class LoggingHelper; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::IO::Files::FileBase.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IAsyncIO;
  using Cloddy::Core::IO::Streams::IDataStream;
  using Cloddy::Core::Logging::ILogger;
  
  // Use referenced classes.
  
  using Cloddy::Core::Logging::LoggingHelper;
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base class for IFile implementations.
   */
  class FileBase : public Disposable, public virtual IFile
  {
    // Declare friend classes.
    
    friend class LocalFile;
    friend class LocalFile_Async;
    friend class LocalFile_Sync;
    friend class LocalFileAsyncIO;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetByteAlignment() = 0;
    
    virtual bool GetDeleteOnDispose();
    
    virtual void SetDeleteOnDispose(bool value);
    
    virtual Ptr<Path> GetFilePath();
    
    virtual bool IsReadOnly();
    
    virtual int64 GetLength();
    
    virtual void SetLength(int64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Flush() = 0;
    
    virtual Ptr<ByteBuffer> Map() = 0;
    
    virtual void Read(int64 offset, ByteBuffer* buffer, IAsyncIO* asyncIO) = 0;
    
    virtual Ptr<IDataStream> ToStream();
    
    virtual Ptr<IDataStream> ToStream(int32 bufferSize);
    
    virtual void Unmap() = 0;
    
    virtual void Write(int64 offset, ByteBuffer* buffer, IAsyncIO* asyncIO) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Asserts that this file is writeable.
     */
    void AssertWriteable();
    
    virtual void DisposeManaged();
    
    /*!
     * @brief  Set the length of this file to the given value.
     * 
     * @param length The new file length (will always be a multiple of #GetByteAlignment).
     */
    virtual void SetFileLength(int64 length) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The logger object of this class.
     */
    static const StaticPtr<ILogger> Logger;
    
    /*!
     * @brief  Shall this file be deleted upon disposal?
     */
    bool deleteOnDispose;
    
    /*!
     * @brief  The file path.
     */
    Ptr<Path> filePath;
    
    /*!
     * @brief  The current file length,in bytes.
     */
   int64 length;
    
    /*!
     * @brief  Is this a read only file?
     */
   bool readOnly;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    FileBase();
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
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
    public: typedef Ptr<FileBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3B0B1B19;
    
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
      if ((ptr = IFile::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
