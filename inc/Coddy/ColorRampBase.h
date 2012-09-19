////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_COLORS_COLORRAMPBASE_H
#define CLODDY_API_UTIL_COLORS_COLORRAMPBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IColorRamp.h"

// Declare class ::Cloddy::API::Util::Colors::ColorRampBase.

namespace Cloddy { namespace API { namespace Util { namespace Colors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Abstract base class for IColorRamp implementations.
   */
  class ColorRampBase : public virtual IColorRamp
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetColorCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual int32 Get(float64 x) = 0;
    
    virtual Array<int32> ToColorPalette(float64 x1, float64 x2, int32 n);
    
    virtual Ptr<IColorRamp> Transform(float64 scale, float64 offset);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ColorRampBase> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3B186DDE;
    
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
      if ((ptr = IColorRamp::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
