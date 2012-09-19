////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAPPICKER_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAPPICKER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IBeginEnd.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3D; } } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3I; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Geometries { class IGeometry; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Geometries { class GeometrySample; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::HeightmapPicker.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Geometries::IGeometry;
  using Cloddy::API::Util::IBeginEnd;
  
  // Use referenced classes.
  
  using Cloddy::API::Geometries::GeometrySample;
  
  /*!
   * @brief  The HeightmapPicker class is a helper for quickly picking points in terrain-space from 
   *         a heightmap.
   * 
   * In contrast to the Picking class which works with a CLOD mesh,this class directly operates on 
   * the samples of a heightmap.
   */
  class HeightmapPicker : public virtual IBeginEnd
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of HeightmapPicker.
     * 
     * @param heightmap <b>[not-null]</b>  The heightmap to use.
     * @param geometry <b>[not-null]</b>  The geometry to use.
     */
    HeightmapPicker(IHeightmap* heightmap, IGeometry* geometry);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Begin();
    
    virtual void End();
    
    /*!
     * @brief  Picks a point in terrain-space from the heightmap.
     * 
     * All calls to this method must be wrapped in calls to IBeginEnd::Begin and IBeginEnd::End in 
     * order to ensure proper synchronization of heightmap accesses (most likely background 
     * refinement or some other thread will access the heightmap concurrently).
     * 
     * @param coords The heightmap coordinates.
     * @param sample <b>[not-null]</b>  The output geometry sample.
     * 
     * @return \c true  if a point has been picked,\c false  if not.
     */
    bool PickFromHeightmap(const Vec3I& coords, GeometrySample* sample);
    
    /*!
     * @brief  Picks a point in terrain-space from the heightmap.
     * 
     * All calls to this method must be wrapped in calls to IBeginEnd::Begin and IBeginEnd::End in 
     * order to ensure proper synchronization of heightmap accesses (most likely background 
     * refinement or some other thread will access the heightmap concurrently).
     * 
     * @param heightmapX X-component of heightmap coordinates.
     * @param heightmapY Y-component of heightmap coordinates.
     * @param heightmapZ Z-component of heightmap coordinates.
     * @param sample <b>[not-null]</b>  The output geometry sample.
     * 
     * @return \c true  if a point has been picked,\c false  if not.
     */
    bool PickFromHeightmap(int32 heightmapX, int32 heightmapY, int32 heightmapZ, GeometrySample* sample);
    
    /*!
     * @brief  Picks a point in terrain-space from the heightmap.
     * 
     * The given reference point is translated into heightmap space.Then,the actual elevation from 
     * the heightmap is used to compute the terrain-space position of the picked point.
     * 
     * All calls to this method must be wrapped in calls to IBeginEnd::Begin and IBeginEnd::End in 
     * order to ensure proper synchronization of heightmap accesses (most likely background 
     * refinement or some other thread will access the heightmap concurrently).
     * 
     * @param position Reference point,in terrain-space.
     * @param sample <b>[not-null]</b>  The output geometry sample.
     * 
     * @return \c true  if a point has been picked,\c false  if not.
     */
    bool PickFromTerrain(const Vec3D& position, GeometrySample* sample);
    
    /*!
     * @brief  Picks a point in terrain-space from the heightmap.
     * 
     * The given reference point is translated into heightmap space.Then,the actual elevation from 
     * the heightmap is used to compute the terrain-space position of the picked point.
     * 
     * All calls to this method must be wrapped in calls to IBeginEnd::Begin and IBeginEnd::End in 
     * order to ensure proper synchronization of heightmap accesses (most likely background 
     * refinement or some other thread will access the heightmap concurrently).
     * 
     * @param positionX X-coordinate of reference point,in terrain-space.
     * @param positionY Y-coordinate of reference point,in terrain-space.
     * @param positionZ Z-coordinate of reference point,in terrain-space.
     * @param sample <b>[not-null]</b>  The output geometry sample.
     * 
     * @return \c true  if a point has been picked,\c false  if not.
     */
    bool PickFromTerrain(float64 positionX, float64 positionY, float64 positionZ, GeometrySample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The used geometry.
     */
    Ptr<IGeometry> geometry;
    
    /*!
     * @brief  The used heightmap.
     */
    Ptr<IHeightmap> heightmap;
    
    /*!
     * @brief  Data container for heightmap samples.
     */
    Ptr<HeightmapSample> heightmapSample;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HeightmapPicker> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x91CC3DDD;
    
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
      if ((ptr = IBeginEnd::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
