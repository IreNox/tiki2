////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_MODULATE_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_MODULATE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/BrushMask.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class BrushMask; } } } }
namespace Cloddy { namespace API { namespace Heightmaps { class HeightmapRegion; } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::BrushMask_Modulate.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::API::Heightmaps::HeightmapRegion;
  
  /*!
   * @brief  An implementation of the IBrushMask interface that modulates the mask values of two 
   *         aggregated brush masks.
   */
  class BrushMask_Modulate : public BrushMask
  {
    // Declare friend classes.
    
    friend class BrushMask;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool DoesUseSlope();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
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
     * @brief  The first brush mask.
     */
    Ptr<IBrushMask> first;
    
    /*!
     * @brief  The second brush mask.
     */
    Ptr<IBrushMask> second;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BrushMask_Modulate.
     * 
     * @param width The brush mask width,in samples.
     * @param height The brush mask height,in samples.
     * @param first The first brush mask.
     * @param second The second brush mask.
     */
    BrushMask_Modulate(int32 width, int32 height, IBrushMask* first, IBrushMask* second);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BrushMask_Modulate> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC8BEA882;
    
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
