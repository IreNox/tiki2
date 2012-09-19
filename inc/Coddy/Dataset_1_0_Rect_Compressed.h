////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASET_1_0_RECT_COMPRESSED_H
#define CLODDY_API_DATASETS_DATASET_1_0_RECT_COMPRESSED_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Dataset.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Compression { class ICompressionCodec; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IOperation; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class Dataset; } } }
namespace Cloddy { namespace API { namespace Datasets { class LodBlockCache; } } }
namespace Cloddy { namespace API { namespace Datasets { class LodBlockPartitioning2D; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Dataset_1_0_Rect_Compressed.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Datasets::Compression::ICompressionCodec;
  using Cloddy::API::Util::Progress::IOperation;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IDataset for the proprietary CloddySDK dataset format.
   */
  class Dataset_1_0_Rect_Compressed : public Dataset
  {
    // Declare friend classes.
    
    friend class Dataset;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IOperation> Compress(Path* outputDatasetFilePath);
    
    virtual Ptr<IOperation> Decompress(Path* outputDatasetFilePath);
    
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y);
    
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y, int32 z);
    
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
     * @brief  Logarithm of base two of the LOD partitioning block size.
     */
    int32 blockSizeShift;
    
    /*!
     * @brief  The cache for decompressed LOD blocks.
     */
    Ptr<LodBlockCache> cache;
    
    /*!
     * @brief  Number of dataset channels.
     */
    int32 channels;
    
    /*!
     * @brief  The used compression codec.
     */
    Ptr<ICompressionCodec> codec;
    
    /*!
     * @brief  File offset per compressed LOD block.
     */
    Array<int64> compressedBlockOffsets;
    
    /*!
     * @brief  The LOD block partitioning used to arrange dataset samples.
     */
    Ptr<LodBlockPartitioning2D> partitioning;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Dataset_1_0_Rect_Compressed.
     * 
     * @param datafile The underlying datafile.
     */
    Dataset_1_0_Rect_Compressed(IDatafile* datafile);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Dataset_1_0_Rect_Compressed> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7717AD55;
    
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
