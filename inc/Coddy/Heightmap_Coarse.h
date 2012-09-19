////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAP_COARSE_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAP_COARSE_H

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

// Declare class ::Cloddy::API::Heightmaps::Heightmap_Coarse.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Util::Box2I;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  The Heightmap_Coarse class represents another heightmap with reduced resolution.
   */
  class Heightmap_Coarse : public CompositeHeightmapOne
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
     * @brief  Logarithm of base two of the scale factor from coarse heightmap coordinates to 
     *         original heightmap coordinates.
     */
    int32 shift;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Heightmap_Coarse.
     * 
     * @param size Internal size of the coarse heightmap (see IMap::GetSize).
     * @param heightmap The source heightmap.
     */
    Heightmap_Coarse(int32 size, IHeightmap* heightmap);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Heightmap_Coarse> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xBFCBD471;
    
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
