////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_STROKE_CUBE_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_STROKE_CUBE_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Box3I.h"
#include "Cloddy/Vec3I.h"

// Include referenced classes.

#include "Cloddy/Stroke.h"

// Forward declare referenced structures.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { struct SlopeInfo; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IDirtyRegionCallback; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace API { namespace Util { namespace Curves { class ICurve; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class Stroke; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapRegion; } } }
namespace Cloddy { namespace API { namespace Util { namespace Curves { class CurveSample; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::Stroke_Cube.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Heightmaps::SampleBuffers::SlopeInfo;
  using Cloddy::API::Util::Box3I;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IDirtyRegionCallback;
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::API::Util::Curves::ICurve;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::HeightmapRegion;
  using Cloddy::API::Util::Curves::CurveSample;
  
  /*!
   * @brief  The Stroke_Cube class is an implementation of the IStroke interface for cubemap 
   *         heightmaps.
   */
  class Stroke_Cube : public Stroke
  {
    // Declare friend classes.
    
    friend class Stroke;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetOverlap();
    
    virtual void SetOverlap(int32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DoBegin(IHeightmap* heightmap, IDirtyRegionCallback* dirtyRegionCallback);
    
    virtual int32 DoEnd();
    
    virtual void DoFinished();
    
    virtual void DoFlush();
    
    virtual void DoPoint(int32 x, int32 y, int32 z, int32 strength);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Bounding box of the best brush location found by #FindIndex.
     */
    Box3I bestBrushBox;
    
    /*!
     * @brief  Coordinates of the best brush location found by #FindIndex.
     */
    Vec3I bestBrushLocation;
    
    /*!
     * @brief  Bounding box of the current brush location.
     */
    Box3I brushBox;
    
    /*!
     * @brief  The brush height,divided by two.
     */
    int32 brushHeightHalf;
    
    /*!
     * @brief  Coordinates of the current brush location.
     */
    Vec3I brushLocation;
    
    /*!
     * @brief  The brush width,divided by two.
     */
    int32 brushWidthHalf;
    
    /*!
     * @brief  Control point index of current brush location.
     */
    float32 controlPointIndex;
    
    /*!
     * @brief  The current ICurve of this stroke.
     */
    Ptr<ICurve> curve;
    
    /*!
     * @brief  The dirty region callback to use.
     */
    Ptr<IDirtyRegionCallback> dirtyRegionCallback;
    
    /*!
     * @brief  The heightmap to paint on.
     */
    Ptr<IHeightmap> heightmap;
    
    /*!
     * @brief  Size of current heightmap,minus one.
     */
    int32 heightmapSizeMinusOne;
    
    /*!
     * @brief  Counts the number of brush applications.
     */
    int32 n;
    
    /*!
     * @brief  Bounding box of the next brush location.
     */
    Box3I nextBrushBox;
    
    /*!
     * @brief  Coordinates of the next brush location.
     */
    Vec3I nextBrushLocation;
    
    /*!
     * @brief  The current relative overlap.
     */
    int32 overlap;
    
    /*!
     * @brief  Bounding box of the brush location that is being probed.
     */
    Box3I probedBrushBox;
    
    /*!
     * @brief  Coordinates of the brush location that is being probed.
     */
    Vec3I probedBrushLocation;
    
    /*!
     * @brief  The heightmap region used for applying the brush.
     */
    Ptr<HeightmapRegion> region;
    
    /*!
     * @brief  The output curve sample object used for evaluating the given curve.
     */
    Ptr<CurveSample> sample;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Stroke_Rect.
     * 
     * @param brush The brush to use.
     * @param mask The brush mask to use.
     * @param slopeInfo The slope info value.
     * @param curve The curve to use.
     */
    Stroke_Cube(IBrush* brush, IBrushMask* mask, const SlopeInfo& slopeInfo, ICurve* curve);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Evaluates the control point curve at the given index.
     * 
     * @param controlPointIndex The control point index.
     * @param brushLocation The output brush location.
     * @param brushBox The output brush bounding box.
     */
    void EvaluateCurve(float32 controlPointIndex, Vec3I& brushLocation, Box3I& brushBox);
    
    /*!
     * @brief  Tries to find the control point index of the next brush application.
     * 
     * @param maxIndex The maximum control point index.
     * 
     * @return \c true  if a suitable control point index has been found,\c false  if not.
     */
    bool FindIndex(float32 maxIndex);
    
    /*!
     * @brief  Performs painting up to the given maximum control point index.
     * 
     * @param maxControlPointIndex The maximum control point index.
     */
    void Paint(int32 maxControlPointIndex);
    
    /*!
     * @brief  Computes the relative overlap between the current brush location and the brush 
     *         located at the given curve index.
     * 
     * @param index The curve control point index.
     * 
     * @return The relative overlap in the interval <c>[0..100]</c>.
     */
    int32 Probe(float32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Stroke_Cube> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x45D0E23C;
    
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
      if ((ptr = Stroke::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
