////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_BACKFACECULLINGERRORMETRICCOMPONENT_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_BACKFACECULLINGERRORMETRICCOMPONENT_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetricComponent.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components { class ErrorTerm; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::BackfaceCullingErrorMetricComponent.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  An error metric component that applies backface-culling,ie. vertices that lie on 
   *         backfacing parts of the terrain are not refined and are not visible.
   * 
   * This error metric component may be used with CLOD IMesh objects that provide 
   * a ComponentIdsApi::Req_CameraPosition component.
   * 
   * When computing the vertex error for a vertex during refinement,backface-culling is performed.
   * If the vertex face is found to be backfacing,the vertex error is set to \c 0 .When frontfacing,
   * the vertex error is computed using an aggregated IErrorMetricComponent.
   * <pre>
   *      a := Angle between eye and normal vector
   *      t := Backface-culling threshold in range [0..1]
   *      Front-facing:
   *      -------------
   *      0   &lt;= a      &lt;  90?
   *      1   >= cos(a) >  -t
   *      Back-facing:
   *      ------------
   *      90? &lt;= a      &lt;= 180?
   *      -t  >= cos(a) >= -1
   * </pre>
   */
  class BackfaceCullingErrorMetricComponent : public virtual IErrorMetricComponent
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The backface-culling threshold.
     * 
     * <pre>
     *    a := Angle between eye and normal vector
     *    t := Backface-culling threshold in range [0..1]
     *    Front-facing:
     *    -------------
     *    0   &lt;= a      &lt;  90?
     *    1   >= cos(a) >  -t
     *    Back-facing:
     *    ------------
     *    90? &lt;= a      &lt;= 180?
     *    -t  >= cos(a) >= -1
     * </pre>
     * 
     * @return <b>[0..1]</b>  The backface-culling threshold.
     */
    float32 GetBackfaceCullingThreshold();
    
    /*!
     * @brief  The backface-culling threshold.
     * 
     * <pre>
     *    a := Angle between eye and normal vector
     *    t := Backface-culling threshold in range [0..1]
     *    Front-facing:
     *    -------------
     *    0   &lt;= a      &lt;  90?
     *    1   >= cos(a) >  -t
     *    Back-facing:
     *    ------------
     *    90? &lt;= a      &lt;= 180?
     *    -t  >= cos(a) >= -1
     * </pre>
     * 
     * @param value <b>[0..1]</b>  The backface-culling threshold.
     */
    void SetBackfaceCullingThreshold(float32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of BackfaceCullingErrorMetricComponent.
     * 
     * The backface-culling threshold defaults to <c>0.1</c>.
     * 
     * @param errorMetricComponent <b>[not-null]</b>  The error metric to use for frontfacing 
     * vertices.
     */
    BackfaceCullingErrorMetricComponent(IErrorMetricComponent* errorMetricComponent);
    
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
     * @brief  The backface-culling threshold.
     */
    float32 backfaceCullingThreshold;
    
    /*!
     * @brief  The base vertical error metric (along normal vector).
     */
    Ptr<IErrorMetricComponent> errorMetricComponent;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<BackfaceCullingErrorMetricComponent> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x650E0199;
    
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
