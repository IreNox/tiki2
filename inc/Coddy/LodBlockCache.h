////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_LODBLOCKCACHE_H
#define CLODDY_API_DATASETS_LODBLOCKCACHE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class IDictionary; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Cube_Compressed; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Rect_Compressed; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::LodBlockCache.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IDictionary;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Caches LOD block data.
   */
  class LodBlockCache : public Disposable
  {
    // Declare friend classes.
    
    friend class Dataset_1_0_Cube_Compressed;
    friend class Dataset_1_0_Rect_Compressed;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Does the most recently accessed LOD block need to be loaded from disk?
     * 
     * @return \c true  if the LOD block needs to be loaded,\c false  if not.
     */
    bool ShallLoadBlock();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Accesses to the given LOD block.
     * 
     * @param blockIdx The LOD block index.
     * 
     * @return <b>[not-null]</b>  A ByteBuffer holding the LOD block bytes.
     */
    Ptr<ByteBuffer> AccessLodBlock(int32 blockIdx);
    
    /*!
     * @brief  Tries to access to the given LOD block.
     * 
     * @param blockIdx The LOD block index.
     * 
     * @return \c true  if the requested LOD block is not in the cache,\c false  if it is.
     */
    bool FailLodBlock(int32 blockIdx);
    
    /*!
     * @brief  Tries to accesses to the given LOD block and updates its LRU status when it is in 
     *         the cache.
     * 
     * @param blockIdx The LOD block index.
     */
    void HitLodBlock(int32 blockIdx);
    
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
     * @brief  The byte buffer that holds the LOD block cache.
     */
    Ptr<ByteBuffer> blockCache;
    
    /*!
     * @brief  Mapping from LOD block index to cache block index.
     */
    Ptr<IDictionary<Prm<int64>, Prm<int32> > > blockIdxToCacheIdx;
    
    /*!
     * @brief  Size of a LOD block,in bytes.
     */
    int32 blockSizeInBytes;
    
    /*!
     * @brief  Mapping from cache block index to LOD block index.
     */
    Array<int32> cacheIdxToBlockIdx;
    
    /*!
     * @brief  Head pointer of the LRU list of cache blocks.
     */
    int32 head;
    
    /*!
     * @brief  Next pointers of the LRU list of cache blocks.
     */
    Array<int32> next;
    
    /*!
     * @brief  Next pointers of the LRU list of cache blocks.
     */
    Array<int32> prev;
    
    /*!
     * @brief  Does the most recently accessed LOD block need to be loaded from disk?
     */
    bool shallLoadBlock;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of this class.
     * 
     * @param blockSizeInBytes Size of one LOD block,in bytes.
     * @param cacheMemory The amount of cache memory to use,in megabytes.
     */
    LodBlockCache(int32 blockSizeInBytes, int32 cacheMemory);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Marks the given cache LOD block as used (ie. it moves it to the tail of the LRU list 
     *         of cache blocks).
     * 
     * @param index The cache page.
     */
    void MarkAsUsed(int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LodBlockCache> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5A37481F;
    
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
