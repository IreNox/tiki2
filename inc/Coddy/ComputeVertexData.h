////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_COMPUTEVERTEXDATA_H
#define CLODDY_API_MESHVISITORS_COMPUTEVERTEXDATA_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"
#include "Cloddy/ComputeVertexDataInfo.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMesh; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class ComputeVertexDataInfo; } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3D; } } } }

// Declare class ::Cloddy::API::MeshVisitors::ComputeVertexData.

namespace Cloddy { namespace API { namespace MeshVisitors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IMesh;

  // Use referenced structures.

  using Cloddy::Core::Math::Vectors::Vec3D;
  
  // Use referenced classes.
  
  using Cloddy::API::Geometries::GeometrySample;
  using Cloddy::API::Heightmaps::HeightmapSample;
  using Cloddy::API::MeshVisitors::ComputeVertexDataInfo;
  
  /*!
   * @brief  Computes vertex data specified on a given point.
   */
  class ComputeVertexData : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ComputeVertexData.
     */
    ComputeVertexData();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes vertex data specified on a given point.
     * 
     * The IMesh::GetProvider of the given \e mesh  object must contain 
     * a ComponentIdsApi::Req_Geometry and ComponentIdsApi::Req_Heightmap component.
     * 
     * @param position A position in terrain-space.
     * @param elevation The terrain base elevation.
     * @param mesh <b>[not-null]</b>  The CLOD mesh.
     *
     * @returns The computed vertex data info.
     */
    Ptr<ComputeVertexDataInfo> Compute(Vec3D& position, float32 elevation, IMesh* mesh);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The used GeometrySample object.
     */
    Ptr<GeometrySample> geometrySample;

    /*!
     * @brief  The used HeightmapSample object.
     */
    Ptr<HeightmapSample> heightmapSample;

    /*!
     * @brief  The used ComputeVertexDataInfo object.
     */
    Ptr<ComputeVertexDataInfo> vertexDataInfo;

    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ComputeVertexData> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAB4AC276;
    
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
