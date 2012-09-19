////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_IDATASET_H
#define CLODDY_API_DATASETS_IDATASET_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMap.h"
#include "Cloddy/IUserData.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec2I; } } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3I; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleFormat; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IOperation; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class DatasetRegion; } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class DatasetMetadata; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare interface ::Cloddy::API::Datasets::IDataset.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::API::Heightmaps::SampleFormats::ISampleFormat;
  using Cloddy::API::Util::IMap;
  using Cloddy::API::Util::Progress::IOperation;
  using Cloddy::Kernel::IUserData;
  
  // Use referenced classes.
  
  using Cloddy::API::Datasets::Metadata::DatasetMetadata;
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Represents a general purpose terrain dataset.
   */
  class NO_VTABLE IDataset : public virtual IMap, public virtual IUserData
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of channels.
     * 
     * Each channel is an 8-bit value.
     * 
     * @return <b>[>0]</b>  The number of dataset channels.
     */
    virtual int32 GetChannels() = 0;
    
    /*!
     * @brief  Is this a compressed dataset?
     * 
     * @return \c true  if this dataset is compressed,\c false  if it is uncompressed.
     */
    virtual bool IsCompressed() = 0;
    
    /*!
     * @brief  Does this dataset implementation support compression?
     * 
     * @return \c true  if compression is supported,\c false  if not.
     * 
     * @see #Compress
     * @see #Decompress
     */
    virtual bool IsCompressionSupported() = 0;
    
    /*!
     * @brief  Returns the metadata of this dataset.
     * 
     * @return <b>[not-null]</b>  The metadata collection.
     */
    virtual Ptr<DatasetMetadata> GetMetadata() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Appends the channels of the given dataset to the channels of this dataset.
     * 
     * The returned dataset will use the same meta data collection as this dataset.
     * 
     * @param other <b>[not-null]</b>  The other dataset.
     * 
     * @return <b>[not-null]</b>  The resulting dataset.
     */
    virtual Ptr<IDataset> AppendChannels(IDataset* other) = 0;
    
    /*!
     * @brief  Compresses this dataset.
     * 
     * @param outputDatasetFilePath <b>[not-null]</b>  The output dataset file path.
     * 
     * @return An IOperation object that performs the actual work or \c null  if this dataset 
     * implementation does not support compression.
     * 
     * @see #IsCompressionSupported
     */
    virtual Ptr<IOperation> Compress(Path* outputDatasetFilePath) = 0;
    
    /*!
     * @brief  Creates a heightmap based on the samples of this dataset.The metadata information 
     *         will be used to create an appropriate.sample format.
     * 
     * The user data object set for this IDataset object (see IUserData::GetUserData)will be set 
     * for the created IHeightmap object as well.
     * 
     * @return <b>[not-null]</b>  The created heightmap.
     */
    virtual Ptr<IHeightmap> CreateHeightmap() = 0;
    
    /*!
     * @brief  Creates a heightmap based on the samples of this dataset.
     * 
     * The user data object set for this IDataset object (see IUserData::GetUserData)will be set 
     * for the created IHeightmap object as well.
     * 
     * @param sampleConverter <b>[not-null]</b>  The sample format to use.
     * 
     * @return <b>[not-null]</b>  The created heightmap.
     */
    virtual Ptr<IHeightmap> CreateHeightmap(ISampleFormat* sampleConverter) = 0;
    
    /*!
     * @brief  Decompresses this dataset.
     * 
     * @param outputDatasetFilePath <b>[not-null]</b>  The output dataset file path.
     * 
     * @return An IOperation object that performs the actual work or \c null  if this dataset 
     * implementation does not support compression.
     * 
     * @see #IsCompressionSupported
     */
    virtual Ptr<IOperation> Decompress(Path* outputDatasetFilePath) = 0;
    
    /*!
     * @brief  Fills the entire dataset with the given sample.
     * 
     * @param sample <b>[not-null]</b>  The sample to use for filling the dataset.
     * 
     * @return An IOperation object that performs the actual work or \c null  if this dataset 
     * implementation is not mutable.
     */
    virtual Ptr<IOperation> Fill(ByteBuffer* sample) = 0;
    
    /*!
     * @brief  Flushes the metadata of this dataset to the persistent store.
     */
    virtual void FlushMetadata() = 0;
    
    /*!
     * @brief  Returns a region of this dataset in a single bulk operation.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * @param region <b>[not-null]</b>  The output dataset region.
     */
    virtual void Get(DatasetRegion* region) = 0;
    
    /*!
     * @brief  Reads a sample from the dataset.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * @param xy Coordinates of sample.
     * 
     * @return A byte buffer holding the sample.
     */
    virtual Ptr<ByteBuffer> Get(const Vec2I& xy) = 0;
    
    /*!
     * @brief  Reads a sample from the dataset.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * 
     * @return A byte buffer holding the sample.
     */
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y) = 0;
    
    /*!
     * @brief  Reads a sample from the dataset.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * @param xyz Coordinates of sample.
     * 
     * @return A byte buffer holding the sample.
     */
    virtual Ptr<ByteBuffer> Get(const Vec3I& xyz) = 0;
    
    /*!
     * @brief  Reads a sample from the dataset.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param z Z-coordinate of sample.
     * 
     * @return A byte buffer holding the sample.
     */
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y, int32 z) = 0;
    
    /*!
     * @brief  Updates a region of this dataset in a single bulk operation.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * If this dataset is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param region <b>[not-null]</b>  The dataset region.
     */
    virtual void Set(DatasetRegion* region) = 0;
    
    /*!
     * @brief  Writes a sample to the dataset.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * If this dataset is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param xy Coordinates of sample.
     * 
     * @return A byte buffer holding the sample.
     */
    virtual Ptr<ByteBuffer> Set(const Vec2I& xy) = 0;
    
    /*!
     * @brief  Writes a sample to the dataset.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * If this dataset is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * 
     * @return A byte buffer holding the sample.
     */
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y) = 0;
    
    /*!
     * @brief  Writes a sample to the dataset.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * If this dataset is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param xyz Coordinates of sample
     * 
     * @return A byte buffer holding the sample.
     */
    virtual Ptr<ByteBuffer> Set(const Vec3I& xyz) = 0;
    
    /*!
     * @brief  Writes a sample to the dataset.
     * 
     * All calls to this method must be wrapped in IBeginEnd::Begin /IBeginEnd::End 
     * 
     * If this dataset is immutable (see IMap::IsMutable),the method does nothing and returns 
     * silently.
     * 
     * @param x X-coordinate of sample.
     * @param y Y-coordinate of sample.
     * @param z Z-coordinate of sample.
     * 
     * @return A byte buffer holding the sample.
     */
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y, int32 z) = 0;
    
    /*!
     * @brief  Extracts a range of subchannels from this dataset.
     * 
     * The returned dataset will use the same meta data collection as this dataset.
     * 
     * @param first <b>[0..#GetChannels-1]</b>  Index of first dataset channel to extract.
     * @param count <b>[1..#GetChannels-first]</b>  Number of dataset channels to extract.
     * 
     * @return <b>[not-null]</b>  The resulting dataset.
     */
    virtual Ptr<IDataset> SubChannels(int32 first, int32 count) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDataset> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEC501914;
    
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
      if ((ptr = IMap::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IUserData::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
