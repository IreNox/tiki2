////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_CACHE_H
#define CLODDY_API_DATAFILES_CACHE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class IDictionary; } } }
namespace Cloddy { namespace Core { namespace IO { class IAsyncIO; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datafiles { class Datafile; } } }
namespace Cloddy { namespace API { namespace Datafiles { class Datafile_Cached; } } }
namespace Cloddy { namespace API { namespace Datafiles { class IoStats; } } }
namespace CodeX { namespace System { class ByteBuffer; } }
namespace CodeX { namespace System { class Monitor; } }

// Declare class ::Cloddy::API::Datafiles::Cache.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IDictionary;
  using Cloddy::Core::IO::IAsyncIO;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  using CodeX::System::Monitor;
  
  /*!
   * @brief  The Cache class provides a page based cache in memory.
   */
  class Cache : public Disposable
  {
    // Declare friend classes.
    
    friend class Datafile;
    friend class Datafile_Cached;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Mapping from cache page index to asynchroneous I/O slot.
     */
    Array<int8> asyncPageToSlot;
    
    /*!
     * @brief  Asynchroneous I/O slots.
     */
    Array<Ptr<IAsyncIO> > asyncSlot;
    
    /*!
     * @brief  Index of I/O slot that will be used next.
     */
    int32 asyncSlotNext;
    
    /*!
     * @brief  Mapping from asynchroneous I/O slot to cache page index.
     */
    Array<int32> asyncSlotToPage;
    
    /*!
     * @brief  The cache memory,in megabytes.
     */
    int32 cacheMemory;
    
    /*!
     * @brief  Dirty flags per cache page.
     */
    Array<bool> dirty;
    
    /*!
     * @brief  Index of the cache page that represents the head of the LRU list.
     */
    int32 head;
    
    /*!
     * @brief  Mapping from cache page ID to cache page index.
     */
    Ptr<IDictionary<Prm<int64>, Prm<int32> > > idToIndex;
    
    /*!
     * @brief  Mapping from cache page index to cache page ID.
     */
    Array<int64> indexToId;
    
    /*!
     * @brief  The monitor object used for synchronization when accessing cached datafiles.
     */
    Ptr<Monitor> monitor;
    
    /*!
     * @brief  Next pointers of the LRU list for cache pages.
     */
    Array<int32> next;
    
    /*!
     * @brief  The page size.
     */
    int32 pageSize;
    
    /*!
     * @brief  The cache page buffer.
     */
    Ptr<ByteBuffer> pages;
    
    /*!
     * @brief  Previous pointers of the LRU list for cache pages.
     */
    Array<int32> prev;
    
    /*!
     * @brief  Counts the number of source files that are currently associated with this cache.
     */
    int32 sourceFileCount;
    
    /*!
     * @brief  The source datafiles,indexed by source IDs.
     */
    Array<Ptr<Datafile_Cached> > sourceFiles;
    
    /*!
     * @brief  The I/O information object.
     */
    Ptr<IoStats> stats;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Cache.
     * 
     * @param cacheMemory The cache size,in megabytes.
     * @param pageSize The page size.
     * @param stats The IoStats object to use.
     */
    Cache(int32 cacheMemory, int32 pageSize, IoStats* stats);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Accesses a datafile page.
     * 
     * @param sourceId The source ID of the datafile that contains the page to access.
     * @param sourceIndex The datafile page index.
     * @param cacheIndex The last known cache page index or \c 0  if unknown.
     * 
     * @return The cache page index.
     */
    int32 AccessPage(int32 sourceId, int64 sourceIndex, int32 cacheIndex);
    
    /*!
     * @brief  Allocates a source ID in this cache for the given source file.
     * 
     * @param sourceFile The source file.
     * 
     * @return <b>[1..65535]</b>  The source ID.
     */
    int32 AllocateSourceId(Datafile_Cached* sourceFile);
    
    /*!
     * @brief  Begins asynchroneous I/O for the given cache page.
     * 
     * @param page The cache page index.
     * 
     * @return <b>[not-null]</b>  The asynchroneous I/O handle object.
     */
    Ptr<IAsyncIO> BeginIO(int32 page);
    
    /*!
     * @brief  Tries to access to given page and loads it if necessary.
     * 
     * @param sourceId The source ID of the datafile that contains the page to access..
     * @param sourceIndex The datafile page index.
     */
    void FailPage(int32 sourceId, int64 sourceIndex);
    
    /*!
     * @brief  Finishes all asynchroneous I/O.
     */
    void FinishIO();
    
    /*!
     * @brief  Finishes asynchroneous I/O for the given cache page.
     * 
     * @param page The cache page index.
     */
    void FinishIO(int32 page);
    
    /*!
     * @brief  Flushes the given cache page to disk and clears the dirty flag.
     * 
     * @param cacheIndex The cache page index.
     */
    void FlushDirtyPage(int32 cacheIndex);
    
    /*!
     * @brief  Flushes a range of dirty cache pages.
     * 
     * @param sourceId The datafile source ID.
     * @param sourceIndexFrom Index of first cache page to flush.
     * @param count The number of cache pages to flush.
     */
    void FlushDirtyPages(int32 sourceId, int64 sourceIndexFrom, int64 count);
    
    /*!
     * @brief  Tries to access to given page and updates its LRU status if it does not need to be 
     *         loaded from disk.
     * 
     * @param sourceId The source ID of the datafile that contains the page to access..
     * @param sourceIndex The datafile page index.
     */
    void HitPage(int32 sourceId, int64 sourceIndex);
    
    /*!
     * @brief  Moves the given cache page to the head of the LRU list.
     * 
     * @param index The cache page index.
     */
    void LruToHead(int32 index);
    
    /*!
     * @brief  Moves the given cache page to the tail of the LRU list.
     * 
     * @param index The cache page index.
     */
    void LruToTail(int32 index);
    
    /*!
     * @brief  Releases a range of source file pages.
     * 
     * @param sourceId The source ID.
     * @param sourceIndex Index of first source file page to release.
     * @param count Number of source file pages to release.
     */
    void ReleasePages(int32 sourceId, int64 sourceIndex, int64 count);
    
    /*!
     * @brief  Releases a source ID.
     * 
     * @param sourceId The source ID.
     */
    void ReleaseSourceId(int32 sourceId);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Cache> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC414AD19;
    
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
      return (void*) 0;
    }
  };
  
} } } 

#endif
