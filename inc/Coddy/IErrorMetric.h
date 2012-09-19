////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_IERRORMETRIC_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_IERRORMETRIC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMeshCallback.h"

// Declare interface ::Cloddy::API::VisibilityCriteria::ErrorMetrics::IErrorMetric.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::IMeshCallback;
  
  /*!
   * @brief  An IErrorMetric implementation computes terrain-space error values for vertices of a 
   *         CLOD mesh.During refinement,these error values are projected to screen-space in order 
   *         to perform the actual visibility test,thus deciding if the vertex shall be visible 
   *         when the CLOD mesh is rendered.
   * 
   * The terrain-space error value of a vertex can be interpreted as the squared radius of a sphere 
   * centered at the vertex.The sphere is projected to screen-space and the projected sphere radius 
   * is then compared to a screen-space tolerance value.If it exceeds the tolerance,the vertex will 
   * be visible when rendering the CLOD mesh.
   */
  class NO_VTABLE IErrorMetric : public virtual IMeshCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Computes the vertex error for the given vertex.
     * 
     * @param v Index of the vertex.
     * @param g Index of grand-parent vertex.
     * @param a Index of ancestor vertex.
     * 
     * @return The vertex error in terrain-space,squared.
     */
    virtual float64 ComputeVertexError(int32 v, int32 g, int32 a) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IErrorMetric> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x17933C4D;
    
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
} } } } 

#endif
