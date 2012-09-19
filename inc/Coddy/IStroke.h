////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_ISTROKE_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_ISTROKE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"
#include "Cloddy/IFlushable.h"
#include "Cloddy/ITerrainSlopeDependant.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IDirtyRegionCallback; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class PointInfo; } } }

// Declare interface ::Cloddy::API::Heightmaps::Brushes::IStroke.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IDirtyRegionCallback;
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::Core::IO::IFlushable;
  using CodeX::System::IDisposable;
  
  // Use referenced classes.
  
  using Cloddy::API::MeshVisitors::PointInfo;
  
  /*!
   * @brief  Base interface for classes that apply a stroke of brushes to a heightmap.
   * 
   * A stroke consists of a path that is interpolated between a given number of control points (
   * see ICurve)and a brush which is applied at multiple locations along that path (see IBrush):
   * <pre>
   *      +---------+
   *      |         |
   *      |       ###-------+
   *      |    o  ###       |
   *      |       ###       |
   *      |       ###  o    |
   *      +-------###   #####-----+
   *      |     #####     |
   *      +-----#####     |
   *      |    o    |
   *      |         |
   *      |         |
   *      +---------+
   *      o := Interpolated points along the path
   *      # := Overlapping regions
   * </pre>
   * In order to give the stroke a uniform appearance,the locations along the path at which the 
   * brush is be applied are chosen according to a given relative overlap (see #GetOverlap).The 
   * relative overlap is the ratio between the overlapping regions of two adjacent brush 
   * applications and the brush area.The points at which the given path is evaluated are chosen to 
   * meet this requirement.
   * 
   * Painting on a heightmap using a IStroke is performed via the following steps:
   *   -# Create an IStroke instance or use an existing one.
   *   -# Begin a new stroke by calling #Begin(IHeightmap*,IDirtyRegionCallback*).
   *   -# Define the stroke path by adding control points via #Point(int32,int32,int32,int32) for 
   *   rectangular heightmaps and #Point(int32,int32,int32,int32) for cubemap heightmaps.
   *   -# Finish the path of the stroke by calling #Finished (optional).
   *   -# End the stroke by calling #End.
   * The following figure illustrates the states of an IStroke object and the possible state 
   * transitions (after instantiation,an IStroke object is in state \c Inactive ):
   * <pre>
   *      +--------------+
   *      |   Inactive   | &lt;--------------------+
   *      +--------------+                      |
   *      ^        |                         |
   *      | End()  | Begin(...)              | End()
   *      |        V                         |
   *      +--------------+              +--------------+
   *      +--> |   Painting   | -----------> |   Finished   | &lt;--+
   *      |    +--------------+  Finished()  +--------------+    |
   *      |           |                              |           |
   *      +-----------+                              +-----------+
   *      Point(...)                                  Flush()
   *      Flush()
   * </pre>
   */
  class NO_VTABLE IStroke : public virtual ITerrainSlopeDependant, public virtual IFlushable, public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The current IBrush of this stroke.
     * 
     * @return <b>[not-null]</b>  The brush of this stroke.
     */
    virtual Ptr<IBrush> GetBrush() = 0;
    
    /*!
     * @brief  The current IBrushMask of this stroke.
     * 
     * @return The brush mask of this stroke or \c null .
     */
    virtual Ptr<IBrushMask> GetBrushMask() = 0;
    
    /*!
     * @brief  Has all painting for the current stroke been performed (ie. calling the #End method 
     *         will result in no extra work)?
     * 
     * @return \c true  if all painting has been performed,\c false  if not.
     */
    virtual bool IsComplete() = 0;
    
    /*!
     * @brief  Has the current stroke finished (ie. the #Finished method has been called)?
     * 
     * When a stroke has been finished,no more control points can be added 
     * via #Point(int32,int32,int32,int32).
     * 
     * @return \c true  if the current stroke has finished,\c false  if not.
     */
    virtual bool IsFinished() = 0;
    
    /*!
     * @brief  Is this stroke current inactive?
     * 
     * @return \c true  if the stroke is inactive,\c false  if not.
     */
    virtual bool IsInactive() = 0;
    
    /*!
     * @brief  Is this stroke currently painting?
     * 
     * @return \c true  if the stroke is currently painting (ie. 
     * the #Begin(IHeightmap*,IDirtyRegionCallback*) method has been called and the stroke has not 
     * yet been ended via #End),\c false  if the stroke is not painting at the moment.
     */
    virtual bool IsPainting() = 0;
    
    /*!
     * @brief  Specifies the maximum euclidean distance between control points.
     * 
     * If a control point is added via #Point(int32,int32,int32,int32),#Point(PointInfo*,int32) and 
     * the euclidean distance between the new point and the last point is greater this this value,
     * the control point is silently dropped.
     * 
     * <b>Note:</b> The euclidean distance is computed in the coordinate space of the mutable base 
     * heightmap of the heightmap that has been specified 
     * via #Begin(IHeightmap*,IDirtyRegionCallback*).
     * 
     * The default value is \c 256 .
     * 
     * @return <b>[>0]</b>  The maximum distance between control points.
     */
    virtual int32 GetMaximumPointDistance() = 0;
    
    /*!
     * @brief  Specifies the maximum euclidean distance between control points.
     * 
     * If a control point is added via #Point(int32,int32,int32,int32),#Point(PointInfo*,int32) and 
     * the euclidean distance between the new point and the last point is greater this this value,
     * the control point is silently dropped.
     * 
     * <b>Note:</b> The euclidean distance is computed in the coordinate space of the mutable base 
     * heightmap of the heightmap that has been specified 
     * via #Begin(IHeightmap*,IDirtyRegionCallback*).
     * 
     * The default value is \c 256 .
     * 
     * @param value <b>[>0]</b>  The maximum distance between control points.
     */
    virtual void SetMaximumPointDistance(int32 value) = 0;
    
    /*!
     * @brief  The overlap (relative)between brush applications.
     * 
     * The default value is \c 75 ,ie. adjacent brushes must overlap by 75%.
     * 
     * @return <b>[1..99]</b>  The relative overlap in percent.
     */
    virtual int32 GetOverlap() = 0;
    
    /*!
     * @brief  The overlap (relative)between brush applications.
     * 
     * The default value is \c 75 ,ie. adjacent brushes must overlap by 75%.
     * 
     * @param value <b>[1..99]</b>  The relative overlap in percent.
     */
    virtual void SetOverlap(int32 value) = 0;
    
    /*!
     * @brief  Returns a threaded version of this stroke.
     * 
     * A threaded stroke performs all painting asynchronously in a background thread.
     * 
     * @return <b>[not-null]</b>  The threaded stroke.
     */
    virtual Ptr<IStroke> GetThreaded() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Begins a new stroke on the given heightmap.
     * 
     * Painting is performed on the mutable base heightmap of the given heightmap (
     * see IHeightmap::GetBaseHeightmap).
     * 
     * All control points that are added 
     * via #Point(int32,int32,int32,int32),#Point(PointInfo*,int32) are automatically translated 
     * from the coordinate space of \e heightmap  to that of its mutable base heightmap.
     * 
     * <b>Note:</b> The size of the used brush (see #GetBrush)is relative to the dimensions of the 
     * mutable base heightmap of \e heightmap .
     * 
     * @param heightmap <b>[not-null]</b>  The heightmap to paint on.
     * @param dirtyRegionCallback Optional callback for marking dirty regions while painting.
     */
    virtual void Begin(IHeightmap* heightmap, IDirtyRegionCallback* dirtyRegionCallback) = 0;
    
    /*!
     * @brief  Ends the current stroke.
     * 
     * After a stroke has ended,a new one can be started 
     * with #Begin(IHeightmap*,IDirtyRegionCallback*).
     * 
     * @return <b>[>0]</b>  The number of times the brush has been applied to the heightmap.
     */
    virtual int32 End() = 0;
    
    /*!
     * @brief  Tells this stroke that no more control points will be added.
     */
    virtual void Finished() = 0;
    
    /*!
     * @brief  Adds a control point to this stroke.
     * 
     * @param x X-component of heightmap coordinates of the control point.
     * @param y Y-component of heightmap coordinates of the control point.
     * @param z Z-component of heightmap coordinates of the control point.
     * @param strength <b>[0..1024]</b>  The relative brush IBrush::GetStrength.
     */
    virtual void Point(int32 x, int32 y, int32 z, int32 strength) = 0;
    
    /*!
     * @brief  Adds a control point to this stroke.
     * 
     * @param pointInfo <b>[not-null]</b>  The control point.
     * @param strength <b>[0..1024]</b>  The relative brush IBrush::GetStrength.
     */
    virtual void Point(PointInfo* pointInfo, int32 strength) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IStroke> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6495CED3;
    
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
      if ((ptr = ITerrainSlopeDependant::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IFlushable::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } 

#endif
