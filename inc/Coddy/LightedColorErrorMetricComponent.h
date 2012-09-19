////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_LIGHTEDCOLORERRORMETRICCOMPONENT_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_LIGHTEDCOLORERRORMETRICCOMPONENT_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ColorErrorMetricComponent.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Lightings { class ILighting; } } } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components { class ErrorTerm; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::LightedColorErrorMetricComponent.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VisibilityCriteria::ErrorMetrics::Lightings::ILighting;
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  This error metric components computes the color error of a vertex in a way similar to 
   *         the ColorErrorMetricComponent class:An additional lighting term is applied to the 
   *         vertex diffuse color prior to error value computation.
   * 
   * This error metric component may be used with CLOD IMesh objects that provide 
   * a ComponentIdsApi::Opt_Lighting component.If the IMesh does not provide such a component,the 
   * error computation of the ColorErrorMetricComponent class is applied.
   * 
   * The following components of the CloddySDK are used by this class (\e opt  means that the 
   * component will be used if present,\e req  means that the component must be present):
   *   - \e opt  - ComponentIdsApi::Opt_Lighting
   */
  class LightedColorErrorMetricComponent : public ColorErrorMetricComponent
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual float64 ComputeVertexError(ErrorTerm* errorTerm);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The lighting term to apply.
     */
    Ptr<ILighting> lighting;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LightedColorErrorMetricComponent> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFC3DE71B;
    
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
      if ((ptr = ColorErrorMetricComponent::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } } 

#endif
