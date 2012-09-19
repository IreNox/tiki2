////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASETBASE_H
#define CLODDY_API_DATASETS_DATASETBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IDataset.h"

// Include referenced classes.

#include "Cloddy/MapBase.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec2I; } } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3I; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleFormat; } } } }
namespace Cloddy { namespace API { namespace Util { class IMap; } } }
namespace Cloddy { namespace API { namespace Util { namespace Progress { class IOperation; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class DatasetRegion; } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class DatasetMetadata; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::DatasetBase.

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
  
  // Use referenced classes.
  
  using Cloddy::API::Datasets::Metadata::DatasetMetadata;
  using Cloddy::API::Util::MapBase;
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Abstract base class for IDataset implementations.
   * 
   * The following interface implementations are provided by this class:
   *   - #IsCompressed:default
   *   - #IsCompressionSupported:default
   *   - #GetMetadata:fixed
   *   - #GetUserData:fixed
   *   - #Compress:default
   *   - #CreateHeightmap():fixed
   *   - #CreateHeightmap(ISampleFormat*):fixed
   *   - #Decompress:default
   *   - #Get(DatasetRegion*):default
   *   - #Get(const Vec2I&):fixed
   *   - #Get(const Vec3I&):fixed
   *   - #Set(DatasetRegion*):default
   *   - #Set(const Vec2I&):fixed
   *   - #Set(const Vec3I&):fixed
   */
  class DatasetBase : public MapBase, public virtual IDataset
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetChannels() = 0;
    
    virtual bool IsCompressed();
    
    virtual bool IsCompressionSupported();
    
    virtual Ptr<DatasetMetadata> GetMetadata();
    
    virtual void* GetUserData();
    
    virtual void SetUserData(void* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IDataset> AppendChannels(IDataset* other);
    
    virtual Ptr<IOperation> Compress(Path* outputDatasetFilePath);
    
    virtual Ptr<IHeightmap> CreateHeightmap();
    
    virtual Ptr<IHeightmap> CreateHeightmap(ISampleFormat* sampleConverter);
    
    virtual Ptr<IOperation> Decompress(Path* outputDatasetFilePath);
    
    virtual Ptr<IOperation> Fill(ByteBuffer* sample);
    
    virtual void FlushMetadata() = 0;
    
    virtual void Get(DatasetRegion* region);
    
    virtual Ptr<ByteBuffer> Get(const Vec2I& xy);
    
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y) = 0;
    
    virtual Ptr<ByteBuffer> Get(const Vec3I& xyz);
    
    virtual Ptr<ByteBuffer> Get(int32 x, int32 y, int32 z) = 0;
    
    virtual void Set(DatasetRegion* region);
    
    virtual Ptr<ByteBuffer> Set(const Vec2I& xy);
    
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y);
    
    virtual Ptr<ByteBuffer> Set(const Vec3I& xyz);
    
    virtual Ptr<ByteBuffer> Set(int32 x, int32 y, int32 z);
    
    virtual Ptr<IDataset> SubChannels(int32 first, int32 count);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of DatasetBase.
     */
    DatasetBase();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DisposeManaged();
    
    /*!
     * @brief  This method is called when the dataset metadata is queried for the first time.
     * 
     * The default implementation simply returns a new instance of DatasetMetadata.
     * 
     * @return <b>[not-null]</b>  The loaded dataset metadata.
     * 
     * @see #GetMetadata
     */
    virtual Ptr<DatasetMetadata> LoadMetadata();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The metadata collection of this dataset.
     */
    Ptr<DatasetMetadata> metadata;
    
    /*!
     * @brief  The current user data object.
     */
    void* userData;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    void AssertSameSize(IMap* other);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5C44E6AA;
    
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
      if ((ptr = MapBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDataset::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
