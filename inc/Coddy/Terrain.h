////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TERRAIN_H
#define CLODDY_API_TERRAIN_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MapType.h"
#include "Cloddy/MeshFace.h"
#include "Cloddy/TerrainMesh.h"

// Include referenced interfaces.

#include "Cloddy/IDirtyRegionCallback.h"
#include "Cloddy/IFlushable.h"
#include "Cloddy/IUserData.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Geometries { class IGeometry; } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrush; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IStroke; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class ICollisionShape; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class IFrustum; } } }
namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegion; } } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILighting; } } } } }
namespace Cloddy { namespace Kernel { class IMesh; } }
namespace Cloddy { namespace Kernel { class IMeshVisitor; } }
namespace Cloddy { namespace Kernel { class IRefinementProgress; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapPicker; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapRegion; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class MeshDirtyRegionCallback; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class ContactPointInfo; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class PointInfo; } } }
namespace Cloddy { namespace API { namespace Rendering { class MeshBuilder; } } }
namespace Cloddy { namespace API { class TerrainManager; } }
namespace Cloddy { namespace API { class TriangulationOptions; } }
namespace Cloddy { namespace API { namespace Util { class CameraPosition; } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { class DefaultErrorMetric; } } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { class RegionErrorMetric; } } } }
namespace Cloddy { namespace Kernel { class Provider; } }

// Declare class ::Cloddy::API::Terrain.

namespace Cloddy { namespace API
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Util;
  using namespace Cloddy::Kernel;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Geometries::IGeometry;
  using Cloddy::API::Heightmaps::Brushes::IBrush;
  using Cloddy::API::Heightmaps::Brushes::IStroke;
  using Cloddy::API::Heightmaps::IDirtyRegionCallback;
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::API::MeshVisitors::ICollisionShape;
  using Cloddy::API::MeshVisitors::IFrustum;
  using Cloddy::API::Util::Spatial::ITerrainSpaceRegion;
  using Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::ILighting;
  using Cloddy::Core::IO::IFlushable;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::HeightmapPicker;
  using Cloddy::API::Heightmaps::HeightmapRegion;
  using Cloddy::API::Heightmaps::MeshDirtyRegionCallback;
  using Cloddy::API::MeshVisitors::ContactPointInfo;
  using Cloddy::API::MeshVisitors::PointInfo;
  using Cloddy::API::Rendering::MeshBuilder;
  using Cloddy::API::VisibilityCriteria::ErrorMetrics::DefaultErrorMetric;
  using Cloddy::API::VisibilityCriteria::ErrorMetrics::RegionErrorMetric;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  The Terrain class represents a single CLOD mesh and all associated API objects that 
   *         are necessary for typical for most applications.
   */
  class Terrain : public Disposable, public virtual IDirtyRegionCallback, public virtual IUserData, public virtual IFlushable
  {
    // Declare friend classes.
    
    friend class TerrainManager;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Position of the scene camera,in terrain-space.
     * 
     * @return <b>[not-null]</b>  The CameraPosition object that represents the local camera 
     * position of this terrain.
     */
    Ptr<CameraPosition> GetCameraPosition();
    
    /*!
     * @brief  Returns the refinement status for this CLOD terrains collision mesh.
     * 
     * This property must only be used when a collision mesh has been created for this terrain (
     * see #GetCollisionRegion).
     * 
     * @return <b>[not-null]</b>  The refinement status object.
     */
    Ptr<IRefinementProgress> GetCollisionMeshProgress();
    
    /*!
     * @brief  The terrain space region that depicts the terrain regions that are relevant for 
     *         collision detection.
     * 
     * Setting the terrain space region to \c null  will delete the collision mesh (if existing);
     * setting the region to an ITerrainSpaceRegion object will create a new collision mesh resp. 
     * update the existing one.
     * 
     * The collision mesh of a terrain will be paused automatically once refinement has finished (
     * see IRefinementProgress::GetPauseOnFinished).The TerrainManager class checks all paused 
     * collision meshes in its TerrainManager::UpdateTerrains method.If the collision region of 
     * a Terrain has changed (see ITerrainSpaceRegion::HasChanged),refinement for the corresponding 
     * collision mesh will be resumed automatically.
     * 
     * @return The terrain space region or \c null .
     */
    Ptr<ITerrainSpaceRegion> GetCollisionRegion();
    
    /*!
     * @brief  The terrain space region that depicts the terrain regions that are relevant for 
     *         collision detection.
     * 
     * Setting the terrain space region to \c null  will delete the collision mesh (if existing);
     * setting the region to an ITerrainSpaceRegion object will create a new collision mesh resp. 
     * update the existing one.
     * 
     * The collision mesh of a terrain will be paused automatically once refinement has finished (
     * see IRefinementProgress::GetPauseOnFinished).The TerrainManager class checks all paused 
     * collision meshes in its TerrainManager::UpdateTerrains method.If the collision region of 
     * a Terrain has changed (see ITerrainSpaceRegion::HasChanged),refinement for the corresponding 
     * collision mesh will be resumed automatically.
     * 
     * @param value The terrain space region or \c null .
     */
    void SetCollisionRegion(ITerrainSpaceRegion* value);
    
    /*!
     * @brief  The error metric for this terrains render CLOD mesh.
     * 
     * @return <b>[not-null]</b>  The DefaultErrorMetric object.
     */
    Ptr<DefaultErrorMetric> GetErrorMetric();
    
    /*!
     * @brief  The frustum to use for culling when rendering this terrain.
     * 
     * @return The IFrustum to use for culling or \c null  to render the whole terrain.
     */
    Ptr<IFrustum> GetFrustum();
    
    /*!
     * @brief  The frustum to use for culling when rendering this terrain.
     * 
     * @param value The IFrustum to use for culling or \c null  to render the whole terrain.
     */
    void SetFrustum(IFrustum* value);
    
    /*!
     * @brief  Returns the IGeometry object that is used to compute positions of the vertices of 
     *         this terrain.
     * 
     * @return <b>[not-null]</b>  The IGeometry object used by this terrain.
     */
    Ptr<IGeometry> GetGeometry();
    
    /*!
     * @brief  Returns the IHeightmap object of this terrain.
     * 
     * @return <b>[not-null]</b>  The IHeightmap object used by this terrain.
     */
    Ptr<IHeightmap> GetHeightmap();
    
    /*!
     * @brief  The HeightmapPicker of this terrain.
     * 
     * The heightmap picker can be used to pick points in terrain-space directly from the heightmap,
     * which is independent on the current refinement progress of this terrains CLOD mesh.
     * 
     * @return <b>[not-null]</b>  The HeightmapPicker of this terrain.
     */
    Ptr<HeightmapPicker> GetHeightmapPicker();
    
    /*!
     * @brief  The lighting term to use when refining this terrain.
     * 
     * @return The ILighting term to use for refining this terrain or \c null .
     */
    Ptr<ILighting> GetLighting();
    
    /*!
     * @brief  The lighting term to use when refining this terrain.
     * 
     * @param value The ILighting term to use for refining this terrain or \c null .
     */
    void SetLighting(ILighting* value);
    
    /*!
     * @brief  Returns the MapType of this terrain.
     * 
     * @return The MapType value.
     */
    MapType GetMapType();
    
    /*!
     * @brief  Returns the refinement status for this CLOD terrain.
     * 
     * @return <b>[not-null]</b>  The refinement status object.
     */
    Ptr<IRefinementProgress> GetRenderMeshProgress();
    
    /*!
     * @brief  The terrain manager that has created this terrain.
     * 
     * @return <b>[not-null]</b>  The TerrainManager instance.
     */
    Ptr<TerrainManager> GetTerrainManager();
    
    /*!
     * @brief  The triangulation options of the terrain.
     * 
     * @return <b>[not-null]</b>  The triangulation options.
     */
    Ptr<TriangulationOptions> GetTriangulationOptions();
    
    virtual void* GetUserData();
    
    virtual void SetUserData(void* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Applies the given IBrush to the mutable base heightmap of this terrain (
     *         see #GetHeightmap .IHeightmap::GetBaseHeightmap).
     * 
     * The given brush location (the \e center  parameter)is specified in the coordinate space of 
     * this terrains heightmap.It will be transformed into the coordinate space of the terrains 
     * base heightmap.The brush size however will remain unchanged.
     * 
     * @param brush <b>[not-null]</b>  The brush to apply.
     * @param center <b>[not-null]</b>  A PointInfo object that represents the location of the 
     * brush center on the terrain surface.
     * @param heightmapRegion The preallocated heightmap region buffer to use or \c null .
     * 
     * @see #Pick
     */
    void ApplyBrush(IBrush* brush, PointInfo* center, HeightmapRegion* heightmapRegion);
    
    /*!
     * @brief  Applies the given IBrush to the mutable base heightmap of this terrain (
     *         see #GetHeightmap .IHeightmap::GetBaseHeightmap).
     * 
     * The given brush location (the \e centerX ,\e centerY  and \e centerZ  parameters)is 
     * specified in the coordinate space of this terrains heightmap.It will be transformed into the 
     * coordinate space of the terrains base heightmap.The brush size however will remain unchanged.
     * 
     * @param brush <b>[not-null]</b>  The brush to apply.
     * @param centerX Heightmap X-coordinate of brush center on the terrain surface.
     * @param centerY Heightmap Y-coordinate of brush center on the terrain surface.
     * @param centerZ Heightmap Z-coordinate of brush center on the terrain surface.
     * @param heightmapRegion The preallocated heightmap region buffer to use or \c null .
     * 
     * @see #Pick
     */
    void ApplyBrush(IBrush* brush, int32 centerX, int32 centerY, int32 centerZ, HeightmapRegion* heightmapRegion);
    
    /*!
     * @brief  Applies the given IBrush to the mutable base heightmap of this terrain (
     *         see #GetHeightmap .IHeightmap::GetBaseHeightmap).
     * 
     * The given cubemap face coordinates are specified in the heightmap coordinate space of the 
     * mutable base heightmap of this terrain.
     * Use IHeightmap::TransformToBaseHeightmap(const Vec3I&),IHeightmap::TransformToBaseHeightmap(int32,int32,int32) 
     * and IHeightmap::TransformFromBaseHeightmap to convert between heightmap coordinate spaces.
     * 
     * @param brush <b>[not-null]</b>  The brush to apply.
     * @param face The cubemap face of the top-left corner of the brush.
     * @param faceX Cubemap face X-coordinate of the top-left corner of the brush.
     * @param faceY Cubemap face Y-coordinate of the top-left corner of the brush.
     * @param heightmapRegion The preallocated heightmap region buffer to use or \c null .
     * 
     * @see Cubemap
     */
    void ApplyBrushBase(IBrush* brush, int32 face, int32 faceX, int32 faceY, HeightmapRegion* heightmapRegion);
    
    /*!
     * @brief  Begins a stroke on this terrains heightmap.
     * 
     * @param stroke <b>[not-null]</b>  The stroke to begin.
     */
    void BeginStroke(IStroke* stroke);
    
    /*!
     * @brief  Performs collision detection between the given CLOD and triangle mesh.
     * 
     * @param terrainMesh The terrain mesh to use.
     * @param collisionShape <b>[not-null]</b>  The collision shape.
     * @param pointInfoFlags The PointInfo flags.
     * 
     * @return \c true  if at least one contact point has been generated,\c false  if there are no 
     * contact points (ie. no collision has occurred).
     */
    bool Collide(TerrainMesh terrainMesh, ICollisionShape* collisionShape, int32 pointInfoFlags);
    
    /*!
     * @brief  Performs collision detection between the given CLOD and triangle mesh.
     * 
     * @param terrainMesh The terrain mesh to use.
     * @param collisionShape <b>[not-null]</b>  The collision shape.
     * @param contactPoints <b>[not-null]</b>  Output array for contact points.
     * @param contactPointsOffset <b>[>=0]</b>  Offset to start writing into \e contactPoints  
     * array.
     * @param contactPointCount <b>[>=0]</b>  Maximum number of contact points to return.
     * @param pointInfoFlags The PointInfo flags.
     * 
     * @return <b>[>=0]</b>  The number of returned contact points.Will be \c 0  if no collision 
     * has occurred.
     */
    int32 Collide(TerrainMesh terrainMesh, ICollisionShape* collisionShape, Array<Ptr<ContactPointInfo> > contactPoints, int32 contactPointsOffset, int32 contactPointCount, int32 pointInfoFlags);
    
    /*!
     * @brief  Computes the minimum distance from the current camera position to the terrain 
     *         surface.
     * 
     * @param terrainMesh The terrain mesh to use.
     * 
     * @return The distance to the terrain surface,in terrain-space.
     */
    float64 ComputeDistanceToGround(TerrainMesh terrainMesh);
    
    /*!
     * @brief  Computes the minimum distance from the given point in terrain-space to the terrain 
     *         surface.
     * 
     * @param terrainMesh The terrain mesh to use.
     * @param pointX X-coordinate of point,in terrain-space.
     * @param pointY Y-coordinate of point,in terrain-space.
     * @param pointZ Z-coordinate of point,in terrain-space.
     * 
     * @return The distance to the terrain surface,in terrain-space.
     */
    float64 ComputeDistanceToGround(TerrainMesh terrainMesh, float64 pointX, float64 pointY, float64 pointZ);
    
    /*!
     * @brief  Computes the height of the current camera position above the terrain surface.
     * 
     * @param terrainMesh The terrain mesh to use.
     * 
     * @return The height above the terrain surface.
     */
    float64 ComputeHeightAboveGround(TerrainMesh terrainMesh);
    
    /*!
     * @brief  Computes the height of the given point above the terrain surface.
     * 
     * @param terrainMesh The terrain mesh to use.
     * @param pointX X-coordinate of point,in terrain-space.
     * @param pointY Y-coordinate of point,in terrain-space.
     * @param pointZ Z-coordinate of point,in terrain-space.
     * 
     * @return The height above the terrain surface.
     */
    float64 ComputeHeightAboveGround(TerrainMesh terrainMesh, float64 pointX, float64 pointY, float64 pointZ);
    
    /*!
     * @brief  Exports the collision mesh of this terrain using the given MeshBuilder.
     * 
     * This method must only be called when a collision mesh has been created for this terrain (
     * see #GetCollisionRegion).
     * 
     * @param terrainMesh The terrain mesh to use.
     * @param meshBuilder <b>[not-null]</b>  The MeshBuilder object.
     */
    void ExportMesh(TerrainMesh terrainMesh, MeshBuilder* meshBuilder);
    
    virtual void Flush();
    
    virtual void MarkAsDirty(int32 faceX, int32 faceY, int32 face, int32 width, int32 height);
    
    /*!
     * @brief  Performs picking on this terrain along the given ray in terrain-space.
     * 
     * @param terrainMesh The terrain mesh to use.
     * @param pointX X-coordinate of point,in terrain-space.
     * @param pointY Y-coordinate of point,in terrain-space.
     * @param pointZ Z-coordinate of point,in terrain-space.
     * @param directionX X-coordinate of direction vector,in terrain-space.
     * @param directionY Y-coordinate of direction vector,in terrain-space.
     * @param directionZ Z-coordinate of direction vector,in terrain-space.
     * @param pointInfoFlags The PointInfo flags.
     * 
     * @return The picking result as a PointInfo object or \c null  if the given ray does not 
     * intersect the terrain.
     */
    Ptr<PointInfo> Pick(TerrainMesh terrainMesh, float64 pointX, float64 pointY, float64 pointZ, float64 directionX, float64 directionY, float64 directionZ, int32 pointInfoFlags);
    
    /*!
     * @brief  Traverses the vertex hierarchy of this terrain.
     * 
     * @param terrainMesh The terrain mesh to use.
     * @param visitor <b>[not-null]</b>  The mesh visitor object to use.
     * @param userData Optional user data to pass on to visitor.
     */
    void Traverse(TerrainMesh terrainMesh, IMeshVisitor* visitor, int32 userData);
    
    /*!
     * @brief  Triangulates this terrain using the current #GetFrustum and the 
     *         current TriangulationOptions.
     * 
     * @param terrainMesh The terrain mesh to use.
     * @param meshFace The mesh face to triangulate.
     * @param userData Optional user data object to pass on 
     * to ITriangulationCallback::BeginTriangulation.
     */
    void Triangulate(TerrainMesh terrainMesh, MeshFace meshFace, void* userData);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Size of the cubemap for the mutable base heightmap of this terrain,minus one.
     */
    int32 baseCubemapSizeMinusOne;
    
    /*!
     * @brief  The CLOD mesh that represents the current collision mesh of this terrain.
     */
    Ptr<IMesh> collisionMesh;
    
    /*!
     * @brief  The dirty region callback object for the collision CLOD mesh.
     */
    Ptr<MeshDirtyRegionCallback> collisionMeshCallback;
    
    /*!
     * @brief  Size of the cubemap for the heightmap of this terrain,minus one.
     */
    int32 cubemapSizeMinusOne;
    
    /*!
     * @brief  The error metric for this terrains render CLOD mesh.
     */
    Ptr<DefaultErrorMetric> errorMetric;
    
    /*!
     * @brief  The frustum to use for culling when rendering this terrain.
     */
    Ptr<IFrustum> frustum;
    
    /*!
     * @brief  The geometry of this terrain.
     */
    Ptr<IGeometry> geometry;
    
    /*!
     * @brief  The heightmap of this terrain.
     */
    Ptr<IHeightmap> heightmap;
    
    /*!
     * @brief  The HeightmapPicker of this terrain.
     */
    Ptr<HeightmapPicker> heightmapPicker;
    
    /*!
     * @brief  The CLOD mesh used for rendering this terrain.
     */
    Ptr<IMesh> mesh;
    
    /*!
     * @brief  The dirty region callback object for the render CLOD mesh.
     */
    Ptr<MeshDirtyRegionCallback> meshCallback;
    
    /*!
     * @brief  Helper object for performing picking on this terrain.
     */
    Ptr<PointInfo> pointInfo;
    
    /*!
     * @brief  The provider object of this terrains CLOD mesh.
     */
    Ptr<Provider> provider;
    
    /*!
     * @brief  The error metric for this terrains collision CLOD mesh.
     */
    Ptr<RegionErrorMetric> regionErrorMetric;
    
    /*!
     * @brief  The terrain manager that has created this terrain.
     */
    Ptr<TerrainManager> terrainManager;
    
    /*!
     * @brief  The triangulation options of the terrain.
     */
    Ptr<TriangulationOptions> triangulationOptions;
    
    /*!
     * @brief  The current user data object.
     */
    void* userData;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Terrain.
     * 
     * @param terrainManager The terrain manager that owns this terrain.
     * @param mesh The CLOD mesh of this terrain.
     */
    Terrain(TerrainManager* terrainManager, IMesh* mesh);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that the heightmap of this terrain is mutable.
     */
    void AssertHasBaseHeightmap();
    
    /*!
     * @brief  Asserts that a collision mesh has been created for this terrain.
     * 
     * @see #GetCollisionRegion
     */
    void AssertHasCollisionMesh();
    
    /*!
     * @brief  Asserts that a triangulation callback has been configured.
     */
    void AssertHasTriangulationCallback();
    
    /*!
     * @brief  Returns a CLOD mesh of this terrain.
     * 
     * @param terrainMesh The terrain mesh to return.
     * 
     * @return <b>[not-null]</b>  The CLOD mesh.
     */
    Ptr<IMesh> GetMesh(TerrainMesh terrainMesh);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Terrain> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8595F4B5;
    
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
      if ((ptr = IDirtyRegionCallback::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IUserData::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IFlushable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
