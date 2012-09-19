////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_COMPOSITEHEIGHTMAPTWO_H
#define CLODDY_API_HEIGHTMAPS_COMPOSITEHEIGHTMAPTWO_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/HeightmapLayer.h"

// Include referenced structures.

#include "Cloddy/SampleBitDepth.h"

// Include referenced classes.

#include "Cloddy/Heightmap.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { class IDirtyRegionCallback; } } }
namespace Cloddy { namespace API { namespace Heightmaps { class IHeightmap; } } }

// Declare class ::Cloddy::API::Heightmaps::CompositeHeightmapTwo.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::API::Heightmaps::SampleFormats::SampleBitDepth;
  
  /*!
   * @brief  Abstract base class for IHeightmap implementations that wrap two other IHeightmap 
   *         objects.
   */
  class CompositeHeightmapTwo : public Heightmap
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual SampleBitDepth GetBitDepth();
    
    virtual HeightmapLayer GetLayerMask();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Begin();
    
    virtual void BeginDirty(IDirtyRegionCallback* callback);
    
    virtual void End();
    
    virtual void Flush();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Attributes
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  The first wrapped IHeightmap object.
     */
    Ptr<IHeightmap> firstHeightmap;
    
    /*!
     * @brief  The second wrapped IHeightmap object.
     */
    Ptr<IHeightmap> secondHeightmap;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of CompositeHeightmapTwo.
     */
    CompositeHeightmapTwo();
    
    /*!
     * @brief  Creates a new instance of CompositeHeightmapTwo.
     * 
     * @param first <b>[not-null]</b>  The first heightmap to wrap.
     * @param second <b>[not-null]</b>  The second heightmap to wrap.
     */
    CompositeHeightmapTwo(IHeightmap* first, IHeightmap* second);
    
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
    public: typedef Ptr<CompositeHeightmapTwo> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x25A0D416;
    
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
