////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_POSITIONERRORMETRIC_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_POSITIONERRORMETRIC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetric.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::PositionErrorMetric.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  An error metric that computes the euclidean distance between the interpolated and 
   *         actual positions of a vertex in terrain-space.
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e req  - Semantic::Position
   */
  class PositionErrorMetric : public virtual IErrorMetric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual float64 ComputeVertexError(int32 v, int32 g, int32 a);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Vertex data container for vertex positions,in terrain-space.
     */
    Ptr<IVertexData> position;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PositionErrorMetric> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA8E75C11;
    
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
