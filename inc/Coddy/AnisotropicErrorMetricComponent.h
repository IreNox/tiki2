////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_ANISOTROPICERRORMETRICCOMPONENT_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_ANISOTROPICERRORMETRICCOMPONENT_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetricComponent.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components { class ErrorTerm; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::AnisotropicErrorMetricComponent.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  This error metric component aggregates two IErrorMetricComponent objects,interprets 
   *         one of them as the horizontal error and the other one as the vertical error.Both 
   *         errors are combined anisotropically,based on the angle between the vertex eye vector 
   *         and normal vector (for the horizontal error)resp. the angle between the vertex eye 
   *         vector and up vector (for the vertical error).
   * 
   * This error metric component may be used with CLOD IMesh objects that provide 
   * a ComponentIdsApi::Req_CameraPosition component.
   * 
   * The vertical error is aligned to the vertex normal vector and the horizontal The error 
   * returned by this error metric is the maximum of the scaled error values returned by the 
   * aggregated horizontal and vertical error metricses:
   * <pre>
   *      E = max(Eh * Sh, Ev * Sv)
   *      E  := The returned error value
   *      Eh := The horizontal error value.
   *      Ev := The vertical error value.
   *      Sh := Scale factor for horizontal error value.
   *      Sv := Scale factor for vertical error value.
   * </pre>
   * The scale factors \c Sh  and \c Sv  are derived from the angle between the vertex eye vector 
   * and normal vector resp. the angle between the vertex eye vector and up vector:
   * <pre>
   *      .                 direction of
   *      .                 normal vector
   *      .   
   *      .                       |
   *      .            C          |          C
   *      .             .         |         .
   *      .              .        |        .
   *      .               .      /|\\      .
   *      .                .    / | \\    .
   *      .                 .  /a | a\\  .
   *      .                  ./   |   \\.
   *      .                   .   |   .
   *      .                    .  |  .
   *      .                     . | .
   *      .                      .|.
   *      .    -------------------o--------------------
   *      .                       V          tangent/binormal 
   *      .         plane
   *      .   
   *      .   V := Vertex for which the anisotropic error is being computed
   *      .   C := Position of camera
   *      .   a := Angle between eye and normal vector
   *      .   b := Angle between eye and up vector
   * </pre>
   */
  class AnisotropicErrorMetricComponent : public virtual IErrorMetricComponent
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of AnisotropicErrorMetricComponent.
     * 
     * @param horizontal The horizontal error metric.
     * @param vertical The vertical error metric.
     */
    AnisotropicErrorMetricComponent(IErrorMetricComponent* horizontal, IErrorMetricComponent* vertical);
    
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
     * @brief  The base horizontal error metric (along tangent/binormal plane).
     */
    Ptr<IErrorMetricComponent> horizontal;
    
    /*!
     * @brief  The base vertical error metric (along normal vector).
     */
    Ptr<IErrorMetricComponent> vertical;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<AnisotropicErrorMetricComponent> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x89ADA5C2;
    
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
