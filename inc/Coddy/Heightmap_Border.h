////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAP_BORDER_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAP_BORDER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CompositeHeightmapOne.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class Heightmap; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::Heightmap_Border.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  The Heightmap_Border class wraps another rectangular IHeightmap instance and adds a 
   *         smooth border falloff to the right and bottom heightmap edges.
   */
  class Heightmap_Border : public CompositeHeightmapOne
  {
    // Declare friend classes.
    
    friend class Heightmap;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Get(int32 x, int32 y, HeightmapSample* sample);
    
    virtual void Get(int32 x, int32 y, int32 z, HeightmapSample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Width of the border falloff region,in heightmap samples.
     */
    int32 borderFalloff;
    
    /*!
     * @brief  The heightmap sample used for the padded border region.
     */
    Ptr<HeightmapSample> borderSample;
    
    /*!
     * @brief  Height of the inner heightmap,in heightmap samples.
     */
    int32 innerHeight;
    
    /*!
     * @brief  Width of the inner heightmap,in heightmap samples.
     */
    int32 innerWidth;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Heightmap_Border.
     * 
     * @param heightmap The inner heightmap.
     * @param borderSample The heightmap sample values to use for the padded border.
     * @param borderFalloff Width of the border falloff region,in heightmap samples.
     */
    Heightmap_Border(IHeightmap* heightmap, HeightmapSample* borderSample, int32 borderFalloff);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Heightmap_Border> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x15F298A8;
    
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
