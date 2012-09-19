////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_MAPREGION_H
#define CLODDY_API_UTIL_MAPREGION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMapRegion.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { class IMapRegionCallback; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Util::MapRegion.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerializableBase;
  
  class MapRegion : public SerializableBase, public virtual IMapRegion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Compiles the given map region into an optimized representation.
     * 
     * @param region <b>[not-null]</b>  The map region to compile.
     * 
     * @return <b>[not-null]</b>  The compiled map region.
     */
    static Ptr<IMapRegion> Compile(IMapRegion* region);
    
    /*!
     * @brief  Returns a map region that fully covers a cubemap of the given size.
     * 
     * @param cubeSize <b>[pow2+1]</b>  The cubemap size.
     * 
     * @return <b>[not-null]</b>  The map region.
     */
    static Ptr<IMapRegion> FullCube(int32 cubeSize);
    
    /*!
     * @brief  Returns a map region that fully covers a rectangular map of the given size.
     * 
     * @param width <b>[>0]</b>  The map width.
     * @param height <b>[>0]</b>  The map height.
     * 
     * @return <b>[not-null]</b>  The map region.
     */
    static Ptr<IMapRegion> FullRect(int32 width, int32 height);
    
    /*!
     * @brief  Returns a map region that represents the union of the given regions.
     * 
     * @param first <b>[not-null]</b>  First input region.
     * @param second <b>[not-null]</b>  Second input region.
     * 
     * @return <b>[not-null]</b>  The resulting map region.
     */
    static Ptr<IMapRegion> Union(IMapRegion* first, IMapRegion* second);
    
    virtual Ptr<IMapRegion> MapRegionCompile();
    
    virtual void MapRegionEnumerate(IMapRegionCallback* callback) = 0;
    
    virtual int32 MapRegionIntersectsWith(int32 minX, int32 minY, int32 minZ, int32 maxX, int32 maxY, int32 maxZ) = 0;
    
    virtual Ptr<IMapRegion> MapRegionUnion(IMapRegion* region);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of MapRegion.
     * 
     * @param serialType The serial type ID.
     */
    MapRegion(ISerialTypeInfo* serialType);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MapRegion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCE0793C;
    
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
      if ((ptr = SerializableBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IMapRegion::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
