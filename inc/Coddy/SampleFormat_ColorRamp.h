////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEFORMAT_COLORRAMP_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEFORMATS_SAMPLEFORMAT_COLORRAMP_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"

// Include referenced classes.

#include "Cloddy/SampleFormat.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class ISampleEncoder; } } } }
namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorRamp; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats { class SampleFormat; } } } }
namespace CodeX { namespace System { class ByteBuffer; } }

// Declare class ::Cloddy::API::Heightmaps::SampleFormats::SampleFormat_ColorRamp.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleFormats
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Heightmaps;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::Colors::IColorRamp;
  
  // Use referenced classes.
  
  using CodeX::System::ByteBuffer;
  
  /*!
   * @brief  An implementation of the ISampleFormat interface that computes vertex diffuse colors 
   *         by mapping the elevation onto a color ramp.
   */
  class SampleFormat_ColorRamp : public SampleFormat
  {
    // Declare friend classes.
    
    friend class SampleFormat;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual SampleBitDepth GetBitDepth();
    
    virtual int32 GetChannels();
    
    /*!
     * @brief  Start index of color ramp interval to use.
     * 
     * The default value is <c>0.0f</c>.
     * 
     * @return The start index.
     */
    float64 GetColorRampFrom();
    
    /*!
     * @brief  Start index of color ramp interval to use.
     * 
     * The default value is <c>0.0f</c>.
     * 
     * @param value The start index.
     */
    void SetColorRampFrom(float64 value);
    
    /*!
     * @brief  End index of color ramp interval to use.
     * 
     * The default value is <c>1.0f</c>.
     * 
     * @return The end index.
     */
    float64 GetColorRampTo();
    
    /*!
     * @brief  End index of color ramp interval to use.
     * 
     * The default value is <c>1.0f</c>.
     * 
     * @param value The end index.
     */
    void SetColorRampTo(float64 value);
    
    virtual HeightmapLayer GetLayerMask();
    
    virtual String GetMnemonic();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DatasetToHeightmap(ByteBuffer* datasetSample, HeightmapSample* heightmapSample);
    
    virtual void HeightmapToDataset(HeightmapSample* heightmapSample, ByteBuffer* datasetSample);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The color ramp to use.
     */
    Ptr<IColorRamp> colorRamp;
    
    /*!
     * @brief  Scale factor from normalized elevation values to color ramp interval.
     */
    float64 colorRampFactor;
    
    /*!
     * @brief  Start index of color ramp interval to use.
     */
    float64 colorRampFrom;
    
    /*!
     * @brief  End index of color ramp interval to use.
     */
    float64 colorRampTo;
    
    /*!
     * @brief  The sample format that is augmented with a color ramp.
     */
    Ptr<ISampleEncoder> sampleFormat;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SampleFormat_ColorRamp.
     * 
     * @param sampleFormat The sample encoder to wrap.
     * @param colorRamp The color ramp to use for generating diffuse colors.
     */
    SampleFormat_ColorRamp(ISampleEncoder* sampleFormat, IColorRamp* colorRamp);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SampleFormat_ColorRamp> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC9C4B961;
    
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
      if ((ptr = SampleFormat::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
