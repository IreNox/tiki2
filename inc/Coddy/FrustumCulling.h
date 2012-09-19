////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_FRUSTUMCULLING_H
#define CLODDY_API_MESHVISITORS_FRUSTUMCULLING_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/MeshFace.h"

// Include referenced interfaces.

#include "Cloddy/IMeshVisitor.h"

// Include referenced structures.

#include "Cloddy/Mat4D.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace MeshVisitors { class IFrustum; } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IMesh; } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { class CameraPosition; } } }
namespace Cloddy { namespace API { namespace Util { class PerspectiveProjection; } } }
namespace Cloddy { namespace API { namespace VertexData { class Int1; } } }
namespace Cloddy { namespace Kernel { class Traversal; } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Mat4D; } } } }

// Declare class ::Cloddy::API::MeshVisitors::FrustumCulling.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Kernel;
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::CameraPosition;
  using Cloddy::API::Util::PerspectiveProjection;
  using Cloddy::API::VertexData::Int1;

  // Use referenced structures.

  using Cloddy::Core::Math::Vectors::Mat4D;
  
  /*!
   * @brief  This class is an IMeshVisitor that performs frustum culling.
   * 
   * Each visited mesh sector is tested against the frustum.If it lies outside the frustum,the 
   * traversal of that branch ends.It it lies inside the frustum,the mesh sector is triangulated (
   * eg. rendered).If the mesh sector intersects the frustum,the traversal is continued until one 
   * of the first two cases occur.
   * 
   * The following components of the CloddySDK are used by this class (\e opt  means that the 
   * component will be used if present,\e req  means that the component must be present):
   *   - \e req  - ComponentIdsApi::Opt_PerspectiveProjection
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e req  - Semantic::Position
   *   - \e req  - Semantic::Radius
   *   - \e opt  - Semantic::ElevationMin
   *   - \e opt  - Semantic::ElevationMax
   */
  class FrustumCulling : public virtual IMeshVisitor
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  A bitmask that indicates the frustum planes that will not be tested.Each bit 
     *         corresponds to one frustum plane (IFrustum::TestSphere).
     * 
     * Setting the bitmask to \c 0x7FFFFFFF  will disable frustum culling;setting it to \c 0  will 
     * enable all planes for frustum culling.
     * 
     * @return The frustum plane bitmask.
     */
    int32 GetInsideMask();
    
    /*!
     * @brief  A bitmask that indicates the frustum planes that will not be tested.Each bit 
     *         corresponds to one frustum plane (IFrustum::TestSphere).
     * 
     * Setting the bitmask to \c 0x7FFFFFFF  will disable frustum culling;setting it to \c 0  will 
     * enable all planes for frustum culling.
     * 
     * @param value The frustum plane bitmask.
     */
    void SetInsideMask(int32 value);
    
    /*!
     * @brief  Cull mesh sectors that lie completely above the given elevation value.
     * 
     * The default value is HeightmapSample::MaxValue.
     * 
     * @return The maximum elevation value.
     */
    int32 GetMaxElevation();
    
    /*!
     * @brief  Cull mesh sectors that lie completely above the given elevation value.
     * 
     * The default value is HeightmapSample::MaxValue.
     * 
     * @param value The maximum elevation value.
     */
    void SetMaxElevation(int32 value);
    
    /*!
     * @brief  Cull mesh sectors that lie completely below the given elevation value.
     * 
     * The default value is \c 0 .
     * 
     * @return The minimum elevation value.
     */
    int32 GetMinElevation();
    
    /*!
     * @brief  Cull mesh sectors that lie completely below the given elevation value.
     * 
     * The default value is \c 0 .
     * 
     * @param value The minimum elevation value.
     */
    void SetMinElevation(int32 value);
    
    /*!
     * @brief  Minimum sector size,in screen-space.
     * 
     * The default value is <c>150.0f</c> 
     * 
     * @return Minimum sector size,in screen-space.
     */
    float32 GetMinSectorSize();
    
    /*!
     * @brief  Minimum sector size,in screen-space.
     * 
     * The default value is <c>150.0f</c> 
     * 
     * @param value Minimum sector size,in screen-space.
     */
    void SetMinSectorSize(float32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of this class.
     */
    FrustumCulling();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginFace(MeshFace face);
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual void EndFace();
    
    virtual void EndMeshAction();
    
    /*!
     * @brief  Performs view frustum culling on the given CLOD mesh.All at least partially visible 
     *         mesh parts are triangulated and forwarded to the configured ITriangulationCallback 
     *         object.
     * 
     * Since this method performs CLOD mesh triangulation,it may only be called when 
     * the CloddyKernel::BeginTriangulation method has been called on the CloddyKernel object that 
     * owns the given \e mesh .
     * 
     * @param frustum <b>[not-null]</b>  The frustum to use for culling.
     * @param transform A transform matrix.
     * @param mesh The mesh.
     * @param meshFace The mesh face.
     */
    void Perform(IFrustum* frustum, Mat4D transform, IMesh* mesh, MeshFace meshFace);
    
    virtual void VisitSector(Traversal* traversal, int32 userData);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:

    Mat4D transform;
    
    /*!
     * @brief  Position of camera.
     */
    Ptr<CameraPosition> cameraPosition;
    
    Ptr<Int1> elevationMax;
    
    Ptr<Int1> elevationMin;
    
    /*!
     * @brief  The view frustum to cull against.
     */
    Ptr<IFrustum> frustum;
    
    /*!
     * @brief  A bitmask that indicates the frustum planes that will not be tested.Each bit 
     *         corresponds to one frustum plane (IFrustum::TestSphere).
     * 
     * Setting the bitmask to \c 0x7FFFFFFF  will disable frustum culling;setting it to \c 0  will 
     * enable all planes for frustum culling.
     */
    int32 insideMask;
    
    /*!
     * @brief  Cull mesh sectors that lie completely above the given elevation value.
     */
    int32 maxElevation;
    
    int32 maxElevationCurrent;
    
    /*!
     * @brief  Cull mesh sectors that lie completely below the given elevation value.
     */
    int32 minElevation;
    
    int32 minElevationCurrent;
    
    /*!
     * @brief  Minimum sector size,in screen-space.
     */
    float32 minSectorSize;
    
    /*!
     * @brief  Vertex positions.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  The projection transform.
     */
    Ptr<PerspectiveProjection> projection;
    
    /*!
     * @brief  Vertex bounding sphere radii.
     */
    Ptr<IVertexData> radius;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FrustumCulling> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x8F7BFC9A;
    
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
      if ((ptr = IMeshVisitor::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
