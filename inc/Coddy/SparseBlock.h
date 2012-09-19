////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_METADATA_SPARSEBLOCK_H
#define CLODDY_API_DATASETS_METADATA_SPARSEBLOCK_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMetadataBlock.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { class IMapRegion; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Datasets::Metadata::SparseBlock.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::IMapRegion;
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerializableBase;
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An IMetadataBlock that describes the areas of a sparse dataset that contain data.
   */
  class SparseBlock : public SerializableBase, public virtual IMetadataBlock
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Unique ID token for SparseBlocks.
     * 
     * @see #GetId
     */
    static const String SparseId;
    
    virtual String GetId();
    
    virtual String GetName();
    
    /*!
     * @brief  The map region that defines the areas for which data is available.
     * 
     * @return <b>[not-null]</b>  The map region.
     */
    Ptr<IMapRegion> GetRegion();
    
    /*!
     * @brief  The map region that defines the areas for which data is available.
     * 
     * @param value <b>[not-null]</b>  The map region.
     */
    void SetRegion(IMapRegion* value);
    
    /*!
     * @brief  Returns a byte buffer that contains a dataset sample which represents void areas in 
     *         the dataset.
     * 
     * @return <b>[not-null]</b>  The byte buffer holding a single void sample.
     */
    Ptr<ByteBuffer> GetVoidSample();
    
    /*!
     * @brief  Returns a byte buffer that contains a dataset sample which represents void areas in 
     *         the dataset.
     * 
     * @param value <b>[not-null]</b>  The byte buffer holding a single void sample.
     */
    void SetVoidSample(ByteBuffer* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    SparseBlock();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{A654CBF0-5A88-494F-A385-A1FEB39FC718}
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
     * @brief  The map region that defines the areas for which data is available.
     */
    Ptr<IMapRegion> region;
    
    /*!
     * @brief  The dataset sample used for void areas.
     */
    Ptr<ByteBuffer> voidSample;
    
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
    public: typedef Ptr<SparseBlock> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1127A1B9;
    
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
      if ((ptr = IMetadataBlock::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
