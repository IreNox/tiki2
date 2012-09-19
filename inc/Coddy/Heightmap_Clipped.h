////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAP_CLIPPED_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAP_CLIPPED_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec3I.h"

// Include referenced classes.

#include "Cloddy/CompositeHeightmapOne.h"

// Forward declare referenced structures.

namespace Cloddy { namespace API { namespace Util { struct Box2I; } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class Heightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Heightmap_Clipped.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Util::Box2I;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  The Heightmap_Clipped class can be used to extract a subregion of another heightmap.
   */
  class Heightmap_Clipped : public CompositeHeightmapOne
  {
    // Declare friend classes.
    
    friend class Heightmap;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Get(int32 x, int32 y, HeightmapSample* sample);
    
    virtual void Get(int32 x, int32 y, int32 z, HeightmapSample* sample);
    
    virtual int32 TransformFromBaseHeightmap(int32 face, Box2I& region);
    
    virtual Vec3I TransformToBaseHeightmap(int32 x, int32 y, int32 z);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Size of the source heightmap cubemap,minus one.
     */
    int32 cubemapSizeMinusOne;
    
    /*!
     * @brief  The cubemap face of this clipped heightmap.
     */
    int32 face;
    
    /*!
     * @brief  Translation offset along the X-axis.
     */
    int32 offsetX;
    
    /*!
     * @brief  Translation offset along the Y-axis.
     */
    int32 offsetY;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Heightmap_Clipped.
     * 
     * Choosing the subregion for a clipped heightmap is performed as follows:
     *   -# A block size is chosen (must be a power of two plus one),see \e blockSize .
     *   -# The given \e heightmap  is divided into blocks according to the chosen block size.
     *   -# A grid of adjacent blocks is selected as the subregion for the clipped heightmap.
     * Small block sizes will reduce performance when accessing heightmap samples that are stored 
     * in a LOD friendly manner.Thus,the block size should be as big as possible.
     * 
     * @param blockSize The block size.
     * @param x X-coordinate of top-left block of subregion.
     * @param y Y-coordinate of top-left block of subregion.
     * @param width Width of subregion,in blocks.
     * @param height Height of subregion,in blocks.
     * @param face The cubemap face of the subregion (see constants in Cubemap class for possible 
     * values).For rectangular heightmaps,use Cubemap::FaceNegZ.
     * @param heightmap The source heightmap.
     */
    Heightmap_Clipped(int32 blockSize, int32 x, int32 y, int32 width, int32 height, int32 face, IHeightmap* heightmap);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Heightmap_Clipped> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDF420A4F;
    
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
      if ((ptr = CompositeHeightmapOne::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
