////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TERRAINMANAGER_H
#define CLODDY_API_TERRAINMANAGER_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Handedness.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Include referenced interfaces.

#include "Cloddy/IUserData.h"

// Include referenced classes.

#include "CodeX/Disposable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Geometries { class IGeometry; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexDataCollection; } } }
namespace Cloddy { namespace API { namespace VertexFactories { namespace VertexFormats { class IVertexFormat; } } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Kernel { class IVertexBuffer; } }
namespace Cloddy { namespace Kernel { class IVertexBufferCollection; } }
namespace Cloddy { namespace Kernel { class IVertexFactory; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace MeshVisitors { class CollisionDetection; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class DistanceToGround; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class FrustumCulling; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class HeightAboveGround; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class Picking; } } }
namespace Cloddy { namespace API { namespace Rendering { class MeshBuilder; } } }
namespace Cloddy { namespace API { class Terrain; } }
namespace Cloddy { namespace API { namespace Util { class PerspectiveProjection; } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { class ScreenSpaceVisibilityCriterion; } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { class TerrainSpaceVisibilityCriterion; } } }
namespace Cloddy { namespace Kernel { class CloddyKernel; } }
namespace Cloddy { namespace Kernel { class CloddyKernelOptions; } }

// Declare class ::Cloddy::API::TerrainManager.

namespace Cloddy { namespace API
{
  // Use referenced namespaces.
  
  using namespace Cloddy::API::Geometries;
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::IHeightmap;
  using Cloddy::API::VertexData::IVertexDataCollection;
  using Cloddy::API::VertexFactories::VertexFormats::IVertexFormat;
  using Cloddy::Core::Collections::IList;
  using Cloddy::Kernel::IUserData;
  using Cloddy::Kernel::IVertexBuffer;
  using Cloddy::Kernel::IVertexBufferCollection;
  using Cloddy::Kernel::IVertexFactory;
  
  // Use referenced classes.
  
  using Cloddy::API::MeshVisitors::CollisionDetection;
  using Cloddy::API::MeshVisitors::DistanceToGround;
  using Cloddy::API::MeshVisitors::FrustumCulling;
  using Cloddy::API::MeshVisitors::HeightAboveGround;
  using Cloddy::API::MeshVisitors::Picking;
  using Cloddy::API::Rendering::MeshBuilder;
  using Cloddy::API::Util::PerspectiveProjection;
  using Cloddy::API::VisibilityCriteria::ScreenSpaceVisibilityCriterion;
  using Cloddy::API::VisibilityCriteria::TerrainSpaceVisibilityCriterion;
  using Cloddy::Kernel::CloddyKernel;
  using Cloddy::Kernel::CloddyKernelOptions;
  using CodeX::System::Disposable;
  
  /*!
   * @brief  The TerrainManager class is a helper for quickly initializing the CloddySDK.
   * 
   * This class wraps the components in the CloddySDK in an easy to use facade.It is designed to 
   * facilitate the first steps with the CloddySDK.
   */
  class TerrainManager : public Disposable, public virtual IUserData
  {
    // Declare friend classes.
    
    friend class Terrain;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The shared TerrainSpaceVisibilityCriterion object used for generating collision 
     *         meshes for Terrain objects.
     * 
     * @return <b>[not-null]</b>  The TerrainSpaceVisibilityCriterion object.
     * 
     * @see Terrain::GetCollisionRegion
     */
    Ptr<TerrainSpaceVisibilityCriterion> GetAccuracyCriterion();
    
    /*!
     * @brief  The shared FrustumCulling object used by all Terrain objects created with this 
     *         terrain manager.
     * 
     * @return <b>[not-null]</b>  The FrustumCulling object.
     */
    Ptr<FrustumCulling> GetFrustumCulling();
    
    /*!
     * @brief  The coordinate system handedness to use when creating new terrains.
     * 
     * The TerrainManager uses default implementations of the IGeometry interface.These 
     * implementations correctly reflect the underlying heightmaps iff the application is using a 
     * right handed coordinate system.When using a left handed coordinate system,applications can 
     * set this property to Handedness::Handedness_LeftHanded;newly created terrains will then be 
     * flipped along the terrain space Z-axis so that the heightmap data is rendered correctly.
     * 
     * The default value is Handedness::Handedness_RightHanded.
     * 
     * @return The coordinate system handedness to use.
     */
    Handedness GetGeometryHandedness();
    
    /*!
     * @brief  The coordinate system handedness to use when creating new terrains.
     * 
     * The TerrainManager uses default implementations of the IGeometry interface.These 
     * implementations correctly reflect the underlying heightmaps iff the application is using a 
     * right handed coordinate system.When using a left handed coordinate system,applications can 
     * set this property to Handedness::Handedness_LeftHanded;newly created terrains will then be 
     * flipped along the terrain space Z-axis so that the heightmap data is rendered correctly.
     * 
     * The default value is Handedness::Handedness_RightHanded.
     * 
     * @param value The coordinate system handedness to use.
     */
    void SetGeometryHandedness(Handedness value);
    
    /*!
     * @brief  The initial camera position value to use when creating Terrains.
     * 
     * The default value is <c>(0,0,0)</c>.
     * 
     * @return The initial camera position,in terrain-space.
     */
    Vec3D GetInitialCameraPosition();
    
    /*!
     * @brief  The initial camera position value to use when creating Terrains.
     * 
     * The default value is <c>(0,0,0)</c>.
     * 
     * @param value The initial camera position,in terrain-space.
     */
    void SetInitialCameraPosition(const Vec3D& value);
    
    /*!
     * @brief  The shared PerspectiveProjection object used by all Terrain objects created with 
     *         this terrain manager.
     * 
     * @return <b>[not-null]</b>  The PerspectiveProjection object.
     */
    Ptr<PerspectiveProjection> GetProjection();
    
    virtual void* GetUserData();
    
    virtual void SetUserData(void* value);
    
    /*!
     * @brief  The application vertex data containers.
     * 
     * @return <b>[not-null]</b>  The vertex data containers.
     */
    Ptr<IVertexDataCollection> GetVertexDataCollection();
    
    /*!
     * @brief  The vertex layout used by this terrain manager.
     * 
     * @return <b>[not-null]</b>  The used vertex layout.
     */
    Ptr<IVertexFormat> GetVertexFormat();
    
    /*!
     * @brief  The shared ScreenSpaceVisibilityCriterion object used by all Terrain objects created 
     *         with this terrain manager.
     * 
     * @return <b>[not-null]</b>  The ScreenSpaceVisibilityCriterion object.
     */
    Ptr<ScreenSpaceVisibilityCriterion> GetVisibilityCriterion();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of TerrainManager.
     * 
     * @param vertexBuffer <b>[not-null]</b>  The vertex buffer to use for storing vertex data of 
     * the terrains that are created by this terrain manager.
     * @param vertexFormat The vertex format to use.
     */
    TerrainManager(IVertexBuffer* vertexBuffer, IVertexFormat* vertexFormat);
    
    /*!
     * @brief  Creates a new instance of TerrainManager.
     * 
     * @param vertexBuffers <b>[not-null]</b>  The vertex buffers to use for storing vertex data of 
     * the terrains that are created by this terrain manager.
     * @param vertexFormat The vertex format to use.
     */
    TerrainManager(IVertexBufferCollection* vertexBuffers, IVertexFormat* vertexFormat);
    
    /*!
     * @brief  Creates a new instance of TerrainManager.
     * 
     * @param options <b>[not-null]</b>  The options to use for creating the Cloddy Kernel.
     * @param vertexBuffer <b>[not-null]</b>  The vertex buffer to use for storing vertex data of 
     * the terrains that are created by this terrain manager.
     * @param vertexFormat The vertex format to use.
     */
    TerrainManager(CloddyKernelOptions* options, IVertexBuffer* vertexBuffer, IVertexFormat* vertexFormat);
    
    /*!
     * @brief  Creates a new instance of TerrainManager.
     * 
     * @param options <b>[not-null]</b>  The options to use for creating the Cloddy Kernel.
     * @param vertexBuffers <b>[not-null]</b>  The vertex buffers to use for storing vertex data of 
     * the terrains that are created by this terrain manager.
     * @param vertexFormat The vertex format to use.
     */
    TerrainManager(CloddyKernelOptions* options, IVertexBufferCollection* vertexBuffers, IVertexFormat* vertexFormat);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a curved terrain.
     * 
     * A curved terrain uses a SphereSectorGeometry object for computing vertex positions.
     * 
     * @param width <b>[>0]</b>  Width of the terrain,in terrain-space.
     * @param height <b>[>0]</b>  Height of the terrain,in terrain-space.
     * @param elevation <b>[>=0]</b>  The maximum terrain elevation,in terrain-space.
     * @param displacement <b>[>=0]</b>  The maximum terrain displacement per axis,in terrain-space.
     * @param radius <b>[>0]</b>  The radius of the base sphere,in terrain-space.
     * @param heightmap <b>[not-null]</b>  The heightmap to use.
     * 
     * @return <b>[not-null]</b>  The created Terrain object.
     */
    Ptr<Terrain> CreateCurvedTerrain(float32 width, float32 height, float32 elevation, float32 displacement, float32 radius, IHeightmap* heightmap);
    
    /*!
     * @brief  Creates a terrain that uses a custom geometry.
     * 
     * @param heightmap <b>[not-null]</b>  The heightmap to use.
     * @param geometry <b>[not-null]</b>  The geometry to use.
     * 
     * @return <b>[not-null]</b>  The created terrain.
     */
    Ptr<Terrain> CreateCustomTerrain(IHeightmap* heightmap, IGeometry* geometry);
    
    /*!
     * @brief  Creates a MeshBuilder object for this terrain manager.
     * 
     * @param initialVertexCount <b>[>0]</b>  Initial vertex count of exported triangle mesh.
     * @param initialIndexCount <b>[>0]</b>  Initial index count of exported triangle mesh.
     * 
     * @return <b>[not-null]</b>  The created mesh builder object.
     */
    Ptr<MeshBuilder> CreateMeshBuilder(int32 initialVertexCount, int32 initialIndexCount);
    
    /*!
     * @brief  Creates a planetary terrain.
     * 
     * A planetary terrain uses a SphereGeometry object for computing vertex positions.
     * 
     * @param radius <b>[>0]</b>  The radius of the base sphere,in terrain-space.
     * @param elevation <b>[>=0]</b>  The maximum terrain elevation,in terrain-space.
     * @param displacement <b>[>=0]</b>  The maximum terrain displacement per axis,in terrain-space.
     * @param heightmap <b>[not-null]</b>  The heightmap to use.
     * 
     * @return <b>[not-null]</b>  The created Terrain object.
     */
    Ptr<Terrain> CreatePlanetaryTerrain(float32 radius, float32 elevation, float32 displacement, IHeightmap* heightmap);
    
    /*!
     * @brief  Creates a rectangular terrain.
     * 
     * A rectangular terrain uses a SquareGeometry object for computing vertex positions.
     * 
     * @param width <b>[>0]</b>  Width of the terrain,in terrain-space.
     * @param height <b>[>0]</b>  Height of the terrain,in terrain-space.
     * @param elevation <b>[>=0]</b>  The maximum terrain elevation,in terrain-space.
     * @param displacement <b>[>=0]</b>  The maximum terrain displacement per axis,in terrain-space.
     * @param heightmap <b>[not-null]</b>  The heightmap to use.
     * 
     * @return <b>[not-null]</b>  The created Terrain object.
     */
    Ptr<Terrain> CreateRectangularTerrain(float32 width, float32 height, float32 elevation, float32 displacement, IHeightmap* heightmap);
    
    /*!
     * @brief  Updates all terrains with new data from background refinement.
     * 
     * The collision regions (see Terrain::GetCollisionRegion)of all Terrains will be tested for 
     * pending changes.For this,the ITerrainSpaceRegion::HasChanged method will be called for each 
     * terrain that has a collision mesh.If a collision region has changed,refinement will 
     * automatically be resumed for the corresponding collision mesh.
     */
    void UpdateTerrains();
    
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
     * @brief  The shared TerrainSpaceVisibilityCriterion object used for generating collision 
     *         meshes for Terrain objects.
     */
    Ptr<TerrainSpaceVisibilityCriterion> accuracyCriterion;
    
    /*!
     * @brief  The shared CollisionDetection object used for performing collision detection.
     */
    Ptr<CollisionDetection> collisionDetection;
    
    /*!
     * @brief  Helper object for computing the distance to ground.
     */
    Ptr<DistanceToGround> distanceToGround;
    
    /*!
     * @brief  The shared frustum culling object for all terrains.
     */
    Ptr<FrustumCulling> frustumCulling;
    
    /*!
     * @brief  The coordinate system handedness to use when creating new terrains.
     */
    Handedness geometryHandedness;
    
    /*!
     * @brief  Helper object for computing the height above ground.
     */
    Ptr<HeightAboveGround> heightAboveGround;
    
    /*!
     * @brief  The initial camera position value to use when creating Terrains.
     */
    Vec3D initialCameraPosition;
    
    /*!
     * @brief  The Cloddy Kernel.
     */
    Ptr<CloddyKernel> kernel;
    
    /*!
     * @brief  Helper object for performing CLOD mesh picking.
     */
    Ptr<Picking> picking;
    
    /*!
     * @brief  The shared projection for all terrains.
     */
    Ptr<PerspectiveProjection> projection;
    
    /*!
     * @brief  The created Terrain objects.
     */
    Ptr<IList<Ref<Terrain> > > terrains;
    
    /*!
     * @brief  The current user data object.
     */
    void* userData;
    
    /*!
     * @brief  The application vertex buffer.
     */
    Ptr<IVertexBufferCollection> vertexBuffers;
    
    /*!
     * @brief  The application vertex data containers.
     */
    Ptr<IVertexDataCollection> vertexDataCollection;
    
    /*!
     * @brief  Vertex factory for MapType::MapType_Rect meshes.
     */
    Ptr<IVertexFactory> vertexFactory;
    
    /*!
     * @brief  The application vertex layout.
     */
    Ptr<IVertexFormat> vertexFormat;
    
    /*!
     * @brief  The shared visibility criterion for all terrains.
     */
    Ptr<ScreenSpaceVisibilityCriterion> visibilityCriterion;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Initializes this terrain manager instance.
     * 
     * @param options The cloddy kernel options to use.
     */
    void Initialize(CloddyKernelOptions* options);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<TerrainManager> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE5FE0B5C;
    
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
      if ((ptr = IUserData::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
