////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASET_1_0_RECT_UNCOMPRESSED_H
#define CLODDY_API_DATASETS_DATASET_1_0_RECT_UNCOMPRESSED_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Dataset.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IOperation; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class Dataset; } } }
namespace Cloddy { namespace API { namespace Datasets { class DatasetBulkGet_1_0_Uncompressed; } } }
namespace Cloddy { namespace API { namespace Datasets { class DatasetRegion; } } }
namespace Cloddy { namespace API { namespace Datasets { class LodBlockPartitioning2D; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Dataset_1_0_Rect_Uncompressed.

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
  class Dataset_1_0_Rect_Uncompressed : public Dataset
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
    
    virtual void Get(DatasetRegion* region);
    
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y, int32 z);
    
    virtual void Set(DatasetRegion* region);
    
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y);
    
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y, int32 z);
    
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
     * @brief  Logarithm of base two of the squared LOD partitioning block size.
     */
    int32 blockSizeShift2;
    
    /*!
     * @brief  Helper object for bulk get operations.
     */
    Ptr<DatasetBulkGet_1_0_Uncompressed> bulkGet;
    
    /*!
     * @brief  Number of dataset channels.
     */
    int32 channels;
    
    /*!
     * @brief  The LOD block partitioning used to arrange dataset samples.
     */
    Ptr<LodBlockPartitioning2D> partitioning;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Dataset_1_0_Rect_Uncompressed.
     * 
     * @param datafile The underlying datafile.
     */
    Dataset_1_0_Rect_Uncompressed(IDatafile* datafile);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Initializes the given datafile for a new uncompressed rectangular dataset.
     * 
     * @param datafile The datafile to use.
     * @param width Width of the dataset,in samples.
     * @param height Height of the dataset,in samples.
     * @param channels Number of dataset channels.
     * 
     * @return <b>[not-null]</b>  The created datafile.
     */
    static Ptr<IDatafile> InitializeDatafile(IDatafile* datafile, int32 width, int32 height, int32 channels);
    
    /*!
     * @brief  Computes the storage offset of the given dataset sample.
     * 
     * @param x X-coordinate of dataset sample.
     * @param y Y-coordinate of dataset sample.
     * 
     * @return Storage offset,beginning at \c 0 ,in bytes.
     */
    int64 GetOffset(int32 x, int32 y);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Dataset_1_0_Rect_Uncompressed> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x9E127B32;
    
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
