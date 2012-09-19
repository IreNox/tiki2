////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_MAPREGIONPROJECTOR_H
#define CLODDY_API_UTIL_MAPREGIONPROJECTOR_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection { class IMapProjection; } } } }
namespace Cloddy { namespace API { namespace Util { class IMapRegion; } } }
namespace Cloddy { namespace API { namespace Util { class IMapRegionCallback; } } }

// Declare class ::Cloddy::API::Util::MapRegionProjector.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::Projection::IMapProjection;
  
  /*!
   * @brief  The MapRegionProjector class can be used to project an arbitrary set of regions in a 
   *         rectangular map to a cubemap.
   */
  class MapRegionProjector : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of MapRegionProjector.
     * 
     * @param region <b>[not-null]</b>  The regions in the rectangular map.
     * @param projection <b>[not-null]</b>  The map projection to use.
     * @param blockSize The minimum size of projected cubemap regions (both width and height).
     * @param callback <b>[not-null]</b>  The callback that will receive the projected cubemap 
     * regions.
     */
    MapRegionProjector(IMapRegion* region, IMapProjection* projection, int32 blockSize, IMapRegionCallback* callback);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Projects the configured rectangular map regions and invoked the callback for each 
     *         projected cubemap region.
     */
    void Project();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Minimum size for projected cubemap regions.
     */
    int32 blockSize;
    
    /*!
     * @brief  The callback object for projected cubemap regions.
     */
    Ptr<IMapRegionCallback> callback;
    
    /*!
     * @brief  The cubemap size.
     */
    int32 cubeSize;
    
    /*!
     * @brief  The cubemap size,minus one.
     */
    int32 cubeSizeMinusOne;
    
    /*!
     * @brief  Width of the rectangular map.
     */
    int32 mapWidth;
    
    /*!
     * @brief  The used map projection.
     */
    Ptr<IMapProjection> projection;
    
    /*!
     * @brief  The rectangular map regions.
     */
    Ptr<IMapRegion> region;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Recursively finds cubemap regions that intersect with the rectangular regions.
     * 
     * @param face The current cubemap face.
     * @param faceX1 X-coordinate of top-left sample cubemap region (inclusive).
     * @param faceY1 Y-coordinate of top-left sample cubemap region (inclusive).
     * @param faceX2 X-coordinate of bottom-right sample cubemap region (exclusive).
     * @param faceY2 Y-coordinate of bottom-right sample cubemap region (exclusive).
     */
    void FindProjectedBlocks(int32 face, int32 faceX1, int32 faceY1, int32 faceX2, int32 faceY2);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MapRegionProjector> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD85A64A4;
    
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
