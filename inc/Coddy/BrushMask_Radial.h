////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_RADIAL_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_BRUSHMASK_RADIAL_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/BrushMask.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class IBrushMask; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes { class BrushMask; } } } }

// Declare class ::Cloddy::API::Heightmaps::Brushes::BrushMask_Radial.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the IBrushMask interface that represents a radial falloff from 
   *         the brush center towards the brush edges.
   */
  class BrushMask_Radial : public BrushMask
  {
    // Declare friend classes.
    
    friend class BrushMask;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetMaskValue(int32 x, int32 y);
    
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
     * @brief  The maximum mask value at the brush center.
     */
    int32 maxValue;
    
    /*!
     * @brief  The minimum mask value at the brush edges.
     */
    int32 minValue;
    
    /*!
     * @brief  The brush mask height,minus one,reciprocal.
     */
    float64 rHeight;
    
    /*!
     * @brief  The brush mask width,minus one,reciprocal.
     */
    float64 rWidth;
    
    /*!
     * @brief  Scale factor for normalized mask value.
     */
    float64 scale;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BrushMask_Radial.
     * 
     * @param width The brush mask width,in samples.
     * @param height The brush mask height,in samples.
     * @param minValue The minimum mask value at the brush edges.
     * @param maxValue The maximum mask value at the brush center.
     */
    BrushMask_Radial(int32 width, int32 height, int32 minValue, int32 maxValue);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BrushMask_Radial> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x266EBEC2;
    
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
