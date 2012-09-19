////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAPREGION_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAPREGION_H

#include "CodeX/System.h"

// Forward declare referenced structures.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { struct SlopeInfo; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ColorBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DetailBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class DisplacementBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class ElevationBuffer; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { class SlopeBuffer; } } } }

// Declare class ::Cloddy::API::Heightmaps::HeightmapRegion.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Heightmaps::SampleBuffers::SlopeInfo;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::Brushes::IBrush;
  using Cloddy::API::Heightmaps::Brushes::IBrushMask;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::SampleBuffers::ColorBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::DetailBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::DisplacementBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::ElevationBuffer;
  using Cloddy::API::Heightmaps::SampleBuffers::SlopeBuffer;
  
  /*!
   * @brief  This class represents the samples of a rectangular region of a heightmap.
   * 
   * @see HeightmapSample
   */
  class HeightmapRegion : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The buffer for diffuse color values.
     * 
     * @return <b>[not-null]</b>  The diffuse color buffer.
     * 
     * @exception FailedAssertionException If this heightmap region does not store diffuse color 
     * values.
     * 
     * @see #HasColor
     */
    Ptr<ColorBuffer> GetColorBuffer();
    
    /*!
     * @brief  The buffer for detail channel values.
     * 
     * @return <b>[not-null]</b>  The detail buffer.
     * 
     * @exception FailedAssertionException If this heightmap region does not store elevation detail 
     * channel values.
     * 
     * @see #HasDetail
     */
    Ptr<DetailBuffer> GetDetailBuffer();
    
    /*!
     * @brief  The buffer for displacement values.
     * 
     * @return <b>[not-null]</b>  The displacement buffer.
     * 
     * @exception FailedAssertionException If this heightmap region does not store displacement 
     * values.
     * 
     * @see #HasDisplacement
     */
    Ptr<DisplacementBuffer> GetDisplacementBuffer();
    
    /*!
     * @brief  The buffer for elevation values.
     * 
     * @return <b>[not-null]</b>  The elevation buffer.
     * 
     * @exception FailedAssertionException If this heightmap region does not store elevation values.
     * 
     * @see #HasElevation
     */
    Ptr<ElevationBuffer> GetElevationBuffer();
    
    /*!
     * @brief  The cubemap face on which this heightmap region is located.
     * 
     * See the constants of the Cubemap class for possible values.
     * 
     * The default value is Cubemap::FaceNegZ.
     */
    int32 Face;
    
    /*!
     * @brief  X-component of cubemap face coordinates of top-left sample of this heightmap region.
     * 
     * The default value is \c 0 .
     * 
     * @see Cubemap
     */
    int32 FaceX;
    
    /*!
     * @brief  Y-component of cubemap face coordinates of top-left sample of this heightmap region.
     * 
     * The default value is \c 0 .
     * 
     * @see Cubemap
     */
    int32 FaceY;
    
    /*!
     * @brief  Does this heightmap region store diffuse color values?
     * 
     * @return \c true  if this heightmap region stores diffuse color values,\c false  if not.
     */
    bool HasColor();
    
    /*!
     * @brief  Does this heightmap region store detail channel values?
     * 
     * @return \c true  if this heightmap region stores detail channel values,\c false  if not.
     */
    bool HasDetail();
    
    /*!
     * @brief  Does this heightmap region store displacement values?
     * 
     * @return \c true  if this heightmap region stores displacement values,\c false  if not.
     */
    bool HasDisplacement();
    
    /*!
     * @brief  Does this heightmap region store elevation values?
     * 
     * @return \c true  if this heightmap region stores elevation values,\c false  if not.
     */
    bool HasElevation();
    
    /*!
     * @brief  The height of this region,in heightmap samples.
     * 
     * @return <b>[>0]</b>  The height the region,in heightmap samples.
     */
    int32 GetHeight();
    
    /*!
     * @brief  Optional slope buffer of this heightmap region.
     * 
     * @return The slope buffer or \c null .
     */
    Ptr<SlopeBuffer> GetSlopeBuffer();
    
    /*!
     * @brief  Optional slope buffer of this heightmap region.
     * 
     * @param value The slope buffer or \c null .
     */
    void SetSlopeBuffer(SlopeBuffer* value);
    
    /*!
     * @brief  The width of this region,in heightmap samples.
     * 
     * @return <b>[>0]</b>  The width of the region,in heightmap samples.
     */
    int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of HeightmapRegion.
     * 
     * At least one of \e hasElevation  and \e hasColor  must be \c true !
     * 
     * @param width <b>[>0]</b>  Width of the heightmap region,in heightmap samples.
     * @param height <b>[>0]</b>  Height of the heightmap region,in heightmap samples.
     * @param hasElevation Shall the heightmap region store elevation values?
     * @param hasColor Shall the heightmap region store diffuse color values?
     * @param hasDisplacement Shall the heightmap region store displacement values?
     * @param hasDetail TODO
     * 
     * @return <b>[not-null]</b>  The created HeightmapRegion object.
     */
    static Ptr<HeightmapRegion> Create(int32 width, int32 height, bool hasElevation, bool hasColor, bool hasDisplacement, bool hasDetail);
    
    /*!
     * @brief  Returns a new HeightmapRegion which can be used to apply the given brush.
     * 
     * @param brush <b>[not-null]</b>  The brush.
     * 
     * @return <b>[not-null]</b>  The heightmap region.
     */
    static Ptr<HeightmapRegion> ForBrush(IBrush* brush);
    
    /*!
     * @brief  Returns a HeightmapRegion that wraps the given sample buffers.
     * 
     * All sample buffers must have the same size.At least one buffer must be specified.
     * 
     * @param elevation <b></b>  The elevation buffer or \c null  if the region does not need to 
     * store elevation values.
     * @param color <b></b> The diffuse color buffer or \c null  if the region does not need to 
     * store diffuse color values.
     * @param displacement <b></b> The displacement buffer or \c null  if the region does not need 
     * to store displacement values.
     * @param detail TODO
     * 
     * @return <b>[not-null]</b>  The created HeightmapRegion object.
     */
    static Ptr<HeightmapRegion> Wrap(ElevationBuffer* elevation, ColorBuffer* color, DisplacementBuffer* displacement, DetailBuffer* detail);
    
    /*!
     * @brief  Applies the given IBrush to the heightmap samples of this heightmap region.
     * 
     * @param brush <b>[not-null]</b>  The IBrush to apply.
     * @param mask Optional brush mask to use.
     */
    void ApplyBrush(IBrush* brush, IBrushMask* mask);
    
    /*!
     * @brief  Clips this heightmap region at the given heightmap bounds (for rectangular 
     *         heightmaps).
     * 
     * @param heightmapWidth <b>[>0]</b>  The heightmap width.
     * @param heightmapHeight <b>[>0]</b>  The heightmap height.
     * 
     * @return <b>[not-null]</b>  The clipped heightmap region.
     */
    Ptr<HeightmapRegion> Clip(int32 heightmapWidth, int32 heightmapHeight);
    
    /*!
     * @brief  Creates a new SlopeBuffer for this heightmap region.
     * 
     * @param slopeInfo The SlopeInfo value to use for computing terrain slope angles.
     * 
     * @return <b>[not-null]</b>  The created slope buffer.
     */
    Ptr<SlopeBuffer> CreateSlopeBuffer(const SlopeInfo& slopeInfo);
    
    /*!
     * @brief  Marks a region of the given heightmap as dirty.
     * 
     * This method uses the current #FaceX,#FaceY,#Face,#GetWidth and #GetHeight values to add a 
     * dirty region to the given heightmap.
     * 
     * @param heightmap <b>[not-null]</b>  The heightmap.
     * 
     * @see IHeightmap::MarkAsDirty
     */
    void MarkAsDirty(IHeightmap* heightmap);
    
    /*!
     * @brief  Reads the given heightmap sample from this heightmap region at the current cursor 
     *         position and increases the cursors X-coordinate.
     * 
     * @param sample <b>[not-null]</b>  The heightmap sample.
     * 
     * @see #SetCursor
     * @see #Write
     */
    void Read(HeightmapSample* sample);
    
    /*!
     * @brief  Reads the given heightmap sample from this heightmap region at the current cursor 
     *         position.
     * 
     * @param sample <b>[not-null]</b>  The heightmap sample.
     * 
     * @see #SetCursor
     * @see #Write
     */
    void ReadKeepCursor(HeightmapSample* sample);
    
    /*!
     * @brief  Sets the heightmap coordinates of this heightmap region.
     * 
     * The value of #Face is not modified by this method.
     * 
     * @param x X-component of heightmap coordinates.
     * @param y Y-component of heightmap coordinates.
     * 
     * @return <b>[not-null]</b>  this
     * 
     * @see #FaceX
     * @see #FaceY
     */
    Ptr<HeightmapRegion> SetCoordinates(int32 x, int32 y);
    
    /*!
     * @brief  Sets the heightmap coordinates of this heightmap region.
     * 
     * @param faceX X-component of cubemap face coordinates.
     * @param faceY Y-component of cubemap face coordinates.
     * @param face The cubemap face (see constants of Cubemap class).
     * 
     * @return <b>[not-null]</b>  this
     * 
     * @see #FaceX
     * @see #FaceY
     * @see #Face
     */
    Ptr<HeightmapRegion> SetCoordinates(int32 faceX, int32 faceY, int32 face);
    
    /*!
     * @brief  Sets the position of the read/write cursor.
     * 
     * The read/write cursor of a heightmap region can be used to access heightmap samples of a 
     * single row.No wrap around is performed,so the result of reading resp. writing beyond the end 
     * of the current row is undefined.
     * 
     * @param x <b>[0..#GetWidth-1]</b>  X-coordinate of new cursor position.
     * @param y <b>[0..#GetHeight-1]</b>  Y-coordinate of new cursor position.
     * 
     * @see #Read
     * @see #Write
     */
    void SetCursor(int32 x, int32 y);
    
    /*!
     * @brief  Shifts the heightmap samples in this region by the given amount.
     * 
     * This method allows heightmap regions to be used in a toroidal manner (ie. as a 
     * two-dimensional ringbuffer).
     * 
     * Specifying a positive value for \e x  will create space for new samples at the left region 
     * border,a negative value for \e x  will create space at the right border.
     * 
     * Specifying a positive value for \e y  will create space for new samples at the top region 
     * border,a negative value for \e y  will create space at the bottom border.
     * 
     * The contents of the heightmap samples in the additional space at the region border is 
     * unspecified and must be set by the application (eg. using #SubRegion).
     * 
     * @param x Horizontal shift amount.
     * @param y Vertical shift amount.
     */
    void Shift(int32 x, int32 y);
    
    /*!
     * @brief  Returns a HeightmapRegion object that represents a subregion of this region.
     * 
     * @param x <b>[0..#GetWidth-width]</b>  X-coordinate of top-left corner of subregion.
     * @param y <b>[0..#GetHeight-height]</b>  Y-coordinate of top-left corner of subregion.
     * @param width <b>[>0]</b>  Width of subregion.
     * @param height <b>[>0]</b>  Height of subregion.
     * 
     * @return <b>[not-null]</b>  The subregion of this heightmap region.
     */
    Ptr<HeightmapRegion> SubRegion(int32 x, int32 y, int32 width, int32 height);
    
    /*!
     * @brief  Writes the given heightmap sample to this heightmap region at the current cursor 
     *         position and increases the cursors X-coordinate.
     * 
     * @param sample <b>[not-null]</b>  The heightmap sample.
     * 
     * @see #SetCursor
     * @see #Read
     */
    void Write(HeightmapSample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The buffer for diffuse color values.
     */
    Ptr<ColorBuffer> colorBuffer;
    
    /*!
     * @brief  Current color buffer read offset.
     */
    int32 colorOffset;
    
    /*!
     * @brief  The samples of the color buffer.
     */
    Array<int32> colorSamples;
    
    /*!
     * @brief  The buffer for detail channel values.
     */
    Ptr<DetailBuffer> detailBuffer;
    
    /*!
     * @brief  Current detail buffer read offset.
     */
    int32 detailOffset;
    
    /*!
     * @brief  The samples of the detail buffer.
     */
    Array<int32> detailSamples;
    
    /*!
     * @brief  The buffer for displacement values.
     */
    Ptr<DisplacementBuffer> displacementBuffer;
    
    /*!
     * @brief  Current displacement buffer read offset.
     */
    int32 displacementOffset;
    
    /*!
     * @brief  The samples of the displacement buffer.
     */
    Array<int32> displacementSamples;
    
    /*!
     * @brief  The buffer for elevation values.
     */
    Ptr<ElevationBuffer> elevationBuffer;
    
    /*!
     * @brief  Current elevation buffer read offset.
     */
    int32 elevationOffset;
    
    /*!
     * @brief  The samples of the elevation buffer.
     */
    Array<int32> elevationSamples;
    
    /*!
     * @brief  The height of this region,in heightmap samples.
     */
    int32 height;
    
    /*!
     * @brief  Optional slope buffer of this heightmap region.
     */
    Ptr<SlopeBuffer> slopeBuffer;
    
    /*!
     * @brief  Does the slope buffer need to be recomputed?
     */
    bool slopeBufferDirty;
    
    /*!
     * @brief  The width of this region,in heightmap samples.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of HeightmapRegion.
     * 
     * @param width The width of this region,in heightmap samples.
     * @param height The height of this region,in heightmap samples.
     * @param elevationBuffer The elevation buffer.
     * @param colorBuffer The color buffer.
     * @param displacementBuffer The displacement buffer.
     * @param detailBuffer The detail buffer.
     */
    HeightmapRegion(int32 width, int32 height, ElevationBuffer* elevationBuffer, ColorBuffer* colorBuffer, DisplacementBuffer* displacementBuffer, DetailBuffer* detailBuffer);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that this heightmap region has a color buffer.
     */
    void AssertHasColorBuffer();
    
    /*!
     * @brief  Asserts that this heightmap region has a detail buffer.
     */
    void AssertHasDetailBuffer();
    
    /*!
     * @brief  Asserts that this heightmap region has a displacement buffer.
     */
    void AssertHasDisplacementBuffer();
    
    /*!
     * @brief  Asserts that this heightmap region has an elevation buffer.
     */
    void AssertHasElevationBuffer();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HeightmapRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6D4A5BEF;
    
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
      return (void*) 0;
    }
  };
  
} } } 

#endif
