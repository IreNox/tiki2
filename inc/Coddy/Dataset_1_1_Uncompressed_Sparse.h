////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASET_1_1_UNCOMPRESSED_SPARSE_H
#define CLODDY_API_DATASETS_DATASET_1_1_UNCOMPRESSED_SPARSE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MapType.h"

// Include referenced classes.

#include "Cloddy/Dataset.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class Dataset; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_1_Cube_Uncompressed_Sparse; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_1_Rect_Uncompressed_Sparse; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Dataset_1_1_Uncompressed_Sparse.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Util;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::Core::Collections::ISetConst;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Abstract base class for uncompressed sparse datasets.
   */
  class Dataset_1_1_Uncompressed_Sparse : public Dataset
  {
    // Declare friend classes.
    
    friend class Dataset;
    friend class Dataset_1_1_Cube_Uncompressed_Sparse;
    friend class Dataset_1_1_Rect_Uncompressed_Sparse;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The index of existing LOD blocks.
     */
    Array<int32> blockIndices;
    
    /*!
     * @brief  Buffer for dummy sample when writing to void areas.
     */
    Ptr<ByteBuffer> dummySample;
    
    /*!
     * @brief  Absolute datafile offset to first LOD block.
     */
    int64 firstBlockOffset;
    
    /*!
     * @brief  Dataset sample for void areas.
     */
    Ptr<ByteBuffer> voidSample;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DisposeManaged();
    
    /*!
     * @brief  Performs a lookup for the given LOD block.
     * 
     * @param blockIdx The LOD block index.
     * 
     * @return Index of the existing LOD block or \c -1  if the LOD block is not present in this 
     * sparse dataset.
     */
    int32 LookupLodBlock(int32 blockIdx);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The number of existing LOD blocks.
     */
    int32 blockCount;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Dataset_1_1_Uncompressed_Sparse.
     * 
     * @param datafile The datafile.
     */
    Dataset_1_1_Uncompressed_Sparse(IDatafile* datafile);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Initializes the given datafile for a new uncompressed sparse dataset.
     * 
     * @param datafile The datafile to use.
     * @param width Width of the dataset,in samples.
     * @param height Height of the dataset,in samples.
     * @param mapType The map type of the dataset.
     * @param channels Number of dataset channels.
     * @param blockIndices The set of existing LOD block indices.
     * @param voidSample Dataset sample to use for void areas.
     * 
     * @return <b>[not-null]</b>  The created datafile.
     */
    static Ptr<IDatafile> InitializeDatafile(IDatafile* datafile, int32 width, int32 height, MapType mapType, int32 channels, ISetConst<Prm<int32> >* blockIndices, ByteBuffer* voidSample);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Dataset_1_1_Uncompressed_Sparse> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3C45F015;
    
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
      if ((ptr = Dataset::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
