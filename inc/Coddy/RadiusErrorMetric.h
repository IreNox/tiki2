////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_RADIUSERRORMETRIC_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_RADIUSERRORMETRIC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetric.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::RadiusErrorMetric.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  An implementation of the IErrorMetric interface that uses the bounding sphere radius 
   *         of a vertex as the error term.
   * 
   * Using this error metric results in a CLOD mesh in which all triangles have roughly the same 
   * size.
   */
  class RadiusErrorMetric : public virtual IErrorMetric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The maximum size of one mesh sector,in pixels.
     * 
     * The default value is \c 64 .
     * 
     * @return <b>[>0]</b>  The maximum sector size,in pixels.
     */
    float64 GetMaxSectorSize();
    
    /*!
     * @brief  The maximum size of one mesh sector,in pixels.
     * 
     * The default value is \c 64 .
     * 
     * @param value <b>[>0]</b>  The maximum sector size,in pixels.
     */
    void SetMaxSectorSize(float64 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of RadiusErrorMetric.
     */
    RadiusErrorMetric();
    
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
     * @brief  The maximum size of one mesh sector,in pixels.
     */
    float64 maxSectorSize;
    
    /*!
     * @brief  Reciprocal of #maxSectorSize.
     */
    float64 rMaxSectorSize;
    
    /*!
     * @brief  Vertex data container for bounding sphere radii.
     */
    Ptr<IVertexData> radius;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RadiusErrorMetric> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF572B8;
    
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
