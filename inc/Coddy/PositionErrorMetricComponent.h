////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_POSITIONERRORMETRICCOMPONENT_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_POSITIONERRORMETRICCOMPONENT_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetricComponent.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components { class ErrorTerm; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::PositionErrorMetricComponent.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  This error metric component computes the positional error of a vertex.
   * 
   * The positional error of a vertex is the euclidean distance in terrain-space between the vertex 
   * position and the interpolated vertex position:
   * <pre>
   *                  O V
   *                 /.\\
   *                / . \\
   *               /  .  \\
   *              /   .   \\
   *             /    .    \\
   *            /     .     \\
   *           /      .      \\
   *          /       .       \\
   *         /        .        \\
   *        /         .         \\
   *       /          .          \\
   *      /           .           \\
   *     /            .            \\
   *    O-------------O-------------O
   *    G             V*            A
   *    V  := Vertex for which the positional error is being computed 
   *    G  := Grand-parent vertex of V 
   *    A  := Ancestor vertex of V 
   *    V* := Interpolated vertex (from G and A) 
   *    => | V* - V | := Positional error of V
   * </pre>
   */
  class PositionErrorMetricComponent : public virtual IErrorMetricComponent
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual float64 ComputeVertexError(ErrorTerm* errorTerm);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PositionErrorMetricComponent> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA2E0ABB4;
    
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
