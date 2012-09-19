////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_LOCALFILEASYNCIO_H
#define CLODDY_CORE_IO_FILES_LOCALFILEASYNCIO_H

#include "CodeX/System_Native.h"

// Include referenced interfaces.

#include "Cloddy/IAsyncIO.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class LocalFile_Async; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class LocalFile_Sync; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class LocalFileSystem; } } } }

// Declare class ::Cloddy::Core::IO::Files::LocalFileAsyncIO.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IAsyncIO;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Native implementation of the IAsyncIO interface.
   */
  class LocalFileAsyncIO : public Disposable, public virtual IAsyncIO
  {
    // Declare friend classes.
    
    friend class LocalFile_Async;
    friend class LocalFile_Sync;
    friend class LocalFileSystem;
    friend class RemoteFile;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 Finish();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeUnmanaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The file of the pending operation.
     */
    Ptr<LocalFile_Async> file;
    
    /*!
     * @brief  The file offset of this access.
     */
    int64 fileOffset;
    
    /*!
     * @brief  Is this a read (\c true )access or a write (\c false )access?
     */
    bool isReadOrWrite;
    
    /*!
     * @brief  The number of bytes to transfer.
     */
    int32 numberOfBytesToTransfer;
    
    /*!
     * @brief  The number of bytes that have been transferred.
     */
    int32 numberOfBytesTransferred;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of LocalFileAsyncIO.
     */
    LocalFileAsyncIO();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Initializes this pending I/O object for an asynchronous operation which is still 
     *         pending.
     * 
     * @param file The file.
     * @param fileOffset The file offset.
     * @param isReadOrWrite Read or write access?
     * @param numberOfBytesToTransfer The number of bytes to transfer.
     */
    void Asynchronous(LocalFile_Async* file, int64 fileOffset, bool isReadOrWrite, int32 numberOfBytesToTransfer);
    
    /*!
     * @brief  Initializes this pending I/O object for a synchronous operation which has already 
     *         finished.
     * 
     * @param numberOfBytesToTransfer The number of bytes to transfer.
     * @param numberOfBytesTransferred The number of bytes that have been transferred.
     */
    void Synchronous(int32 numberOfBytesToTransfer, int32 numberOfBytesTransferred);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LocalFileAsyncIO> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB11607E1;
    
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
      if ((ptr = IAsyncIO::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("BC48E0DE-CF00-48B8-BED7-8A1AA8A4F6B3")
    
#if defined(CODEX_PLATFORM_WINDOWS) 

  private:

    void* pOverlapped;

    void* hEvent;

#elif defined(CODEX_PLATFORM_LINUX) || defined(CODEX_PLATFORM_MAC)

  private:

    void* pAiocb;

#elif defined(CODEX_PLATFORM_WINCE)

  // Nothing to do here.

#else

#error Unsupported platform!

#endif
    
    NATIVE_BLOCK_END   ("BC48E0DE-CF00-48B8-BED7-8A1AA8A4F6B3")
  };
  
} } } } 

#endif
