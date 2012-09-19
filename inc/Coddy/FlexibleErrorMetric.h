////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_FLEXIBLEERRORMETRIC_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_FLEXIBLEERRORMETRIC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetric.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components { class IErrorMetricComponent; } } } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components { class ErrorTerm; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::FlexibleErrorMetric.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::IErrorMetricComponent;
  using Cloddy::Kernel::IProvider;
  
  // Use referenced classes.
  
  using Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::ErrorTerm;
  
  /*!
   * @brief  An IErrorMetric implementation that uses a configurable graph of IErrorMetricComponent
   *         s for computing for terrain-space error for vertices.
   * 
   * The various implementations of the IErrorMetricComponent interface can be used to create an 
   * error metric dynamically at runtime.An ErrorTerm object is used to perform common computations,
   * so that these do not have to be done redundantly in each error metric component.
   * 
   * This error metric can be used with CLOD IMesh objects that provide 
   * a ComponentIdsApi::Req_CameraPosition component.
   */
  class FlexibleErrorMetric : public virtual IErrorMetric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The root error metric component.
     * 
     * @return <b>[not-null]</b>  The root IErrorMetricComponent object.
     */
    Ptr<IErrorMetricComponent> GetErrorMetricComponent();
    
    /*!
     * @brief  The root error metric component.
     * 
     * @param value <b>[not-null]</b>  The root IErrorMetricComponent object.
     */
    void SetErrorMetricComponent(IErrorMetricComponent* value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of FlexibleErrorMetric.
     */
    FlexibleErrorMetric();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual float64 ComputeVertexError(int32 v, int32 g, int32 a);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The root error metric component.
     */
    Ptr<IErrorMetricComponent> errorMetricComponent;
    
    /*!
     * @brief  The error term object that is used for computing the terrain-space error.
     */
    Ptr<ErrorTerm> errorTerm;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that an error metric component has been specified 
     *         via #GetErrorMetricComponent.
     */
    void AssertIsComplete();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FlexibleErrorMetric> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7E95DC51;
    
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
      if ((ptr = IErrorMetric::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
