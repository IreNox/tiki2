////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_COLORRAMPBRUSH_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_COLORRAMPBRUSH_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/IntervalF.h"
#include "Cloddy/IntervalI.h"

// Include referenced classes.

#include "Cloddy/BrushBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ColorBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ElevationBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class SlopeBuffer; } } } }
namespace Cloddy { namespace API { namespace Imaging { class ImageSampler; } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::ColorRampBrush.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::IntervalF;
  using Cloddy::Core::Math::IntervalI;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ColorBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::ElevationBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::SlopeBuffer;
  using Cloddy::API::Imaging::ImageSampler;
  
  /*!
   * @brief  A brush that colors the terrain depending on elevation and slope using a lookup 
   *         texture.
   * 
   * The given image sample is used as a lookup texture.Texture coordinates for a brush sample are 
   * derieved from the terrain slope (texture U-coordinate)and the terrain elevation (texture 
   * V-coordinate):
   * <pre>
   *     .   Zero slope       Max slope (90 degrees)
   *     .   |                |
   *     .   &lt; .............. >
   *     .   
   *     .   +----------------+    ^ - Maximum elevation
   *     .   |(0,0)      (1,0)|    .
   *     .   |                |    .
   *     .   |                |    .
   *     .   |                |    .  
   *     .   |(0,1)      (1,1)|    .
   *     .   +----------------+    v - Minimum elevation
   * </pre>
   */
  class ColorRampBrush : public BrushBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool DoesModifyColor();
    
    virtual bool DoesModifyDetail();
    
    virtual bool DoesModifyDisplacement();
    
    virtual bool DoesModifyElevation();
    
    virtual bool DoesUseSlope();
    
    /*!
     * @brief  The elevation range where the slope brush modifies heightmap samples.
     * 
     * The range is specified as normalized elevation values (see HeightmapSample::MaxValue).
     * 
     * The default value is <c>[0..MaxValue]</c>.
     * 
     * @return The elevation range.
     */
    IntervalI GetRangeElevation();
    
    /*!
     * @brief  The elevation range where the slope brush modifies heightmap samples.
     * 
     * The range is specified as normalized elevation values (see HeightmapSample::MaxValue).
     * 
     * The default value is <c>[0..MaxValue]</c>.
     * 
     * @param value The elevation range.
     */
    void SetRangeElevation(const IntervalI& value);
    
    /*!
     * @brief  The slope range where the slope brush modifies heightmap samples.
     * 
     * The slope range is specified in degrees.
     * 
     * The default value is <c>[0..90]</c>.
     * 
     * @return The slope range.
     */
    IntervalF GetRangeSlope();
    
    /*!
     * @brief  The slope range where the slope brush modifies heightmap samples.
     * 
     * The slope range is specified in degrees.
     * 
     * The default value is <c>[0..90]</c>.
     * 
     * @param value The slope range.
     */
    void SetRangeSlope(const IntervalF& value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ColorRampBrush.
     * 
     * @param width <b>[>0]</b>  The brush width.
     * @param height <b>[>0]</b>  The brush height.
     * @param colorRamp <b>[not-null]</b>  The color ramp image sampler.
     */
    ColorRampBrush(int32 width, int32 height, ImageSampler* colorRamp);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Visit(SlopeBuffer* buffer);
    
    virtual void Visit(ColorBuffer* buffer);
    
    virtual void Visit(ElevationBuffer* buffer);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual Ptr<IBrush> DoScale(int32 numerator, int32 denominator);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The color ramp image sampler.
     */
    Ptr<ImageSampler> colorRamp;
    
    /*!
     * @brief  The current elevation buffer.
     */
    Ptr<ElevationBuffer> elevationBuffer;
    
    /*!
     * @brief  The buffer samples of #elevationBuffer.
     */
    Array<int32> elevationSamples;
    
    /*!
     * @brief  The elevation range where the slope brush modifies heightmap samples.
     */
    IntervalI rangeElevation;
    
    /*!
     * @brief  The slope range where the slope brush modifies heightmap samples.
     */
    IntervalF rangeSlope;
    
    /*!
     * @brief  The current slope buffer.
     */
    Ptr<SlopeBuffer> slopeBuffer;
    
    /*!
     * @brief  The buffer samples of SlopeBuffer.
     */
    Array<float32> slopeSamples;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ColorRampBrush> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB7254AEB;
    
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
      if ((ptr = BrushBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
