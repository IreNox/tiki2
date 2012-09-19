////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_LOOKUPERRORMETRICCOMPONENT_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_LOOKUPERRORMETRICCOMPONENT_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetricComponent.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VertexData { class Float1; } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components { class ErrorTerm; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::LookupErrorMetricComponent.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IProvider;
  
  // Use referenced classes.
  
  using Cloddy::API::VertexData::Float1;
  
  /*!
   * @brief  This error metric components returns precomputed vertex errors from a data container.
   */
  class LookupErrorMetricComponent : public virtual IErrorMetricComponent
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of LookupErrorMetricComponent.
     * 
     * @param errorValues <b>[not-null]</b>  The data container that holds the precomputed vertex 
     * errors.
     */
    LookupErrorMetricComponent(Float1* errorValues);
    
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
     * @brief  The precomputed vertex errors.
     */
    Ptr<Float1> errorValues;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<LookupErrorMetricComponent> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCBF4FA87;
    
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
