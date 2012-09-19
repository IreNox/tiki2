////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASET_INDEX_1_0_H
#define CLODDY_API_DATASETS_DATASET_INDEX_1_0_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IBeginEnd.h"
#include "Cloddy/IFlushable.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class, class> class ISortedDictionary; } } }

// Declare class ::Cloddy::API::Datasets::Dataset_Index_1_0.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Util::IBeginEnd;
  using Cloddy::Core::Collections::ISortedDictionary;
  using Cloddy::Core::IO::IFlushable;
  
  // Use referenced classes.
  
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Helper class that provides access to a dataset block index file.
   */
  class Dataset_Index_1_0 : public Disposable, public virtual IBeginEnd, public virtual IFlushable
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Begin();
    
    virtual void End();
    
    virtual void Flush();
    
    /*!
     * @brief  Performs a lookup for the given LOD block.
     * 
     * @param blockIdx The LOD block index.
     * @param write Allocate new block if not already existent?
     * 
     * @return Index of the existing LOD block,\c -1  if the LOD block is not present in the 
     * dataset index or \c -1-idx  if the LOD block has been newly allocated (where \c idx  
     * represents the LOD block index).
     */
    int32 LookupLodBlock(int32 blockIdx, bool write);
    
    /*!
     * @brief  Performs a lookup for the given LOD block,allocating a new one if necessary.
     * 
     * @param blockIdx The LOD block index.
     * 
     * @return Index of the existing LOD block or \c -1-idx  if the LOD block has been newly 
     * allocated (where \c idx  represents the LOD block index).
     */
    int32 LookupWrite(int32 blockIdx);
    
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
     * @brief  Cache of LOD blocks.
     */
    Ptr<ISortedDictionary<Prm<int32>, Prm<int32> > > cache;
    
    /*!
     * @brief  The current chunk count.
     */
    int32 chunkCount;
    
    /*!
     * @brief  The datafile that stored the dataset index.
     */
    Ptr<IDatafile> datafile;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Dataset_Index_1_0.
     * 
     * @param datafile The datafile that stores the index.
     * @param cacheSize Size of the LOD block index cache.
     */
    Dataset_Index_1_0(IDatafile* datafile, int32 cacheSize);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Allocates a new chunk at the end of the dataset index file.
     * 
     * @return <b>[>=0]</b>  The chunk index.
     */
    int32 AllocateChunk();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Dataset_Index_1_0> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA4E860D3;
    
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
      if ((ptr = IBeginEnd::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IFlushable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
