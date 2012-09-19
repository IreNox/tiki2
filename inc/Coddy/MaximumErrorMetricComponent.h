////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_MAXIMUMERRORMETRICCOMPONENT_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_MAXIMUMERRORMETRICCOMPONENT_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetricComponent.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components { class ErrorTerm; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::MaximumErrorMetricComponent.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  This error metric aggregates two other IErrorMetricComponent objects and returns the 
   *         maximum vertex error value.
   */
  class MaximumErrorMetricComponent : public virtual IErrorMetricComponent
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of MaximumErrorMetricComponent.
     * 
     * @param errorMetricA <b>[not-null]</b>  First error metric.
     * @param errorMetricB <b>[not-null]</b>  Second error metric.
     */
    MaximumErrorMetricComponent(IErrorMetricComponent* errorMetricA, IErrorMetricComponent* errorMetricB);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual float64 ComputeVertexError(ErrorTerm* errorTerm);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  First aggregated error metric.
     */
    Ptr<IErrorMetricComponent> errorMetricA;
    
    /*!
     * @brief  Second aggregated error metric.
     */
    Ptr<IErrorMetricComponent> errorMetricB;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MaximumErrorMetricComponent> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC28F8D5;
    
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
      if ((ptr = IErrorMetricComponent::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } } 

#endif
