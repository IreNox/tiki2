////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_METADATA_DATASETMETADATA_H
#define CLODDY_API_DATASETS_METADATA_DATASETMETADATA_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class IMetadataBlock; } } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Datasets::Metadata::DatasetMetadata.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IList;
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Serialization::SerializableBase;
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  The DatasetMetadata class provides acces to metadata blocks stored in a dataset file.
   */
  class DatasetMetadata : public SerializableBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of metadata blocks in this dataset metadata collection.
     * 
     * @return <b>[>=0]</b>  The number of metadata blocks.
     */
    int32 GetBlockCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DatasetMetadata.
     */
    DatasetMetadata();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Loads the dataset metadata object.
     * 
     * @param datasetFile <b>[not-null]</b>  The dataset file path.
     * 
     * @return <b>[not-null]</b>  The loaded dataset metadata object.
     */
    static Ptr<DatasetMetadata> Load(Path* datasetFile);
    
    /*!
     * @brief  Adds the given dataset metadata block to this collection.
     * 
     * If another metadata block with the same unique ID token is already contained in the 
     * collection,it will be replaced by the given one.
     * 
     * @param block <b>[not-null]</b>  The block to add.
     */
    void AddBlock(IMetadataBlock* block);
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    /*!
     * @brief  Returns a IMetadataBlock by its unique ID token.
     * 
     * @param blockId <b>[not-null]</b>  The ID token.
     * 
     * @return The metadata block or \c null  if no such block has been found.
     * 
     * @see IMetadataBlock::GetId
     */
    Ptr<IMetadataBlock> GetBlockForId(String blockId);
    
    /*!
     * @brief  Returns a IMetadataBlock by its index.
     * 
     * @param index <b>[0..#GetBlockCount-1]</b>  The block index.
     * 
     * @return <b>[not-null]</b>  The metadata block.
     */
    Ptr<IMetadataBlock> GetBlockForIndex(int32 index);
    
    /*!
     * @brief  Removes the given dataset metadatablock from this collection.
     * 
     * @param block <b>[not-null]</b>  The block to remove.
     * 
     * @return \c true  if the block has been removed,\c false  if the block was not in this 
     * collection.
     */
    bool RemoveBlock(IMetadataBlock* block);
    
    /*!
     * @brief  Removes the given dataset metadatablock from this collection.
     * 
     * @param blockId <b>[not-null]</b>  The unique ID token of the block to remove.
     * 
     * @return \c true  if the block has been removed,\c false  if the block was not in this 
     * collection.
     */
    bool RemoveBlock(String blockId);
    
    /*!
     * @brief  Saves this dataset metadata object.
     * 
     * @param datasetFile <b>[not-null]</b>  The dataset file path.
     */
    void Save(Path* datasetFile);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{55E9AB77-46D4-4BCB-B5D2-02639BBB5C1E}
     */
    static const String SerialGuid;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Serialization information about this type.
     */
    static const StaticPtr<ISerialTypeInfo> SerialId;
    
    /*!
     * @brief  The metadata blocks.
     */
    Ptr<IList<Ref<IMetadataBlock> > > blocks;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the path to the metadata file.
     * 
     * @param datasetFile Path to dataset file.
     * 
     * @return Path to metadata file.
     */
    static Ptr<Path> GetMetadataFilePath(Path* datasetFile);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field SerialId.
     */
    static Object* StaticInitializer_SerialId();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatasetMetadata> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x517C5F51;
    
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
      if ((ptr = SerializableBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
