////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IBrushMask.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { struct Gauss; } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Imaging { class IImage; } } }
namespace Cloddy { namespace API { namespace Imaging { class IImageReader; } } }
namespace Cloddy { namespace API { namespace Procedural { class INoiseFunction; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapRegion; } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::BrushMask.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Gauss;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Imaging::IImage;
  using Cloddy::API::Imaging::IImageReader;
  using Cloddy::API::Procedural::INoiseFunction;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::HeightmapRegion;
  
  /*!
   * @brief  Default implementation of the IBrushMask interface.
   */
  class BrushMask : public virtual IBrushMask
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool DoesUseSlope();
    
    virtual int32 GetHeight();
    
    virtual int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a brush mask that filters samples based on the terrain elevation.
     * 
     * The given \e elevationCurve  will be evaluated for elevation values (
     * see HeightmapSample::MaxValue).The resulting curve value is then interpreted as a normalized 
     * mask value in the range <c>[0..1]</c>.
     * 
     * @param width <b>[>0]</b>  The brush mask width,in samples.
     * @param height <b>[>0]</b>  The brush mask height,in samples.
     * @param elevationCurve The weight curve.
     * 
     * @return <b>[not-null]</b>  The brush mask.
     */
    static Ptr<IBrushMask> Elevation(int32 width, int32 height, const Gauss& elevationCurve);
    
    /*!
     * @brief  Creates a brush mask from the given image.
     * 
     * The given image will be converted to 16-bit greyscale and the color intensity values will be 
     * used as mask values.
     * 
     * @param image <b>[not-null]</b>  The image.
     * 
     * @return <b>[not-null]</b>  The brush mask.
     */
    static Ptr<IBrushMask> FromImage(IImage* image);
    
    /*!
     * @brief  Creates a brush mask from the given image.
     * 
     * The given image will be converted to 16-bit greyscale and the color intensity values will be 
     * used as mask values.
     * 
     * @param image <b>[not-null]</b>  The image.
     * 
     * @return <b>[not-null]</b>  The brush mask.
     */
    static Ptr<IBrushMask> FromImage(IImageReader* image);
    
    /*!
     * @brief  Returns a brush mask that contains smooth noise that is produced by the given noise 
     *         function.
     * 
     * @param width <b>[>0]</b>  The brush mask width,in samples.
     * @param height <b>[>0]</b>  The brush mask height,in samples.
     * @param noise <b>[not-null]</b>  The noise function to use.
     * @param seed Random seed value.
     * @param scale Noise scale factor.
     * 
     * @return TODO
     */
    static Ptr<IBrushMask> Noise(int32 width, int32 height, INoiseFunction* noise, int32 seed, float64 scale);
    
    /*!
     * @brief  Returns a brush mask that represents a radial fallof from the brush center towards 
     *         the brush edges.
     * 
     * @param width <b>[>0]</b>  The brush mask width,in samples.
     * @param height <b>[>0]</b>  The brush mask height,in samples.
     * @param minValue <b>[0..32768]</b>  The minimum mask value at the brush edges.
     * @param maxValue <b>[0..32768]</b>  The maximum mask value at the brush center.
     * 
     * @return <b>[not-null]</b>  The brush mask.
     */
    static Ptr<IBrushMask> Radial(int32 width, int32 height, int32 minValue, int32 maxValue);
    
    /*!
     * @brief  Returns a brush mask that filters samples based on the terrain slope.
     * 
     * The given \e slopeCurve  will be evaluated for slope values in degrees.The resulting curve 
     * value is then interpreted as a normalized mask value in the range <c>[0..1]</c>.
     * 
     * @param width <b>[>0]</b>  The brush mask width,in samples.
     * @param height <b>[>0]</b>  The brush mask height,in samples.
     * @param slopeCurve The weight curve.
     * 
     * @return <b>[not-null]</b>  The brush mask.
     */
    static Ptr<IBrushMask> Slope(int32 width, int32 height, const Gauss& slopeCurve);
    
    /*!
     * @brief  Returns a brush mask that returns an uniform mask value for all sample coordinates.
     * 
     * @param width <b>[>0]</b>  The brush mask width,in samples.
     * @param height <b>[>0]</b>  The brush mask height,in samples.
     * @param maskValue <b>[0..32768]</b>  The uniform mask value.
     * 
     * @return <b>[not-null]</b>  The brush mask.
     */
    static Ptr<IBrushMask> Uniform(int32 width, int32 height, int32 maskValue);
    
    virtual Ptr<IBrushMask> Buffer();
    
    virtual int32 GetMaskValue(int32 x, int32 y) = 0;
    
    virtual Ptr<IBrushMask> Invert();
    
    virtual Ptr<IBrushMask> Modulate(IBrushMask* mask);
    
    virtual void Prepare(HeightmapRegion* region);
    
    virtual Ptr<IImageReader> ReadAsImage();
    
    virtual Ptr<IBrushMask> Scale(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of BrushMask.
     * 
     * @param width <b>[>0]</b>  The brush mask width,in samples.
     * @param height <b>[>0]</b>  The brush mask height,in samples.
     */
    BrushMask(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a scaled version of this brush mask.
     * 
     * The given \e width  and \e height  are guaranteed to differ from the width and height of 
     * this brush mask and to be greater than \c 0 .
     * 
     * @param width The scaled brush mask width,in samples.
     * @param height The scaled brush mask height,in samples.
     * 
     * @return <b>[not-null]</b>  The scaled brush mask.
     */
    virtual Ptr<IBrushMask> DoScale(int32 width, int32 height) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The brush mask height,in samples.
     */
    int32 height;
    
    /*!
     * @brief  The brush mask width,in samples.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BrushMask> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5D1446AC;
    
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
      if ((ptr = IBrushMask::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
