////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_DATASET_H
#define CLODDY_API_DATASETS_DATASET_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DatasetBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace API { namespace Datasets { class IDataset; } } }
namespace Cloddy { namespace API { namespace Util { class IMapRegion; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datasets { class DatasetHeader; } } }
namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class DatasetMetadata; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Dataset.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datafiles::IDatafile;
  using Cloddy::API::Util::IMapRegion;
  
  // Use referenced classes.
  
  using Cloddy::API::Datasets::Metadata::DatasetMetadata;
  using Cloddy::Core::IO::Files::Path;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  Represents a terrain dataset.
   */
  class Dataset : public DatasetBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The amount of cache memory to use for subsequently opened compressed datasets.
     * 
     * The default value is \c 32 .
     * 
     * @return <b>[>0]</b>  The amount of cache memory to use,in megabytes.
     */
    static int32 GetCompressedCacheMemory();
    
    /*!
     * @brief  The amount of cache memory to use for subsequently opened compressed datasets.
     * 
     * The default value is \c 32 .
     * 
     * @param value <b>[>0]</b>  The amount of cache memory to use,in megabytes.
     */
    static void SetCompressedCacheMemory(int32 value);
    
    virtual int32 GetChannels();
    
    virtual bool IsCompressed();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new uncompressed cube dataset.
     * 
     * @param filePath <b>[not-null]</b>  Path to the datasets datafile.
     * @param size <b>[pow2+1]</b>  Size of the dataset;must be a power of two plus one.
     * @param channels <b>[>0]</b>  The number of 8-bit dataset channels.
     * 
     * @return The created IDataset.
     */
    static Ptr<IDataset> CreateCube(Path* filePath, int32 size, int32 channels);
    
    /*!
     * @brief  Creates a new uncompressed cube dataset.
     * 
     * @param datafile <b>[not-null]</b>  The datafile to use for the dataset.
     * @param size <b>[pow2+1]</b>  Size of the dataset;must be a power of two plus one.
     * @param channels <b>[>0]</b>  The number of 8-bit dataset channels.
     * 
     * @return The created IDataset.
     */
    static Ptr<IDataset> CreateCube(IDatafile* datafile, int32 size, int32 channels);
    
    /*!
     * @brief  Creates a new uncompressed cube sparse dataset.
     * 
     * @param filePath <b>[not-null]</b>  Path to the dataset datafile.
     * @param size <b>[pow2+1]</b>  Size of the dataset;must be a power of two plus one.
     * @param channels <b>[>0]</b>  The number of 8-bit dataset channels.
     * @param voidSample <b>[not-null]</b>  The dataset sample to use for void areas.
     * @param dataRegion <b>[not-null]</b>  The regions that contain data.
     * 
     * @return The created IDataset.
     */
    static Ptr<IDataset> CreateCubeSparse(Path* filePath, int32 size, int32 channels, ByteBuffer* voidSample, IMapRegion* dataRegion);
    
    /*!
     * @brief  Creates a new uncompressed cube sparse dataset.
     * 
     * @param datafile <b>[not-null]</b>  The dataset datafile.
     * @param size <b>[pow2+1]</b>  Size of the dataset;must be a power of two plus one.
     * @param channels <b>[>0]</b>  The number of 8-bit dataset channels.
     * @param voidSample <b>[not-null]</b>  The dataset sample to use for void areas.
     * @param dataRegion <b>[not-null]</b>  The regions that contain data.
     * 
     * @return The created IDataset.
     */
    static Ptr<IDataset> CreateCubeSparse(IDatafile* datafile, int32 size, int32 channels, ByteBuffer* voidSample, IMapRegion* dataRegion);
    
    /*!
     * @brief  Creates a new uncompressed rectangular dataset.
     * 
     * @param filePath <b>[not-null]</b>  Path to the dataset datafile.
     * @param width <b>[>0]</b>  Width of the dataset.
     * @param height <b>[>0]</b>  Height of the dataset.
     * @param channels <b>[>0]</b>  The number of 8-bit dataset channels.
     * 
     * @return The created IDataset.
     */
    static Ptr<IDataset> CreateRect(Path* filePath, int32 width, int32 height, int32 channels);
    
    /*!
     * @brief  Creates a new uncompressed rectangular dataset.
     * 
     * @param datafile <b>[not-null]</b>  The datafile to use.
     * @param width <b>[>0]</b>  Width of the dataset.
     * @param height <b>[>0]</b>  Height of the dataset.
     * @param channels <b>[>0]</b>  The number of 8-bit dataset channels.
     * 
     * @return The created IDataset.
     */
    static Ptr<IDataset> CreateRect(IDatafile* datafile, int32 width, int32 height, int32 channels);
    
    /*!
     * @brief  Creates a new uncompressed rectangular sparse dataset.
     * 
     * @param filePath <b>[not-null]</b>  Path to the dataset datafile.
     * @param width <b>[>0]</b>  Width of the dataset.
     * @param height <b>[>0]</b>  Height of the dataset.
     * @param channels <b>[>0]</b>  The number of 8-bit dataset channels.
     * @param voidSample <b>[not-null]</b>  The dataset sample to use for void areas.
     * @param dataRegion <b>[not-null]</b>  The regions that contain data.
     * 
     * @return The created IDataset.
     */
    static Ptr<IDataset> CreateRectSparse(Path* filePath, int32 width, int32 height, int32 channels, ByteBuffer* voidSample, IMapRegion* dataRegion);
    
    /*!
     * @brief  Creates a new uncompressed rectangular sparse dataset.
     * 
     * @param datafile <b>[not-null]</b>  The dataset datafile.
     * @param width <b>[>0]</b>  Width of the dataset.
     * @param height <b>[>0]</b>  Height of the dataset.
     * @param channels <b>[>0]</b>  The number of 8-bit dataset channels.
     * @param voidSample <b>[not-null]</b>  The dataset sample to use for void areas.
     * @param dataRegion <b>[not-null]</b>  The regions that contain data.
     * 
     * @return The created IDataset.
     */
    static Ptr<IDataset> CreateRectSparse(IDatafile* datafile, int32 width, int32 height, int32 channels, ByteBuffer* voidSample, IMapRegion* dataRegion);
    
    /*!
     * @brief  Opens an existing dataset.
     * 
     * @param filePath <b>[not-null]</b>  Path to the dataset file.
     * @param readOnly Open the dataset as read only?
     * 
     * @return The IDataset object.
     */
    static Ptr<IDataset> Open(Path* filePath, bool readOnly);

    /*!
     * @brief  Opens an existing dataset through streaming.
     * 
     * @param fileName File name of the dataset.
     * @param host Streaming host or ip.
     * @param port Streaming port.
     * 
     * @return The IDataset object.
     */
    static Ptr<IDataset> Open(String fileName, String host, int port);
    
    /*!
     * @brief  Opens an existing dataset.
     * 
     * @param datafile <b>[not-null]</b>  The datafile of the dataset.
     * 
     * @return The IDataset object.
     */
    static Ptr<IDataset> Open(IDatafile* datafile);
    
    /*!
     * @brief  Opens an existing cube dataset.
     * 
     * @param filePath <b>[not-null]</b>  Path to the dataset file.
     * @param readOnly Open the dataset as read only?
     * 
     * @return The IDataset object.
     */
    static Ptr<IDataset> OpenCube(Path* filePath, bool readOnly);
    
    /*!
     * @brief  Opens an existing cube dataset.
     * 
     * @param datafile <b>[not-null]</b>  The datafile of the dataset.
     * 
     * @return <b>[not-null]</b>  The IDataset object.
     */
    static Ptr<IDataset> OpenCube(IDatafile* datafile);
    
    /*!
     * @brief  Opens an existing rectangular dataset.
     * 
     * @param filePath <b>[not-null]</b>  Path to the dataset file.
     * @param readOnly Open the dataset as read only?
     * 
     * @return The IDataset object.
     */
    static Ptr<IDataset> OpenRect(Path* filePath, bool readOnly);
    
    /*!
     * @brief  Opens an existing rectangular dataset.
     * 
     * @param datafile <b>[not-null]</b>  The datafile of the dataset.
     * 
     * @return The IDataset object.
     */
    static Ptr<IDataset> OpenRect(IDatafile* datafile);
    
    virtual void Begin();
    
    virtual void End();
    
    virtual void Flush();
    
    virtual void FlushMetadata();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The datafile that holds the dataset samples.
     */
    Ptr<IDatafile> datafile;
    
    /*!
     * @brief  The dataset file header values.
     */
    Ptr<DatasetHeader> datasetHeader;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Opens an existing dataset file.
     * 
     * @param datafile <b>[not-null]</b>  The dataset file to open.
     */
    Dataset(IDatafile* datafile);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DisposeManaged();
    
    virtual Ptr<DatasetMetadata> LoadMetadata();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The amount of cache memory to use for compressed datasets.
     */
    static int32 compressedCacheMemory;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Opens an existing dataset.
     * 
     * @param datafile The dataset file.
     * @param datasetHeader The dataset header.
     * 
     * @return <b>[not-null]</b>  The opened dataset.
     */
    static Ptr<IDataset> Open(IDatafile* datafile, DatasetHeader* datasetHeader);
    
    /*!
     * @brief  Opens an existing dataset of version <c>1.0</c>.
     * 
     * @param datafile The dataset file.
     * @param datasetHeader The dataset header.
     * 
     * @return <b>[not-null]</b>  The opened dataset.
     */
    static Ptr<IDataset> Open_1_0(IDatafile* datafile, DatasetHeader* datasetHeader);
    
    /*!
     * @brief  Opens an existing dataset of version <c>1.1</c>.
     * 
     * @param datafile The dataset file.
     * @param datasetHeader The dataset header.
     * 
     * @return <b>[not-null]</b>  The opened dataset.
     */
    static Ptr<IDataset> Open_1_1(IDatafile* datafile, DatasetHeader* datasetHeader);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Dataset> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFF7AD963;
    
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
      if ((ptr = DatasetBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
