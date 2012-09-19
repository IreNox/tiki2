////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_ELEVATION_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_ELEVATION_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Gauss.h"

// Include referenced classes.

#include "Cloddy/BrushMask.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class BrushMask; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapRegion; } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::BrushMask_Elevation.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Gauss;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::HeightmapRegion;
  
  /*!
   * @brief  An implementation of the IBrushMask that computes mask values from the elevation of 
   *         the terrain.
   */
  class BrushMask_Elevation : public BrushMask
  {
    // Declare friend classes.
    
    friend class BrushMask;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetMaskValue(int32 x, int32 y);
    
    virtual void Prepare(HeightmapRegion* region);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual Ptr<IBrushMask> DoScale(int32 width, int32 height);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The weight curve for elevation values.
     */
    Gauss curve;
    
    /*!
     * @brief  The elevation buffer offset.
     */
    int32 offset;
    
    /*!
     * @brief  The elevation buffer samples.
     */
    Array<int32> samples;
    
    /*!
     * @brief  The elevation buffer stride.
     */
    int32 stride;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    BrushMask_Elevation(int32 width, int32 height, const Gauss& curve);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BrushMask_Elevation> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAF5E5060;
    
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
      if ((ptr = BrushMask::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
