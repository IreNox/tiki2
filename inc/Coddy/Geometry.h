////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_GEOMETRIES_GEOMETRY_H
#define CLODDY_API_GEOMETRIES_GEOMETRY_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/Ellipsoid.h"
#include "Cloddy/Handedness.h"

// Include referenced classes.

#include "Cloddy/GeometryBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Geometries { class IGeometry; } } }
namespace Cloddy { namespace API { namespace Util { class IMap; } } }

// Declare class ::Cloddy::API::Geometries::Geometry.

namespace Cloddy { namespace API { namespace Geometries
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::IMap;
  
  /*!
   * @brief  Base class for default IGeometry implementations in the CloddySDK.
   */
  class Geometry : public GeometryBase
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual float64 GetBoundingSphereRadius();
    
    virtual Handedness GetHandedness();
    
    virtual float64 GetMaximumDisplacement();
    
    virtual void SetMaximumDisplacement(float64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of EllipsoidGeometry that uses the given standard ellipsoid.
     * 
     * @param ellipsoid The standard ellipsoid.
     * @param heightmapSize <b>[pow2+1]</b>  Size of the heightmap.
     * @param scale Scale factor from ellipsoid space (in meters)to terrain-space.
     * @param minElevation The minimum ellipsoid height in terrain-space,mapped to elevation \c 0 .
     * @param maxElevation The maximum ellipsoid height in terrain-space,mapped to 
     * elevation HeightmapSample::MaxValue.
     * 
     * @return <b>[not-null]</b>  The created IGeometry object.
     */
    static Ptr<IGeometry> CreateEllipsoid(Ellipsoid ellipsoid, int32 heightmapSize, float64 scale, float64 minElevation, float64 maxElevation);
    
    /*!
     * @brief  Creates a new instance of IGeometry that uses a sphere as base geometry.
     * 
     * @param heightmap <b>[not-null]</b>  The heightmap which will be used with the geometry 
     * object.
     * @param terrainBase <b>[>0]</b>  Distance from sphere center to base elevation level.
     * @param terrainElevation <b>[>0]</b>  Scale factor for scaling normalized elevation values to 
     * terrain-space.
     * 
     * @return <b>[not-null]</b>  The created IGeometry object.
     */
    static Ptr<IGeometry> CreateSphere(IMap* heightmap, float64 terrainBase, float64 terrainElevation);
    
    /*!
     * @brief  Creates a new instance of IGeometry that uses the section of a sphere as base 
     *         geometry.
     * 
     * @param heightmap <b>[not-null]</b>  The heightmap which will be used with the geometry 
     * object.
     * @param terrainWidth <b>[>0]</b>  Width of the terrain base square,in terrain-space.
     * @param terrainHeight <b>[>0]</b>  Height of the terrain base square,in terrain-space.
     * @param terrainElevation <b>[>0]</b>  Maximum terrain elevation,in terrain-space.
     * @param radius <b>[>0]</b>  Radius of the base sphere.
     * 
     * @return <b>[not-null]</b>  The created IGeometry object.
     */
    static Ptr<IGeometry> CreateSphereSector(IMap* heightmap, float64 terrainWidth, float64 terrainHeight, float64 terrainElevation, float64 radius);
    
    /*!
     * @brief  Creates a new instance of IGeometry that uses a planar square as base geometry.
     * 
     * @param heightmap <b>[not-null]</b>  The heightmap which will be used with the geometry 
     * object.
     * @param terrainWidth <b>[>0]</b>  Width of the terrain base square,in terrain-space.
     * @param terrainHeight <b>[>0]</b>  Height of the terrain base square,in terrain-space.
     * @param terrainElevation <b>[>0]</b>  Maximum terrain elevation,in terrain-space.
     * 
     * @return <b>[not-null]</b>  The created IGeometry object.
     */
    static Ptr<IGeometry> CreateSquare(IMap* heightmap, float64 terrainWidth, float64 terrainHeight, float64 terrainElevation);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The bounding sphere radius of this geometry object,in terrain-space.
     */
    float64 boundingSphereRadius;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Geometry.
     * 
     * @param size <b>[pow2+1]</b>  The internal map size.
     */
    Geometry(int32 size);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The maximum displacement,in terrain-space.
     */
    float64 maximumDisplacement;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Geometry> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x92751D22;
    
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
      if ((ptr = GeometryBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
