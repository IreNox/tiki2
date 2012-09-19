////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_MESHVISITORS_HEIGHTABOVEGROUND_H
#define CLODDY_API_MESHVISITORS_HEIGHTABOVEGROUND_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IMesh; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class Picking; } } }
namespace Cloddy { namespace API { namespace MeshVisitors { class PointInfo; } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3D; } } } }

// Declare class ::Cloddy::API::MeshVisitors::HeightAboveGround.

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
  
  /*!
   * @brief  Computes the height of a given point above the terrain surface.
   * 
   * The term \e above  in this context is dependent on the used IGeometry object:points that have 
   * a higher elevations value are considered to be above those points with lower elevation values.
   */
  class HeightAboveGround : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The Picking object used for performing picking on the CLOD mesh.
     * 
     * @return <b>[not-null]</b>  The used Picking object.
     */
    Ptr<Picking> GetPicking();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of HeightAboveGround.
     * 
     * @param picking <b>[not-null]</b>  The Picking object to use.
     */
    HeightAboveGround(Picking* picking);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the height above ground from the given point.
     * 
     * The IMesh::GetProvider of the given \e mesh  object must contain 
     * a ComponentIdsApi::Req_Geometry component.
     * 
     * @param position A position in terrain-space.
     * @param mesh <b>[not-null]</b>  The CLOD mesh.
     * 
     * @return <b>[>=0]</b>  The height above ground,in terrain-space.If the given point is not 
     * located above the terrain,\c 0  is returned.
     */
    float64 Compute(Vec3D& position, IMesh* mesh);

    /*!
     * @brief  Computes the height above ground from the given point.
     * 
     * The IMesh::GetProvider of the given \e mesh  object must contain 
     * a ComponentIdsApi::Req_Geometry component.
     * 
     * @param pointX X-coordinate of the point in terrain-space.
     * @param pointY Y-coordinate of the point in terrain-space.
     * @param pointZ Z-coordinate of the point in terrain-space.
     * @param mesh <b>[not-null]</b>  The CLOD mesh.
     * 
     * @return <b>[>=0]</b>  The height above ground,in terrain-space.If the given point is not 
     * located above the terrain,\c 0  is returned.
     */
    float64 Compute(float64 pointX, float64 pointY, float64 pointZ, IMesh* mesh);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The used GeometrySample object.
     */
    Ptr<GeometrySample> geometrySample;
    
    /*!
     * @brief  The Picking object used for performing picking on the CLOD mesh.
     */
    Ptr<Picking> picking;
    
    /*!
     * @brief  The used #pointInfo object.
     */
    Ptr<PointInfo> pointInfo;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HeightAboveGround> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFA8FB371;
    
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
