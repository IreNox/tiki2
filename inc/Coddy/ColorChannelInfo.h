////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_METADATA_COLORCHANNELINFO_H
#define CLODDY_API_DATASETS_METADATA_COLORCHANNELINFO_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ChannelInfoBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class IChannelInfoVisitor; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleConverter; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Datasets::Metadata::ColorChannelInfo.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::SampleFormats::ISampleConverter;
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  An IMetadataBlock that describes diffuse color in a dataset.
   */
  class ColorChannelInfo : public ChannelInfoBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of ColorChannelInfo.
     */
    ColorChannelInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ColorChannelInfo for 8-bit grayscale color values.
     * 
     * @return <b>[not-null]</b>  The ColorChannelInfo object.
     */
    static Ptr<ColorChannelInfo> ForGrayscale();
    
    /*!
     * @brief  Creates a new instance of ColorChannelInfo for a color palette.
     * 
     * @param colorPalette <b>[not-null]</b>  The used color palette.
     * @param colorIndexSize <b>[1..2]</b>  Size of a single color index,in bytes.
     * 
     * @return <b>[not-null]</b>  The ColorChannelInfo object.
     */
    static Ptr<ColorChannelInfo> ForPalette(Array<int32> colorPalette, int32 colorIndexSize);
    
    /*!
     * @brief  Creates a new instance of ColorChannelInfo for 16-bit RGB (565)color values.
     * 
     * @return <b>[not-null]</b>  The ColorChannelInfo object.
     */
    static Ptr<ColorChannelInfo> ForRGB565();
    
    /*!
     * @brief  Creates a new instance of ColorChannelInfo for 24-bit RGBA (888)color values.
     * 
     * @return <b>[not-null]</b>  The ColorChannelInfo object.
     */
    static Ptr<ColorChannelInfo> ForRGB888();
    
    /*!
     * @brief  Creates a new instance of ColorChannelInfo for 32-bit RGBA (8888)color values.
     * 
     * @return <b>[not-null]</b>  The ColorChannelInfo object.
     */
    static Ptr<ColorChannelInfo> ForRGBA8888();
    
    virtual void Accept(IChannelInfoVisitor* visitor, Object* userData);
    
    virtual Ptr<ISampleConverter> CreateSampleConverter();
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual void Serialize(Serializer* data);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{3CE2BD80-61AC-4ADE-BCFF-0B93638055BB}
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
     * @brief  The color palette,only set for color index mode.
     */
    Array<int32> colorPalette;
    
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
    public: typedef Ptr<ColorChannelInfo> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7C17E664;
    
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
      if ((ptr = ChannelInfoBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
