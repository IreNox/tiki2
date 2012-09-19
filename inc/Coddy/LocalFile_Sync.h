////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_FILES_LOCALFILE_SYNC_H
#define CLODDY_CORE_IO_FILES_LOCALFILE_SYNC_H

#include "CodeX/System_Native.h"

// Include referenced classes.

#include "Cloddy/LocalFile.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { class IAsyncIO; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class LocalFileSystem; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::Core::IO::Files::LocalFile_Sync.

namespace Cloddy { namespace Core { namespace IO { namespace Files
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::IAsyncIO;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the IFile interface for files in the local filesystem.
   * 
   * File access is performed via FileHint::FileHint_BufferedSynchronous semantics.
   */
  class LocalFile_Sync : public LocalFile
  {
    // Declare friend classes.
    
    friend class LocalFileSystem;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetByteAlignment();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Flush();
    
    virtual void Read(int64 offset, ByteBuffer* buffer, IAsyncIO* asyncIO);
    
    virtual void Write(int64 offset, ByteBuffer* buffer, IAsyncIO* asyncIO);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new file object.
     * 
     * @param path Path to the file.
     * @param lengthOp The action to perform:\c -2  for opening an existing file as read only,
     * \c -1  for opening an existing file as read/write and <c>>=0</c> for creating a new file of 
     * the given initial length (in bytes).
     */
    LocalFile_Sync(Path* path, int64 lengthOp);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LocalFile_Sync> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x33CD2865;
    
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
      if ((ptr = LocalFile::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
    
    // ---------------------------------------------------------------------------------------------
    // Native code
    // ---------------------------------------------------------------------------------------------
    
    NATIVE_BLOCK_BEGIN ("0AC3AD15-DCA2-4B40-9676-FB7E044AA550")
    
    // Nothing to do here.
    
    NATIVE_BLOCK_END   ("0AC3AD15-DCA2-4B40-9676-FB7E044AA550")
  };
  
} } } } 

#endif
