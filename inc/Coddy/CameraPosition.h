////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_CAMERAPOSITION_H
#define CLODDY_API_UTIL_CAMERAPOSITION_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Mat4D.h"
#include "Cloddy/Vec3D.h"

// Declare class ::Cloddy::API::Util::CameraPosition.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Mat4D;
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  /*!
   * @brief  The CameraPosition is used by various components of the CloddyAPI.It serves as a data 
   *         container for the position,direction and velocity of the scene camera,in terrain-space.
   * 
   * The application must provide a CameraPosition object for each CLOD mesh by adding 
   * a ComponentIdsApi::Req_CameraPosition component to the meshes IProvider object.
   */
  class CameraPosition : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The camera direction vector,in terrain-space.
     * 
     * @return The normalized direction vector.
     */
    Vec3D GetDirection();
    
    /*!
     * @brief  The camera position,in terrain-space.
     * 
     * @return The position.
     */
    Vec3D GetPosition();
    
    /*!
     * @brief  The transformation matrix from terrain-space to world-space.
     * 
     * @return The transformation matrix.
     */
    Mat4D GetTerrainMatrix();
    
    /*!
     * @brief  The transformation matrix from terrain-space to world-space.
     * 
     * @param value The transformation matrix.
     */
    void SetTerrainMatrix(const Mat4D& value);
    
    /*!
     * @brief  The camera velocity vector,in terrain-space.
     * 
     * @return The velocity vector.
     */
    Vec3D GetVelocity();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CameraPosition.
     * 
     * The camera position will be at the coordinate origin.
     */
    CameraPosition();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the Z-coordinate of the given point in camera-space.
     * 
     * @param v Coordinate of point.
     * 
     * @return The Z-coordinate in camera-space.
     */
    float64 ComputeZ(const Vec3D& v);
    
    /*!
     * @brief  Returns the Z-coordinate of the given point in camera-space.
     * 
     * @param x X-coordinate of point,in terrain-space.
     * @param y Y-coordinate of point,in terrain-space.
     * @param z Z-coordinate of point,in terrain-space.
     * 
     * @return The Z-coordinate in camera-space.
     */
    float64 ComputeZ(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Returns the distance between the given point and the camera position.
     * 
     * @param v Coordinate of point,in terrain-space.
     * 
     * @return The distance,in terrain-space.
     */
    float64 Distance(const Vec3D& v);
    
    /*!
     * @brief  Returns the distance between the given point and the camera position.
     * 
     * @param x X-coordinate of point,in terrain-space.
     * @param y Y-coordinate of point,in terrain-space.
     * @param z Z-coordinate of point,in terrain-space.
     * 
     * @return The distance,in terrain-space.
     */
    float64 Distance(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Returns the square distance between the given point and the camera position.
     * 
     * @param v Coordinate of point,in terrain-space.
     * 
     * @return The square distance,in terrain-space.
     */
    float64 DistanceSqr(const Vec3D& v);
    
    /*!
     * @brief  Returns the square distance between the given point and the camera position.
     * 
     * @param x X-coordinate of point,in terrain-space.
     * @param y Y-coordinate of point,in terrain-space.
     * @param z Z-coordinate of point,in terrain-space.
     * 
     * @return The square distance,in terrain-space.
     */
    float64 DistanceSqr(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Transforms the given position vector from terrain-space to world-space.
     * 
     * @param v The position vector,in terrain-space.
     * 
     * @return The position vector,in world-space.
     */
    Vec3D TerrainToWorldCoords(const Vec3D& v);
    
    /*!
     * @brief  Transforms the given position vector from terrain-space to world-space.
     * 
     * @param x X-coordinate of position vector,in terrain-space.
     * @param y Y-coordinate of position vector,in terrain-space.
     * @param z Z-coordinate of position vector,in terrain-space.
     * 
     * @return The position vector,in world-space.
     */
    Vec3D TerrainToWorldCoords(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Transforms the given direction vector from terrain-space to world-space.
     * 
     * @param v The direction vector,in terrain-space.
     * 
     * @return The direction vector,in world-space.
     */
    Vec3D TerrainToWorldVector(const Vec3D& v);
    
    /*!
     * @brief  Transforms the given direction vector from terrain-space to world-space.
     * 
     * @param x X-component of direction vector,in terrain-space.
     * @param y Y-component of direction vector,in terrain-space.
     * @param z Z-component of direction vector,in terrain-space.
     * 
     * @return The direction vector,in world-space.
     */
    Vec3D TerrainToWorldVector(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Updates the direction vector.
     * 
     * @param v The direction vector in world-space.
     */
    void UpdateDirection(const Vec3D& v);
    
    /*!
     * @brief  Updates the direction vector.
     * 
     * @param x X-component of the direction vector in world-space.
     * @param y Y-component of the direction vector in world-space.
     * @param z Z-component of the direction vector in world-space.
     */
    void UpdateDirection(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Updates the camera position.
     * 
     * @param v The camera position,in world-space.
     */
    void UpdatePosition(const Vec3D& v);
    
    /*!
     * @brief  Updates the camera position.
     * 
     * @param x X-coordinate of camera position,in world-space.
     * @param y Y-coordinate of camera position,in world-space.
     * @param z Z-coordinate of camera position,in world-space.
     */
    void UpdatePosition(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Sets the position and velocity of the camera.
     * 
     * The velocity is computed from the current position and the given position.
     * 
     * @param v Coordinate of camera,in terrain-space.
     * @param time The time that has elapsed.
     */
    void UpdatePositionAndVelocity(const Vec3D& v, float32 time);
    
    /*!
     * @brief  Sets the position and velocity of the camera.
     * 
     * The velocity is computed from the current position and the given position.
     * 
     * @param x X-coordinate of camera,in terrain-space.
     * @param y Y-coordinate of camera,in terrain-space.
     * @param z Z-coordinate of camera,in terrain-space.
     * @param time The time that has elapsed.
     */
    void UpdatePositionAndVelocity(float64 x, float64 y, float64 z, float32 time);
    
    /*!
     * @brief  Transforms the given position vector from world-space to terrain-space.
     * 
     * @param v The position vector,in world-space.
     * 
     * @return The position vector,in terrain-space.
     */
    Vec3D WorldToTerrainCoords(const Vec3D& v);
    
    /*!
     * @brief  Transforms the given position vector from world-space to terrain-space.
     * 
     * @param x X-coordinate of position vector,in world-space.
     * @param y Y-coordinate of position vector,in world-space.
     * @param z Z-coordinate of position vector,in world-space.
     * 
     * @return The position vector,in terrain-space.
     */
    Vec3D WorldToTerrainCoords(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Transforms the given direction vector from world-space to terrain-space.
     * 
     * @param v The direction vector,in world-space.
     * 
     * @return The direction vector,in terrain-space.
     */
    Vec3D WorldToTerrainVector(const Vec3D& v);
    
    /*!
     * @brief  Transforms the given direction vector from world-space to terrain-space.
     * 
     * @param x X-component of direction vector,in world-space.
     * @param y Y-component of direction vector,in world-space.
     * @param z Z-component of direction vector,in world-space.
     * 
     * @return The direction vector,in terrain-space.
     */
    Vec3D WorldToTerrainVector(float64 x, float64 y, float64 z);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The camera direction vector,in terrain-space.
     */
    Vec3D direction;
    
    /*!
     * @brief  The camera position,in terrain-space.
     */
    Vec3D position;
    
    /*!
     * @brief  The transformation matrix from terrain-space to world-space.
     */
    Mat4D terrainMatrix;
    
    /*!
     * @brief  Inverse of #terrainMatrix.
     */
    Mat4D terrainMatrixI;
    
    /*!
     * @brief  Inverse transpose of #terrainMatrix.
     */
    Mat4D terrainMatrixIT;
    
    /*!
     * @brief  Transpose of #terrainMatrix.
     */
    Mat4D terrainMatrixT;
    
    /*!
     * @brief  The camera velocity vector,in terrain-space.
     */
    Vec3D velocity;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CameraPosition> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF654AFFA;
    
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
