////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_COLORS_COLORRAMP_TRANSFORM_H
#define CLODDY_API_UTIL_COLORS_COLORRAMP_TRANSFORM_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ColorRampBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Colors { class IColorRamp; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { namespace Colors { class ColorRampBase; } } } }

// Declare class ::Cloddy::API::Util::Colors::ColorRamp_Transform.

namespace Cloddy { namespace API { namespace Util { namespace Colors
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the IColorRamp interface that performs a linear transformation of 
   *         the input X-coordinates before delegating to another IColorRamp object.
   */
  class ColorRamp_Transform : public ColorRampBase
  {
    // Declare friend classes.
    
    friend class ColorRampBase;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetColorCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual int32 Get(float64 x);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The base color ramp.
     */
    Ptr<IColorRamp> colorRamp;
    
    /*!
     * @brief  The offset value.
     */
    float64 offset;
    
    /*!
     * @brief  The scale factor.
     */
    float64 scale;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ColorRamp_Transform.
     * 
     * @param colorRamp The base color ramp.
     * @param scale The scale factor.
     * @param offset The offset value.
     */
    ColorRamp_Transform(IColorRamp* colorRamp, float64 scale, float64 offset);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ColorRamp_Transform> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7A686240;
    
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
      if ((ptr = ColorRampBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
