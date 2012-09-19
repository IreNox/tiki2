////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_GEOMETRIES_ELLIPSOIDGEOMETRY_H
#define CLODDY_API_GEOMETRIES_ELLIPSOIDGEOMETRY_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Geometry.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }

// Declare class ::Cloddy::API::Geometries::EllipsoidGeometry.

namespace Cloddy { namespace API { namespace Geometries
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  class EllipsoidGeometry : public Geometry
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  
     * 
     * @param heightmapSize <b>[pow2+1]</b>  Size of the heightmap.
     * @param radius <b>[>0]</b>  Equatorial radius,in meters.
     * @param flattening <b>[>=0]</b>  Flattening of ellipsoid.
     * @param scale Scale factor from ellipsoid space (in meters)to terrain-space.
     * @param minElevation The minimum elevation relative to ellipsoid,in terrain-space.
     * @param maxElevation The maximum elevation relative to ellipsoid,in terrain-space.
     */
    EllipsoidGeometry(int32 heightmapSize, float64 radius, float64 flattening, float64 scale, float64 minElevation, float64 maxElevation);
    
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
     * @brief  Precomputed value.
     */
    float64 e2;
    
    /*!
     * @brief  Precomputed value.
     */
    float64 e2m;
    
    /*!
     * @brief  Offset value used to convert heightmap elevation values to ellipsoid space (in 
     *         meters).
     */
    float64 elevationOffset;
    
    /*!
     * @brief  Scale value used to convert heightmap elevation values to ellipsoid space (in 
     *         meters).
     */
    float64 elevationScale;
    
    /*!
     * @brief  Reciprocal scale value used to convert heightmap elevation values to ellipsoid 
     *         space (in meters).
     */
    float64 elevationScaleReciprocal;
    
    /*!
     * @brief  Size of heightmap.
     */
    int32 heightmapSize;
    
    /*!
     * @brief  Equatorial radius of ellipsoid.
     */
    float64 radius;
    
    /*!
     * @brief  Scale factor from ellipsoid space (in meters)to terrain-space.
     */
    float64 scale;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<EllipsoidGeometry> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2B5AD4CB;
    
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
