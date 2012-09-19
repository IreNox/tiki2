////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_COMPOSITEHEIGHTMAPONE_H
#define CLODDY_API_HEIGHTMAPS_COMPOSITEHEIGHTMAPONE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"
#include "Cloddy/Vec3I.h"

// Include referenced classes.

#include "Cloddy/Heightmap.h"

// Forward declare referenced structures.

namespace Cloddy { namespace API { namespace Util { struct Box2I; } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IDirtyRegionCallback; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Declare class ::Cloddy::API::Heightmaps::CompositeHeightmapOne.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Heightmaps::SampleFormats::SampleBitDepth;
  using Cloddy::API::Util::Box2I;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  Abstract base class for IHeightmap implementations that wrap another IHeightmap object.
   */
  class CompositeHeightmapOne : public Heightmap
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IHeightmap> GetBaseHeightmap();
    
    virtual SampleBitDepth GetBitDepth();
    
    virtual HeightmapLayer GetLayerMask();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Begin();
    
    virtual void BeginDirty(IDirtyRegionCallback* callback);
    
    virtual void End();
    
    virtual void Flush();
    
    virtual int32 TransformFromBaseHeightmap(int32 face, Box2I& region);
    
    virtual Vec3I TransformToBaseHeightmap(int32 x, int32 y, int32 z);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The wrapped IHeightmap object.
     */
    Ptr<IHeightmap> heightmap;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CompositeHeightmapOne.
     */
    CompositeHeightmapOne();
    
    /*!
     * @brief  Creates a new instance of CompositeHeightmapOne.
     * 
     * @param heightmap <b>[not-null]</b>  The heightmap to wrap.
     */
    CompositeHeightmapOne(IHeightmap* heightmap);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void DisposeManaged();
    
    virtual void DisposeManagedChildren();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CompositeHeightmapOne> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x434671E4;
    
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
