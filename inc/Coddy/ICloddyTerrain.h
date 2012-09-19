////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_EXTENSIONS_ICLODDYTERRAIN_H
#define CLODDY_EXTENSIONS_ICLODDYTERRAIN_H

// Definitions

#define CODEX_PREFIX
#define CODEX_SYSTEM_PREFIX
#define CLODDY_CORE_PREFIX
#define CLODDY_KERNEL_PREFIX
#define CLODDY_API_PREFIX
#define CLODDY_GRAPHICS_PREFIX

// Include referenced classes.

#include <CodeX/CodeX.h>
#include <CodeX/System.h>
#include <Cloddy/Cloddy_Core.h>

#include "Cloddy/ICloddyBrush.h"

// Declare interface ::Cloddy::Extensions::ICloddyTerrain.

namespace Cloddy { namespace Extensions { 

  /*!
  * @brief  Base interface for classes that represent terrains.
  */
  class NO_VTABLE ICloddyTerrain : public virtual codex_IDisposable, cloddy_IDirtyRegionCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public
    // ---------------------------------------------------------------------------------------------

  public:

    /*!
     * @brief Sets the camera position.
     *
     * @param position The camera position.
     */
    virtual void SetCameraPosition(cloddy_Vec3D& position) = 0;

    /*!
     * @brief Sets the camera position.
     *
     * @param position The camera position.
     */
    virtual void SetCameraPosition(cloddy_Vec3F& position) = 0;

    /*!
     * @brief Sets a terrain transform matrix.
     *
     * @param transform A transform matrix.
     */
    virtual void SetTransform(cloddy_Mat4D& transform) = 0;

    /*!
     * @brief Sets a terrain transform matrix.
     *
     * @param transform A transform matrix.
     */
    virtual void SetTransform(cloddy_Mat4F& transform) = 0;

    /*!
     * @brief Sets the tolerance (detail).
     *
     * @param tolerance A tolerance.
     */
    virtual void SetTolerance(float tolerance) = 0;

    /*!
     * @brief Sets a light direction and color.
     *
     * @param index The light index.
     * @param direction The light direction.
     * @param color The light color.
     */
    virtual void SetLight(codex_int32 index, cloddy_Vec3D& direction, codex_int32 color) = 0;

    /*!
     * @brief Sets a light direction and color.
     *
     * @param index The light index.
     * @param direction The light direction.
     * @param color The light color.
     */
    virtual void SetLight(codex_int32 index, cloddy_Vec3F& direction, codex_int32 color) = 0;

    /*!
     * @brief Sets an ambient light.
     *
     * @param color The ambient light color.
     */
    virtual void SetAmbientLight(codex_int32 color) = 0;

    /*!
     * @brief Enables a light.
     *
     * @param index A light index.
     */
    virtual void EnableLight(codex_int32 index) = 0;

    /*!
     * @brief Enables all lights.
     */
    virtual void EnableLights() = 0;

    /*!
     * @brief Disables a light.
     *
     * @param index A light index.
     */
    virtual void DisableLight(codex_int32 index) = 0;

    /*!
     * @brief Disables all lights.
     */
    virtual void DisableLights() = 0;

    /*!
     * @brief Gets the nearest distance relative to the given position.
     *
     * @param position A position in world-space.
     *
     * @returns The nearest distance.
     */
    virtual codex_float64 GetNearestDistance(cloddy_Vec3D& position) = 0;

    /*!
     * @brief Gets the nearest distance relative to the given position.
     *
     * @param position A position in world-space.
     *
     * @returns The nearest distance.
     */
    virtual codex_float32 GetNearestDistance(cloddy_Vec3F& position) = 0;

    /*!
     * @brief Gets the nearest position relative to the given position.
     *
     * @param position A position in world-space.
     *
     * @returns The nearest position in world-space.
     */
    virtual cloddy_Vec3D GetNearestPosition(cloddy_Vec3D& position) = 0;

    /*!
     * @brief Gets the nearest position relative to the given position.
     *
     * @param position A position in world-space.
     *
     * @returns The nearest position in world-space.
     */
    virtual cloddy_Vec3F GetNearestPosition(cloddy_Vec3F& position) = 0;

    /*!
     * @brief Gets the height above ground relative to the given position.
     *
     * @param position A position in world-space.
     *
     * @returns The height above ground.
     */
    virtual codex_float64 GetHeightAboveGround(cloddy_Vec3D& position) = 0;

    /*!
     * @brief Gets the height above ground relative to the given position.
     *
     * @param position A position in world-space.
     *
     * @returns The height above ground.
     */
    virtual codex_float32 GetHeightAboveGround(cloddy_Vec3F& position) = 0;

    /*!
     * @brief Gets the altitude of the given position.
     *
     * @param position A position in world-space.
     * @param nhn The normal-height-null.
     *
     * @returns The altitude.
     */
    virtual codex_float64 GetAltitude(cloddy_Vec3D& position, codex_float64 nhn) = 0;

    /*!
     * @brief Gets the altitude of the given position.
     *
     * @param position A position in world-space.
     * @param nhn The normal-height-null.
     *
     * @returns The altitude.
     */
    virtual codex_float32 GetAltitude(cloddy_Vec3F& position, codex_float32 nhn) = 0;

    /*!
     * @brief Calculates the given longitude/latitude coordinates into geocentric coordinates in world-space.
     * 
     * @param latitude The latitude in the range <c>[-90..90]</c>.
     * @param longitude The longitude in the range <c>[-180..180]</c>.
     * 
     * @return The geocentric coordinates in world-space.
     */
    virtual cloddy_Vec3D CalculateGeocentricCoordinates(codex_float64 latitude, codex_float64 longitude) = 0;

    /*!
     * @brief Calculates the given longitude/latitude coordinates into geocentric coordinates in world-space.
     * 
     * @param latitude The latitude in the range <c>[-90..90]</c>.
     * @param longitude The longitude in the range <c>[-180..180]</c>.
     * 
     * @return The geocentric coordinates in world-space.
     */
    virtual cloddy_Vec3F CalculateGeocentricCoordinates(codex_float32 latitude, codex_float32 longitude) = 0;

    /*!
     * @brief Computes a vertex data.
     * 
     * @param position A position in world-space.</c>.
     * 
     * @return A computed vertex data info in world-space..
     */
    virtual codex_Ptr<cloddy_ComputeVertexDataInfo> ComputeVertexData(cloddy_Vec3D position) = 0;

    /*!
     * @brief Computes a vertex data.
     * 
     * @param position A position in world-space.</c>.
     * 
     * @return A computed vertex data info in world-space..
     */
    virtual codex_Ptr<cloddy_ComputeVertexDataInfo> ComputeVertexData(cloddy_Vec3F position) = 0;
    
    /*!
     * @brief  Performs picking on this terrain along the given ray.
     * 
     * @param ray A ray in world-space.
     * @param pointInfoFlags The PointInfo flags.
     * 
     * @return The picking result as a PointInfo object or \c null  if the given ray does not intersect 
     * the terrain.
     */
    virtual codex_Ptr<cloddy_PointInfo> Pick(cloddy_Vec3D& ray, codex_int32 pointInfoFlags) = 0;

    /*!
     * @brief  Performs picking on this terrain along the given ray.
     * 
     * @param ray A ray in world-space.
     * @param pointInfoFlags The PointInfo flags.
     * 
     * @return The picking result as a PointInfo object or \c null  if the given ray does not intersect 
     * the terrain.
     */
    virtual codex_Ptr<cloddy_PointInfo> Pick(cloddy_Vec3F& ray, codex_int32 pointInfoFlags) = 0;

    /*!
     * @brief Triangulates the terrain by performing frustum culling.
     *
     * @param The view matrix.
     * @param The projection matrix.
     */
    virtual void Triangulate(cloddy_Mat4D& view, cloddy_Mat4D& projection) = 0;

    /*!
     * @brief Triangulates the terrain by performing frustum culling.
     *
     * @param The view matrix.
     * @param The projection matrix.
     */
    virtual void Triangulate(cloddy_Mat4F& view, cloddy_Mat4F& projection) = 0;

    /*!
     * @brief Triangulates the terrain by performing frustum culling.
     *
     * @param p1 A plane.
     * @param p2 A plane.
     * @param p3 A plane.
     * @param p4 A plane.
     * @param p5 A plane.
     * @param p6 A plane.
     */
    virtual void Triangulate(cloddy_Plane p1, cloddy_Plane p2, cloddy_Plane p3, cloddy_Plane p4, cloddy_Plane p5, cloddy_Plane p6) = 0;

    /*!
     * @brief Triangulates the terrain without performing frustum culling.
     */
    virtual void Triangulate() = 0;

    /*!
     * @brief Applies a given brush onto the terrain mesh.
     *
     * @param brush A brush.
     * @param ray A ray in world-space.
     */
    virtual void ApplyBrush(ICloddyBrush* brush, cloddy_Vec3F ray) = 0;

    /*!
     * @brief Applies a given brush onto the terrain mesh.
     *
     * @param brush A brush.
     * @param ray A ray in world-space.
     */
    virtual void ApplyBrush(ICloddyBrush* brush, cloddy_Vec3D ray) = 0;

    /*!
     * @brief The unique ID of this type.
     */
    static const codex_int32 TypeId = 0xA01BDF29;

    // ---------------------------------------------------------------------------------------------
    // Protected
    // ---------------------------------------------------------------------------------------------

  protected:
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    virtual void* TryCast(int id)
    {
      void* ptr;

      if (id == TypeId) return (void*) this;
      if ((ptr = codex_IDisposable::TryCast(id)) != 0) return ptr;
      if ((ptr = cloddy_IDirtyRegionCallback::TryCast(id)) != 0) return ptr;

      return Object::TryCast(id);
    }
  };

} }

#endif