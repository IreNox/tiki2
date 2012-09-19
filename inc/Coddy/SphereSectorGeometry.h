////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_GEOMETRIES_SPHERESECTORGEOMETRY_H
#define CLODDY_API_GEOMETRIES_SPHERESECTORGEOMETRY_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Geometry.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }
namespace Cloddy { namespace API { namespace Util { class MapBase; } } }

// Declare class ::Cloddy::API::Geometries::SphereSectorGeometry.

namespace Cloddy { namespace API { namespace Geometries
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::MapBase;
  
  /*!
   * @brief  An IGeometry implementation that uses the section of a sphere as base geometry.
   * 
   * In the first step,vertex positions are computed as done by the SquareGeometry class.Then,the 
   * vertex positions are projected onto a sphere which is located below the plane used in the 
   * first step.The sphere touches the plane at <c>(0,0,0)</c> in terrain-space.
   */
  class SphereSectorGeometry : public Geometry
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of SphereSectorGeometry.
     * 
     * @param heightmapWidth <b>[>0]</b>  Width of the heightmap.
     * @param heightmapHeight <b>[>0]</b>  Height of the heightmap.
     * @param terrainWidth <b>[>0]</b>  Width of the terrain base square,in terrain-space.
     * @param terrainHeight <b>[>0]</b>  Height of the terrain base square,in terrain-space.
     * @param terrainElevation <b>[>0]</b>  Maximum terrain elevation,in terrain-space.
     * @param radius <b>[>0]</b>  Radius of the base sphere.
     */
    SphereSectorGeometry(int32 heightmapWidth, int32 heightmapHeight, float64 terrainWidth, float64 terrainHeight, float64 terrainElevation, float64 radius);
    
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
     * @brief  Center of heightmap on X-axis.
     */
    float64 centerX;
    
    /*!
     * @brief  Center of heightmap on Y-axis.
     */
    float64 centerY;
    
    /*!
     * @brief  Maximum heightmap X-coordinate.
     */
    int32 maxX;
    
    /*!
     * @brief  Maximum heightmap Y-coordinate.
     */
    int32 maxY;
    
    /*!
     * @brief  Reciprocal of #scaleElevation.
     */
    float64 rScaleElevation;
    
    /*!
     * @brief  Reciprocal of #scaleX.
     */
    float64 rScaleX;
    
    /*!
     * @brief  Reciprocal of #scaleY.
     */
    float64 rScaleY;
    
    /*!
     * @brief  Radius of the base sphere,in terrain-space.
     */
    float64 radius;
    
    /*!
     * @brief  Scale factor for translating normalized heightmap elevation values to terrain-space 
     *         elevation.
     */
    float64 scaleElevation;
    
    /*!
     * @brief  Scale factor for heightmap X-axis.
     */
    float64 scaleX;
    
    /*!
     * @brief  Scale factor for heightmap Y-axis.
     */
    float64 scaleY;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SphereSectorGeometry> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4CC8C00B;
    
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
