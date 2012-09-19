////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_DATAFILE_CACHED_H
#define CLODDY_API_DATAFILES_DATAFILE_CACHED_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Datafile.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class IFile; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datafiles { class Cache; } } }
namespace Cloddy { namespace API { namespace Datafiles { class DatafileFactory_Cached; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datafiles::Datafile_Cached.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ISetConst;
  using Cloddy::Core::IO::Files::IFile;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the IDatafile interface that uses a Cache object for accessing 
   *         the bytes of a file in the local filesystem.
   */
  class Datafile_Cached : public Datafile
  {
    // Declare friend classes.
    
    friend class Cache;
    friend class DatafileFactory_Cached;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<Path> GetFilePath();
    
    virtual bool IsReadOnly();
    
    virtual int64 GetLength();
    
    virtual void SetLength(int64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Begin();
    
    virtual void End();
    
    virtual void Flush();
    
    virtual void PreLoad(int64 offset, int32 count);
    
    virtual void PreLoad(ISetConst<Prm<int64> >* offsets, int32 count);
    
    virtual Ptr<ByteBuffer> Read(int64 offset, int32 bytes);
    
    virtual Ptr<ByteBuffer> Write(int64 offset, int32 bytes);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The cache of this cached datafile.
     */
    Ptr<Cache> cache;
    
    /*!
     * @brief  Index of the most recently accessed cache page.
     */
    int32 currentIndex;
    
    /*!
     * @brief  Index of the last source file page.
     */
    int64 lastSourceIndex;
    
    /*!
     * @brief  Current length of the datafile,in bytes.
     */
    int64 length;
    
    /*!
     * @brief  The page size of the cache.
     */
    int32 pageSize;
    
    /*!
     * @brief  The page size mask of the cache.
     */
    int32 pageSizeMask;
    
    /*!
     * @brief  The page size shift of the cache.
     */
    int32 pageSizeShift;
    
    /*!
     * @brief  The pages of the cache.
     */
    Ptr<ByteBuffer> pages;
    
    /*!
     * @brief  The underlying datafile.
     */
    Ptr<IFile> sourceFile;
    
    /*!
     * @brief  The source ID of this datafile in the cache.
     */
    int32 sourceId;
    
    /*!
     * @brief  Maximum dirty source page index (only used for flushing).
     */
    int64 sourceIndexDirtyMax;
    
    /*!
     * @brief  Minimum dirty source page index (only used for flushing).
     */
    int64 sourceIndexDirtyMin;
    
    /*!
     * @brief  Temporary buffer used for read/write accesses that straddle cache page boundaries.
     */
    Ptr<ByteBuffer> tempBuffer;
    
    /*!
     * @brief  Datafile byte offset of the temporary buffer or \c -1  if the temporary buffer 
     *         contains no data that needs to be written.
     */
    int64 tempBufferOffset;
    
    /*!
     * @brief  Index of the source page that contains valid data.
     */
    int64 upperValidIndex;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Datafile_Cached.
     * 
     * @param sourceFile The source file.
     * @param cache The cache to use.
     * @param newlyCreated Has the datafile been newly created?
     */
    Datafile_Cached(IFile* sourceFile, Cache* cache, bool newlyCreated);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Fills the temp buffer with data.
     * 
     * @param offset Datafile offset of source data.
     * @param bytes Length of source data.
     * @param sourceIndexFrom Index of first source data page.
     * @param sourceIndexTo Index of last source data page.
     * 
     * @return <b>[not-null]</b>  The filled temp buffer.
     */
    Ptr<ByteBuffer> FillTempBuffer(int64 offset, int32 bytes, int64 sourceIndexFrom, int64 sourceIndexTo);
    
    /*!
     * @brief  Flushes the temporary write buffer.
     */
    void FlushTempBuffer();
    
    /*!
     * @brief  Returns a temporary buffer of the given size.
     * 
     * @param size The buffer size.
     * 
     * @return The temporary buffer.
     */
    Ptr<ByteBuffer> GetTempBuffer(int32 size);
    
    /*!
     * @brief  Marks a cache page as dirty.
     * 
     * @param sourceIndex The source page index.
     * @param cacheIndex The cache page index.
     */
    void MarkAsDirty(int64 sourceIndex, int32 cacheIndex);
    
    /*!
     * @brief  Reads data from this source file.
     * 
     * @param cacheIndex Index of the cache page where to store the data.
     * @param sourceIndex Index of the source page to read from.
     */
    void ReadPage(int32 cacheIndex, int64 sourceIndex);
    
    /*!
     * @brief  Writes data to this source file.
     * 
     * @param cacheIndex Index of the cache page that holds the data.
     * @param sourceIndex Index of the source page to write to.
     */
    void WritePage(int32 cacheIndex, int64 sourceIndex);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Datafile_Cached> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF3FCD100;
    
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
      if ((ptr = Datafile::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
