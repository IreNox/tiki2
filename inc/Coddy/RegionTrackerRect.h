////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_REGIONTRACKERRECT_H
#define CLODDY_API_UTIL_REGIONTRACKERRECT_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"

// Include referenced classes.

#include "Cloddy/MapRegion.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { class IMap; } } }
namespace Cloddy { namespace API { namespace Util { class IMapRegionCallback; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Util::RegionTrackerRect.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  Utility class for tracking dirty regions in a rectangular map.
   * 
   * The map is divided into square blocks.For each block,a dirty flag is stored.
   */
  class RegionTrackerRect : public MapRegion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The block size.
     * 
     * @return The block size.
     */
    int32 GetBlockSize();
    
    /*!
     * @brief  Current number of dirty blocks.
     * 
     * @return <b>[>=0]</b>  The number of dirty blocks.
     */
    int32 GetDirtyCount();
    
    /*!
     * @brief  Height of the block grid.
     * 
     * @return The grid height.
     */
    int32 GetGridHeight();
    
    /*!
     * @brief  Width of the block grid.
     * 
     * @return The grid width.
     */
    int32 GetGridWidth();
    
    /*!
     * @brief  Height of the map.
     * 
     * @return The map height.
     */
    int32 GetHeight();
    
    /*!
     * @brief  Width of the map.
     * 
     * @return The map width.
     */
    int32 GetWidth();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of RegionTrackerRect.
     */
    RegionTrackerRect();
    
    /*!
     * @brief  Creates a new instance of RegionTrackerRect.
     * 
     * @param width <b>[>0]</b>  Width of the map.
     * @param height <b>[>0]</b>  Height of the map.
     * @param blockSize <b>[>0]</b>  The block size.
     */
    RegionTrackerRect(int32 width, int32 height, int32 blockSize);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of RegionTrackerRect.
     * 
     * @param map <b>[not-null]</b>  The map.
     * @param blockSize <b>[>0]</b>  The block size.
     * 
     * @return <b>[not-null]</b>  The created region tracker object.
     */
    static Ptr<RegionTrackerRect> ForMap(IMap* map, int32 blockSize);
    
    /*!
     * @brief  Clears all block dirty flags to \c false .
     */
    void Clear();
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    /*!
     * @brief  Returns the effective size of the given block.
     * 
     * @param x <b>[0..#GetGridWidth-1]</b>  X-coordinate of block.
     * @param y <b>[0..#GetGridHeight-1]</b>  Y-coordinate of block.
     * 
     * @return The block size.
     */
    Vec2I GetEffectiveBlockSize(int32 x, int32 y);
    
    /*!
     * @brief  Returns the dirty flag of the given block.
     * 
     * @param x <b>[0..#GetGridWidth-1]</b>  X-coordinate of block.
     * @param y <b>[0..#GetGridHeight-1]</b>  Y-coordinate of block.
     * 
     * @return The dirty flag.
     */
    bool IsDirty(int32 x, int32 y);
    
    virtual void MapRegionEnumerate(IMapRegionCallback* callback);
    
    virtual int32 MapRegionIntersectsWith(int32 minX, int32 minY, int32 minZ, int32 maxX, int32 maxY, int32 maxZ);
    
    virtual void Serialize(Serializer* data);
    
    /*!
     * @brief  Sets the dirty flag of the given block.
     * 
     * @param x <b>[0..#GetGridWidth-1]</b>  X-coordinate of block.
     * @param y <b>[0..#GetGridHeight-1]</b>  Y-coordinate of block.
     * @param dirty The dirty flag.
     */
    void SetDirty(int32 x, int32 y, bool dirty);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{499E28BB-C536-4A76-BE47-B8FB30D6E334}
     */
    static const String SerialGuid;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Serialization information about this type.
     */
    static const StaticPtr<ISerialTypeInfo> SerialId;
    
    /*!
     * @brief  The dirty flags per block.
     */
    Array<bool> blockDirty;
    
    /*!
     * @brief  The block size.
     */
    int32 blockSize;
    
    /*!
     * @brief  Current number of dirty blocks.
     */
    int32 dirtyCount;
    
    /*!
     * @brief  Height of the block grid.
     */
    int32 gridHeight;
    
    /*!
     * @brief  Width of the block grid.
     */
    int32 gridWidth;
    
    /*!
     * @brief  Height of the map.
     */
    int32 height;
    
    /*!
     * @brief  Width of the map.
     */
    int32 width;
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field SerialId.
     */
    static Object* StaticInitializer_SerialId();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RegionTrackerRect> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4F075708;
    
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
      if ((ptr = MapRegion::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
