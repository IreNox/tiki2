////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASETBULKGET_1_0_UNCOMPRESSED_H
#define CLODDY_API_DATASETS_DATASETBULKGET_1_0_UNCOMPRESSED_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/MapField.h"

// Include referenced interfaces.

#include "Cloddy/ILodBlock2DCallback.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Cube_Uncompressed; } } }
namespace Cloddy { namespace API { namespace Datasets { class Dataset_1_0_Rect_Uncompressed; } } }
namespace Cloddy { namespace API { namespace Datasets { class DatasetRegion; } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::DatasetBulkGet_1_0_Uncompressed.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Util::MapField;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  class DatasetBulkGet_1_0_Uncompressed : public virtual ILodBlock2DCallback
  {
    // Declare friend classes.
    
    friend class Dataset_1_0_Cube_Uncompressed;
    friend class Dataset_1_0_Rect_Uncompressed;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void ProcessLodBlock(int32 blockIdx, int32 blockX, int32 blockY, int32 blockStep, int32 blockSubX1, int32 blockSubY1, int32 blockSubX2, int32 blockSubY2, int32 blockSubStep);
    
    virtual void ProcessLodBlockBegin(int32 face, int32 width, int32 height, int32 blockSize, int32 blockCount);
    
    virtual void ProcessLodBlockEnd();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The cubemap LOD block index offset.
     */
    int32 blockIdxOffset;
    
    /*!
     * @brief  Logarithm of LOD block size,multiplied with 2.
     */
    int32 blockSizeShift2;
    
    /*!
     * @brief  The channels per sample.
     */
    int32 channels;
    
    /*!
     * @brief  Fetching from a cubemap?
     */
    bool cubemap;
    
    /*!
     * @brief  The datafile.
     */
    Ptr<IDatafile> datafile;
    
    /*!
     * @brief  The map field region.
     */
    MapField field;
    
    /*!
     * @brief  The output sample buffer.
     */
    Ptr<ByteBuffer> samples;
    
    int32 samplesStepShift;
    
    /*!
     * @brief  The distance between adjacent scanlines in #samples,in bytes.
     */
    int32 samplesStride;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    DatasetBulkGet_1_0_Uncompressed(IDatafile* datafile, bool cubemap, int32 channels);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    void Prepare(DatasetRegion* region);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBulkGet_1_0_Uncompressed> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6E85F323;
    
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
      if ((ptr = ILodBlock2DCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
