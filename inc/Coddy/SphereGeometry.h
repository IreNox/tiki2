////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_GEOMETRIES_SPHEREGEOMETRY_H
#define CLODDY_API_GEOMETRIES_SPHEREGEOMETRY_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Geometry.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }

// Declare class ::Cloddy::API::Geometries::SphereGeometry.

namespace Cloddy { namespace API { namespace Geometries
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An IGeometry implementation that uses a sphere as base geometry.
   */
  class SphereGeometry : public Geometry
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of this class.
     * 
     * @param heightmapSize <b>[pow2+1]</b>  Size of the heightmap,must be a power of two plus one.
     * @param terrainBase <b>[>0]</b>  Distance from sphere center to base elevation level.
     * @param terrainElevation <b>[>0]</b>  Scale factor for scaling normalized elevation values to 
     * terrain-space.
     */
    SphereGeometry(int32 heightmapSize, float64 terrainBase, float64 terrainElevation);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void ComputeHeightmapCoordinatesAndElevation(GeometrySample* sample);
    
    virtual void ComputeVertexPosition(GeometrySample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Coordinate of heightmap center.
     */
    int32 center;
    
    /*!
     * @brief  Sphere radius that represents the base elevation.
     */
    float64 elevationBase;
    
    /*!
     * @brief  Scale factor for scaling elevation values to terrain-space.
     */
    float64 elevationScale;
    
    /*!
     * @brief  Reciprocal of #elevationScale.
     */
    float64 rElevationScale;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SphereGeometry> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x123FCECB;
    
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
      if ((ptr = Geometry::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
