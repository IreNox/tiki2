////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_DISTANCETOSEALEVEL_H
#define CLODDY_API_MESHVISITORS_DISTANCETOSEALEVEL_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMesh; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class Picking; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class PointInfo; } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3D; } } } }

// Declare class ::Cloddy::API::MeshVisitors::DistanceToSeaLevel.

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
  
  /*!
   * @brief  Computes the distance of a given point to the sea level.
   */
  class DistanceToSeaLevel : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DistanceToSeaLevel.
     */
    DistanceToSeaLevel();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the distance of a given point to the sea level.
     * 
     * The IMesh::GetProvider of the given \e mesh  object must contain 
     * a ComponentIdsApi::Req_Geometry component.
     * 
     * @param position A position in terrain-space.
     * @param elevation The terrain base elevation.
     * @param nhn The normal-height-null..
     * @param mesh <b>[not-null]</b>  The CLOD mesh.
     */
    float64 Compute(Vec3D& position, float32 elevation, float64 nhn, IMesh* mesh);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The used GeometrySample object.
     */
    Ptr<GeometrySample> geometrySample;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DistanceToSeaLevel> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFA4AB341;
    
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
