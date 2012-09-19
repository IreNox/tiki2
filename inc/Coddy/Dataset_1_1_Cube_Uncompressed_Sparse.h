////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASET_1_1_CUBE_UNCOMPRESSED_SPARSE_H
#define CLODDY_API_DATASETS_DATASET_1_1_CUBE_UNCOMPRESSED_SPARSE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Dataset_1_1_Uncompressed_Sparse.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IOperation; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class Dataset; } } }
namespace Cloddy { namespace API { namespace Datasets { class LodBlockPartitioning2D; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Dataset_1_1_Cube_Uncompressed_Sparse.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Util::Progress::IOperation;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IDataset for the proprietary CloddySDK dataset format.
   */
  class Dataset_1_1_Cube_Uncompressed_Sparse : public Dataset_1_1_Uncompressed_Sparse
  {
    // Declare friend classes.
    
    friend class Dataset;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool IsMutable();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IOperation> Compress(Path* outputDatasetFilePath);
    
    virtual Ptr<IOperation> Decompress(Path* outputDatasetFilePath);
    
    virtual Ptr<IOperation> Fill(ByteBuffer* sample);
    
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y);
    
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y, int32 z);
    
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y, int32 z);
    
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y);
    
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
     * @brief  Number of LOD blocks.
     */
    int32 blockCount;
    
    /*!
     * @brief  Size of a single LOD block,in bytes.
     */
    int32 blockSizeInBytes;
    
    /*!
     * @brief  Number of dataset channels.
     */
    int32 channels;
    
    /*!
     * @brief  The LOD block partitioning.
     */
    Ptr<LodBlockPartitioning2D> partitioning;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Dataset_1_1_Cube_Uncompressed_Sparse.
     * 
     * @param datafile The underlying datafile.
     */
    Dataset_1_1_Cube_Uncompressed_Sparse(IDatafile* datafile);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the storage offset of the given dataset sample.
     * 
     * @param x X-coordinate of dataset sample.
     * @param y Y-coordinate of dataset sample.
     * @param z Z-coordinate of dataset sample.
     * 
     * @return The linear storage offset or \c -1  if the dataset does not contain the sample.
     */
    int64 GetOffset(int32 x, int32 y, int32 z);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Dataset_1_1_Cube_Uncompressed_Sparse> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xBA001A0F;
    
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
      if ((ptr = Dataset_1_1_Uncompressed_Sparse::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
