////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_IMAPREGION_H
#define CLODDY_API_UTIL_IMAPREGION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { class IMapRegionCallback; } } }

// Declare interface ::Cloddy::API::Util::IMapRegion.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  
  /*!
   * @brief  Base interface for classes that represent arbitrary regions of a IMap 
   * 
   * An IMapRegion implementation stores a set of rectangles on the cubemap surface;each such 
   * rectangle defines a subregion.
   */
  class NO_VTABLE IMapRegion : public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Compiles this map region into an optimized IMapRegion object.
     * 
     * It is guaranteed that the cubemap face rectangles of a compiled map region do not intersect 
     * with each other.
     * 
     * @return <b>[not-null]</b>  The compiled map region.
     */
    virtual Ptr<IMapRegion> MapRegionCompile() = 0;
    
    /*!
     * @brief  Enumerates over all subregions and calls the given callback for each one.
     * 
     * @param callback <b>[not-null]</b>  The callback to use.
     */
    virtual void MapRegionEnumerate(IMapRegionCallback* callback) = 0;
    
    /*!
     * @brief  Returns if this map region intersects with the given region.
     * 
     * @param minX Minimum X-coordinate of region.
     * @param minY Minimum Y-coordinate of region.
     * @param minZ Minimum Z-coordinate of region.
     * @param maxX Maximum X-coordinate of region.
     * @param maxY Maximum Y-coordinate of region.
     * @param maxZ Maximum Z-coordinate of region.
     * 
     * @return \c -1  if the given region does not intersect with this region,\c 1  if the given 
     * region is fully contained within this region and \c 0  if both regions intersect.
     */
    virtual int32 MapRegionIntersectsWith(int32 minX, int32 minY, int32 minZ, int32 maxX, int32 maxY, int32 maxZ) = 0;
    
    /*!
     * @brief  Returns an IMapRegion object that represents the union between this map region and 
     *         the given one.
     * 
     * @param region <b>[not-null]</b>  The other map region.
     * 
     * @return <b>[not-null]</b>  The map region union.
     */
    virtual Ptr<IMapRegion> MapRegionUnion(IMapRegion* region) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IMapRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x42D1C7D5;
    
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
      if ((ptr = ISerializable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
