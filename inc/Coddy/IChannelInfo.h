////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_METADATA_ICHANNELINFO_H
#define CLODDY_API_DATASETS_METADATA_ICHANNELINFO_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class IChannelInfoVisitor; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleConverter; } } } }

// Declare interface ::Cloddy::API::Datasets::Metadata::IChannelInfo.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::SampleFormats::ISampleConverter;
  using Cloddy::Core::IO::Serialization::ISerializable;
  
  /*!
   * @brief  Base interface for IMetadataBlock implementations that provide information about 
   *         dataset channels (eg. elevation or diffuse color).
   */
  class NO_VTABLE IChannelInfo : public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Number of dataset channels.
     * 
     * @return <b>[>=1]</b>  The channel count.
     */
    virtual int32 GetChannelCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Accepts the given visitor.
     * 
     * @param visitor <b>[not-null]</b>  The visitor object.
     * @param userData Optional user data.
     */
    virtual void Accept(IChannelInfoVisitor* visitor, Object* userData) = 0;
    
    /*!
     * @brief  Creates an ISampleConverter object for this channel metadata block.
     * 
     * @return <b>[not-null]</b>  The ISampleConverter object.
     */
    virtual Ptr<ISampleConverter> CreateSampleConverter() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IChannelInfo> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x36E4B868;
    
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
      if ((ptr = ISerializable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
