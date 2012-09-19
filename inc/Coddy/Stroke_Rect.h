////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_STROKE_RECT_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_STROKE_RECT_H

#include "CodeX/System.h"

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

// Declare class ::Cloddy::API::Heightmaps::Brushes::Stroke_Rect.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Heightmaps::SampleBuffers::SlopeInfo;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IDirtyRegionCallback;
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::API::Util::Curves::ICurve;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::HeightmapRegion;
  using Cloddy::API::Util::Curves::CurveSample;
  
  /*!
   * @brief  The Stroke_Rect class is an implementation of the IStroke interface for rectangular 
   *         heightmaps.
   */
  class Stroke_Rect : public Stroke
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
     * @brief  X-coordinate of top-left corner of current brush location.
     */
    int32 brushX;
    
    /*!
     * @brief  Y-coordinate of top-left corner of current brush location.
     */
    int32 brushY;
    
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
     * @brief  Counts the number of brush applications.
     */
    int32 n;
    
    /*!
     * @brief  X-coordinate of top-left corner of next brush location.
     */
    int32 nextBrushX;
    
    /*!
     * @brief  Y-coordinate of top-left corner of next brush location.
     */
    int32 nextBrushY;
    
    /*!
     * @brief  The current relative overlap.
     */
    int32 overlap;
    
    /*!
     * @brief  X-coordinate of probed brush location (see #Probe).
     */
    int32 probedX;
    
    /*!
     * @brief  Y-coordinate of probed brush location (see #Probe).
     */
    int32 probedY;
    
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
    Stroke_Rect(IBrush* brush, IBrushMask* mask, const SlopeInfo& slopeInfo, ICurve* curve);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Tries to find the control point index of the next brush application.
     * 
     * The following fields are set by this method:
     *   - <i>out </i>#controlPointIndex
     *   - <i>out </i>#nextBrushX
     *   - <i>out </i>#nextBrushY
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
     * @brief  Computes the relative overlap between the current brush location (see #brushX 
     *         and #brushY)and the brush located at the given curve index.
     * 
     * The X- and Y-coordinates of the top-left corner of the probed brush location are stored 
     * in #probedX and #probedY.
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
    public: typedef Ptr<Stroke_Rect> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x215EF7ED;
    
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
