////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_STROKE_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_STROKE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Continuity.h"
#include "Cloddy/MapType.h"

// Include referenced structures.

#include "Cloddy/Vec3I.h"

// Include referenced interfaces.

#include "Cloddy/IStroke.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced structures.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers { struct SlopeInfo; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IDirtyRegionCallback; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace API { namespace Util { namespace Curves { class ICurve; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class PointInfo; } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::Stroke.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Util;
  using namespace Cloddy::API::Util::Curves;
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Heightmaps::SampleBuffers::SlopeInfo;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IDirtyRegionCallback;
  using Cloddy::API::Heightmaps::IHeightmap;
  
  // Use referenced classes.
  
  using Cloddy::API::MeshVisitors::PointInfo;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  Abstract base implementation of the IStroke interface.
   */
  class Stroke : public Disposable, public virtual IStroke
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IBrush> GetBrush();
    
    virtual Ptr<IBrushMask> GetBrushMask();
    
    virtual bool DoesUseSlope();
    
    virtual bool IsComplete();
    
    virtual bool IsFinished();
    
    virtual bool IsInactive();
    
    virtual bool IsPainting();
    
    virtual int32 GetMaximumPointDistance();
    
    virtual void SetMaximumPointDistance(int32 value);
    
    virtual int32 GetOverlap() = 0;
    
    virtual void SetOverlap(int32 value) = 0;
    
    virtual Ptr<IStroke> GetThreaded();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Stroke.
     * 
     * @param mapType The map type of the target heightmap.
     * @param brush <b>[not-null]</b>  The brush to use.
     * @param mask Optional brush mask to use.
     * @param continuity The desired continuity for stroke path interpolation.
     * 
     * @return <b>[not-null]</b>  The IStroke object.
     */
    static Ptr<IStroke> Create(MapType mapType, IBrush* brush, IBrushMask* mask, Continuity continuity);
    
    /*!
     * @brief  Creates a new instance of Stroke.
     * 
     * @param mapType The map type of the target heightmap.
     * @param brush <b>[not-null]</b>  The brush to use.
     * @param mask Optional brush mask to use.
     * @param slopeInfo The slope info value to use for computing terrain slope values.
     * @param continuity The desired continuity for stroke path interpolation.
     * 
     * @return <b>[not-null]</b>  The IStroke object.
     */
    static Ptr<IStroke> Create(MapType mapType, IBrush* brush, IBrushMask* mask, const SlopeInfo& slopeInfo, Continuity continuity);
    
    /*!
     * @brief  Creates a new instance of Stroke.
     * 
     * @param mapType The map type of the target heightmap.
     * @param brush <b>[not-null]</b>  The brush to use.
     * @param mask Optional brush mask to use.
     * @param curve <b>[not-null]</b>  The curve to use.
     * 
     * @return <b>[not-null]</b>  The IStroke object.
     */
    static Ptr<IStroke> Create(MapType mapType, IBrush* brush, IBrushMask* mask, ICurve* curve);
    
    /*!
     * @brief  Creates a new instance of Stroke.
     * 
     * @param mapType The map type of the target heightmap.
     * @param brush <b>[not-null]</b>  The brush to use.
     * @param mask Optional brush mask to use.
     * @param slopeInfo The slope info value to use for computing terrain slope values.
     * @param curve <b>[not-null]</b>  The curve to use.
     * 
     * @return <b>[not-null]</b>  The IStroke object.
     */
    static Ptr<IStroke> Create(MapType mapType, IBrush* brush, IBrushMask* mask, const SlopeInfo& slopeInfo, ICurve* curve);
    
    virtual void Begin(IHeightmap* heightmap, IDirtyRegionCallback* dirtyRegionCallback);
    
    virtual int32 End();
    
    virtual void Finished();
    
    virtual void Flush();
    
    virtual void Point(PointInfo* pointInfo, int32 strength);
    
    virtual void Point(int32 x, int32 y, int32 z, int32 strength);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The brush of this stroke.
     */
    Ptr<IBrush> brush;
    
    /*!
     * @brief  The brush mask.
     */
    Ptr<IBrushMask> mask;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Stroke.
     * 
     * @param brush <b>[not-null]</b>  The brush to use.
     * @param mask Optional brush mask to use.
     */
    Stroke(IBrush* brush, IBrushMask* mask);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that this IStroke instance is in state \c Inactive .
     * 
     * @exception FailedAssertionException If the assertion fails.
     */
    void AssertInactive();
    
    /*!
     * @brief  Asserts that this IStroke instance is in state \c Painting .
     * 
     * @exception FailedAssertionException If the assertion fails.
     */
    void AssertPainting();
    
    /*!
     * @brief  Asserts that this IStroke instance is in state \c Painting  or \c Finished .
     * 
     * @exception FailedAssertionException If the assertion fails.
     */
    void AssertPaintingOrFinished();
    
    virtual void DisposeManaged();
    
    /*!
     * @brief  Performs the transition from \c Inactive  to \c Painting .
     * 
     * @param heightmap The heightmap to paint on.
     * @param dirtyRegionCallback The dirty region callback to use.
     */
    virtual void DoBegin(IHeightmap* heightmap, IDirtyRegionCallback* dirtyRegionCallback) = 0;
    
    /*!
     * @brief  Performs the transition from \c Finished  to \c Inactive .
     * 
     * @return <b>[>=0]</b>  The number of times the brush has been applied.
     */
    virtual int32 DoEnd() = 0;
    
    /*!
     * @brief  Performs the transition from \c Painting  to \c Finished .
     */
    virtual void DoFinished() = 0;
    
    /*!
     * @brief  Flushes the painting while in \c Painting  or \c Finished  state.
     */
    virtual void DoFlush() = 0;
    
    /*!
     * @brief  Adds a new point while in \c Painting  state.
     * 
     * @param x X-coordinate of point.
     * @param y Y-coordinate of point.
     * @param z Z-coordinate of point.
     * @param strength The relative strength of the point.
     */
    virtual void DoPoint(int32 x, int32 y, int32 z, int32 strength) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Has a stroke begun?
     */
    bool hasBegun;
    
    /*!
     * @brief  Does #lastPoint contain a valid value?
     */
    bool hasLastPoint;
    
    /*!
     * @brief  The IHeightmap that has been specified via #Begin(IHeightmap*,IDirtyRegionCallback*).
     */
    Ptr<IHeightmap> heightmap;
    
    /*!
     * @brief  Has the path of the stroke been finished?
     */
    bool isFinished;
    
    /*!
     * @brief  Holds the coordinates of the last point provided via #Point(int32,int32,int32,int32) 
     *         resp. #Point(PointInfo*,int32).
     */
    Vec3I lastPoint;
    
    /*!
     * @brief  The maximum allowed distance between control points.
     */
    int32 maximumPointDistance;
    
    /*!
     * @brief  Square value of #maximumPointDistanceSqr.
     */
    int64 maximumPointDistanceSqr;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Stroke> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7437559C;
    
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
      if ((ptr = Disposable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IStroke::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
