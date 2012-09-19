////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_REGIONTRACKERCUBE_H
#define CLODDY_API_UTIL_REGIONTRACKERCUBE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/MapRegion.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Projection { class IMapProjection; } } } }
namespace Cloddy { namespace API { namespace Util { class IMapRegionCallback; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { class RegionTrackerRect; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::API::Util::RegionTrackerCube.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Heightmaps::Projection::IMapProjection;
  using Cloddy::Core::IO::Serialization::ISerializable;
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::Serializer;
  using Cloddy::Core::IO::Serialization::SerialTypeInfo;
  
  /*!
   * @brief  Utility class for tracking dirty regions in a cubemap.
   * 
   * The map is divided into square blocks.For each block,a dirty flag is stored.
   */
  class RegionTrackerCube : public MapRegion
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
     * @brief  The cubemap size.
     * 
     * @return <b>[pow2+1]</b>  The cubemap size.
     */
    int32 GetCubeSize();
    
    /*!
     * @brief  The grid size.
     * 
     * @return The grid size.
     */
    int32 GetGridSize();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    RegionTrackerCube();
    
    /*!
     * @brief  Creates a new instance of RegionTrackerCube.
     * 
     * @param cubeSize <b>[pow2+1]</b>  The cubemap size.
     * @param blockSize <b>[pow2]</b>  The block size.
     */
    RegionTrackerCube(int32 cubeSize, int32 blockSize);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    int32 CountDirtyBlocks();
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    /*!
     * @brief  Projects the regions tracked by the given rectangular region tracker and stores the 
     *         resulting regions in this region tracker.
     * 
     * @param dirty <b>[not-null]</b>  The rectangular region tracker.
     * @param projection <b>[not-null]</b>  The projection to use.
     */
    void FromRectangularProjection(RegionTrackerRect* dirty, IMapProjection* projection);
    
    /*!
     * @brief  Returns if the given block is dirty.
     * 
     * @param blockX <b>[0..#GetGridSize-1]</b>  X-coordinate of block.
     * @param blockY <b>[0..#GetGridSize-1]</b>  Y-coordinate of block.
     * @param face <b>[0..5]</b>  The cubemap face.
     * 
     * @return \c true  if the block is dirty,\c false  if it is not.
     */
    bool IsDirty(int32 blockX, int32 blockY, int32 face);
    
    virtual void MapRegionEnumerate(IMapRegionCallback* callback);
    
    virtual int32 MapRegionIntersectsWith(int32 minX, int32 minY, int32 minZ, int32 maxX, int32 maxY, int32 maxZ);
    
    virtual void Serialize(Serializer* data);
    
    /*!
     * @brief  Sets the dirty flag of the given block.
     * 
     * @param blockX <b>[0..#GetGridSize-1]</b>  X-coordinate of block.
     * @param blockY <b>[0..#GetGridSize-1]</b>  Y-coordinate of block.
     * @param face <b>[0..5]</b>  The cubemap face.
     * @param dirty The new dirty flag value.
     */
    void SetDirty(int32 blockX, int32 blockY, int32 face, bool dirty);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The GUID that uniquely identifies this type:{AE330FC9-24AE-40D7-B9C2-F1E4B97EF3D2}
     */
    static const String SerialGuid;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Serialization information about this type.
     */
    static const StaticPtr<ISerialTypeInfo> SerialId;
    
    Array<bool> blockDirty;
    
    /*!
     * @brief  The block size.
     */
    int32 blockSize;
    
    int32 blockSizeRect;
    
    /*!
     * @brief  The cubemap size.
     */
    int32 cubeSize;
    
    /*!
     * @brief  Cubemap size minus one.
     */
    int32 cubeSizeMinusOne;
    
    /*!
     * @brief  The rectangular dirty region tracker (used by #FromRectangularProjection method).
     */
    Ptr<RegionTrackerRect> dirty;
    
    /*!
     * @brief  Size of the block grid (both width and height),in blocks.
     */
    int32 gridSize;
    
    /*!
     * @brief  The map projection (used by #FromRectangularProjection method).
     */
    Ptr<IMapProjection> projection;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    void FindDirtyCubeBlocks(int32 face, int32 faceX1, int32 faceY1, int32 faceX2, int32 faceY2);
    
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
    public: typedef Ptr<RegionTrackerCube> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x73794559;
    
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
