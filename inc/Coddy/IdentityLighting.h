////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_IDENTITYLIGHTING_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_LIGHTINGS_IDENTITYLIGHTING_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/Lighting.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILightingVisitor; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::IdentityLighting.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An ILighting implementation that returns the vertex diffuse color (ie. no lighting is 
   *         performed at all).
   */
  class IdentityLighting : public Lighting
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void Accept(ILightingVisitor* visitor, Object* userData);
    
    virtual int32 ComputeLighting(float64 positionX, float64 positionY, float64 positionZ, float32 normalX, float32 normalY, float32 normalZ, int32 diffuse);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IdentityLighting> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6B0868FF;
    
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
      if ((ptr = Lighting::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } } 

#endif
