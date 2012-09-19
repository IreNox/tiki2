////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_ILIGHTING_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_ILIGHTING_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMeshCallback.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILightingVisitor; } } } } }

// Declare interface ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::ILighting.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IMeshCallback;
  
  /*!
   * @brief  Instances of this interface perform lighting computations during mesh refinement.
   * 
   * Per-vertex visibility tests usually reflect the lighting used to render the terrain in order 
   * to reduce the number of triangles to render:Dark and shadowed areas are usually rendered at 
   * lower detail.The same holds for areas that are covered by fog or secluded by atmospheric 
   * scattering.
   */
  class NO_VTABLE ILighting : public virtual IMeshCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Accepts the given visitor object.
     * 
     * @param visitor <b>[not-null]</b>  The visitor object.
     * @param userData Optional user data.
     */
    virtual void Accept(ILightingVisitor* visitor, Object* userData) = 0;
    
    /*!
     * @brief  Returns an ILighting object that applies the lighting terms of this object and the 
     *         given one in sequence.
     * 
     * @param lighting <b>[not-null]</b>  The second lighting term to apply.
     * 
     * @return <b>[not-null]</b>  The resulting lighting object.
     */
    virtual Ptr<ILighting> Combine(ILighting* lighting) = 0;
    
    /*!
     * @brief  Computes lighting for the given vertex.
     * 
     * @param positionX X-coordinate of vertex position.
     * @param positionY Y-coordinate of vertex position.
     * @param positionZ Z-coordinate of vertex position.
     * @param normalX X-component of unit length normal vector.
     * @param normalY Y-component of unit length normal vector.
     * @param normalZ Z-component of unit length normal vector.
     * @param diffuse 32-bit ARGB diffuse color value.
     * 
     * @return The lighted color value.
     */
    virtual int32 ComputeLighting(float64 positionX, float64 positionY, float64 positionZ, float32 normalX, float32 normalY, float32 normalZ, int32 diffuse) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ILighting> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2EBEF50C;
    
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
      if ((ptr = IMeshCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } } } 

#endif
