////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_GEOMETRIES_GEOMETRYSAMPLE_H
#define CLODDY_API_GEOMETRIES_GEOMETRYSAMPLE_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"

// Declare class ::Cloddy::API::Geometries::GeometrySample.

namespace Cloddy { namespace API { namespace Geometries
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  Data container for information returned by the IGeometry::ComputeVertexPosition 
   *         and IGeometry::ComputeHeightmapCoordinatesAndElevation methods.
   */
  class GeometrySample : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The elevation value.
     */
    int32 Elevation;
    
    /*!
     * @brief  Returns the heightmap coordinates.
     * 
     * @return The heightmap coordinate vector.
     * 
     * @see #HeightmapX
     * @see #HeightmapY
     * @see #HeightmapZ
     */
    Vec3D GetHeightmap();
    
    /*!
     * @brief  X-component of heightmap coordinates.
     */
    float64 HeightmapX;
    
    /*!
     * @brief  Y-component of heightmap coordinates.
     */
    float64 HeightmapY;
    
    /*!
     * @brief  Z-component of heightmap coordinates.
     */
    float64 HeightmapZ;
    
    /*!
     * @brief  Returns the vertex position vector.
     * 
     * @return The vertex position vector.
     * 
     * @see #PositionX
     * @see #PositionY
     * @see #PositionZ
     */
    Vec3D GetPosition();
    
    /*!
     * @brief  X-coordinate of vertex position.
     */
    float64 PositionX;
    
    /*!
     * @brief  Y-coordinate of vertex position.
     */
    float64 PositionY;
    
    /*!
     * @brief  Y-coordinate of vertex position.
     */
    float64 PositionZ;
    
    /*!
     * @brief  Returns the vertex up vector.
     * 
     * @return The vertex up vector.
     * 
     * @see #UpX
     * @see #UpY
     * @see #UpZ
     */
    Vec3D GetUp();
    
    /*!
     * @brief  X-component of up vector.
     */
    float64 UpX;
    
    /*!
     * @brief  Y-component of up vector.
     */
    float64 UpY;
    
    /*!
     * @brief  Z-component of up vector.
     */
    float64 UpZ;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    GeometrySample();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<GeometrySample> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD92EB1AC;
    
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
