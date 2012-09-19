////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_ISAMPLEFORMAT_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_ISAMPLEFORMAT_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/SampleConverterType.h"

// Include referenced interfaces.

#include "Cloddy/ISampleEncoder.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datasets { namespace Metadata { class IChannelInfo; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleConverter; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorRamp; } } } }

// Declare interface ::Cloddy::API::Heightmaps::SampleFormats::ISampleFormat.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Datasets::Metadata::IChannelInfo;
  using Cloddy::API::Util::Colors::IColorRamp;
  
  /*!
   * @brief  Represents a dataset sample format.
   */
  class NO_VTABLE ISampleFormat : public virtual ISampleEncoder
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Appends the given sample converter to this sample format.
     * 
     * @param component <b>[not-null]</b>  The sample converter to append.
     * 
     * @return <b>[not-null]</b>  The resulting sample format.
     */
    virtual Ptr<ISampleFormat> Append(ISampleConverter* component) = 0;
    
    /*!
     * @brief  Appends the given sample converter to this sample format.
     * 
     * @param sampleConverter The built in sample converter to append.
     * 
     * @return <b>[not-null]</b>  The resulting sample format.
     */
    virtual Ptr<ISampleFormat> Append(SampleConverterType sampleConverter) = 0;
    
    /*!
     * @brief  Ensures that this sample format sets all values of a HeightmapSample.
     * 
     * If one or more HeightmapSample components are not set by this sample format,this method 
     * returns another sample format that sets those missing values to the following default values:
     *   - HeightmapSample::Elevation :0
     *   - HeightmapSample::Diffuse :Color::White
     *   - HeightmapSample::DisplacementX :HeightmapSample::MidValue
     *   - HeightmapSample::DisplacementY :HeightmapSample::MidValue
     *   - HeightmapSample::DisplacementZ :HeightmapSample::MidValue
     *   - HeightmapSample::Detail0 :0
     *   - HeightmapSample::Detail1 :0
     *   - HeightmapSample::Detail2 :0
     *   - HeightmapSample::Detail3 :0
     * 
     * @return <b>[not-null]</b>  The opaque ISampleFormat instance.
     */
    virtual Ptr<ISampleFormat> MakeOpaque() = 0;
    
    /*!
     * @brief  Returns an array of IChannelInfo objects that describes this sample format.
     * 
     * The returned IChannelInfo objects can be stored as metadata with a dataset.
     * 
     * @return The IChannelInfo array or \c null  if this sample format cannot be described.
     */
    virtual Array<Ptr<IChannelInfo> > MetadataInfo() = 0;
    
    /*!
     * @brief  Creates a sample format that uses the given color ramp to compute diffuse color 
     *         values that are based on elevation.
     * 
     * The elevation value is transformed to <c>[0..1]</c> and then used to access the given color 
     * ramp.
     * 
     * @param colorRamp <b>[not-null]</b>  The color ramp to use.
     * 
     * @return <b>[not-null]</b>  The resulting sample format.
     */
    virtual Ptr<ISampleFormat> UseColorRamp(IColorRamp* colorRamp) = 0;
    
    /*!
     * @brief  Creates a sample format that uses the given color ramp to compute diffuse color 
     *         values that are based on elevation.
     * 
     * The elevation value is transformed to <c>[from..to]</c> and then used to access the given 
     * color ramp.
     * 
     * @param colorRamp <b>[not-null]</b>  The color ramp to use.
     * @param from Lower bound of transformed elevation value.
     * @param to Upper bound of transformed elevation value.
     * 
     * @return <b>[not-null]</b>  The resulting sample format.
     */
    virtual Ptr<ISampleFormat> UseColorRamp(IColorRamp* colorRamp, float64 from, float64 to) = 0;
    
    /*!
     * @brief  Creates a sample format that uses an uniform diffuse color for all heightmap samples.
     * 
     * @param color The uniform color,as a 32-bit ARGB color value.
     * 
     * @return <b>[not-null]</b>  The resulting sample format.
     */
    virtual Ptr<ISampleFormat> UseUniformColor(int32 color) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISampleFormat> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2EC640;
    
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
      if ((ptr = ISampleEncoder::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
