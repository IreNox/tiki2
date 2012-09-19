////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_MOCKHEIGHTMAP_H
#define CLODDY_API_HEIGHTMAPS_MOCKHEIGHTMAP_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced classes.

#include "Cloddy/Heightmap.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapSample; } } }

// Declare class ::Cloddy::API::Heightmaps::MockHeightmap.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the IHeightmap interface that does nothing.
   * 
   * This class is only useful as a mock implementation for unit testing.
   */
  class MockHeightmap : public Heightmap
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IHeightmap> GetBaseHeightmap();
    
    virtual HeightmapLayer GetLayerMask();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of MockHeightmap.
     * 
     * @param width <b>[>0]</b>  The width of the heightmap,in samples.
     * @param height <b>[>0]</b>  The height of the heightmap,in samples.
     */
    MockHeightmap(int32 width, int32 height);
    
    /*!
     * @brief  Creates a new instance of MockHeightmap.
     * 
     * @param size <b>[pow2+1]</b>  The heightmap size.
     */
    MockHeightmap(int32 size);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Get(int32 x, int32 y, HeightmapSample* sample);
    
    virtual void Get(int32 x, int32 y, int32 z, HeightmapSample* sample);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MockHeightmap> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCDDE0AB5;
    
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
      if ((ptr = Heightmap::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
