////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_TERRAINSPACEVISIBILITYCRITERION_H
#define CLODDY_API_VISIBILITYCRITERIA_TERRAINSPACEVISIBILITYCRITERION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IVisibilityCriterion.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { class IErrorMetric; } } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Declare class ::Cloddy::API::VisibilityCriteria::TerrainSpaceVisibilityCriterion.

namespace Cloddy { namespace API { namespace VisibilityCriteria
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::API::VisibilityCriteria::ErrorMetrics::IErrorMetric;
  using Cloddy::Kernel::IProvider;
  using Cloddy::Kernel::IVisibilityCriterion;
  
  /*!
   * @brief  This visibility criterion uses an IErrorMetric to compute terrain-space error values.
   *         Mesh vertices become visible when their error value exceeds the configured 
   *         terrain-space tolerance.
   * 
   * The following components of the CloddySDK are used by this class (\e opt  means that the 
   * component will be used if present,\e req  means that the component must be present):
   *   - \e req  - ComponentIdsApi::Opt_ErrorMetric
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e opt  - Semantic::Radius
   * 
   * @see ComponentIdsApi
   */
  class TerrainSpaceVisibilityCriterion : public virtual IVisibilityCriterion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  When computing terrain-space error values,the bounding sphere radius of a vertex can 
     *         be taken into account in order to avoid that refinement gets stuck at a coarse 
     *         level (since vertex error values are not nested).
     *         If a vertex data container with bound sphere radii has been specified in the 
     *         constructor,the radius fraction can be set.
     * 
     * The following equation is used when the radius is affecting error value computation:
     * <pre>
     *       adjustedError := max(error, radius / fraction)
     * </pre>
     * where \c adjustedError  is the computed error value,\c error  is the raw error value as 
     * computed by the aggregated error metric,\c radius  is the bounding sphere radius of the 
     * vertex and \c fraction  is the radius fraction value set by this property.
     * 
     * The default value is \c 0 .
     * 
     * @return <b>[>=0]</b>  The new radius fraction value.Set to \c 0  to disable the radius 
     * computation.
     */
    float32 GetRadiusFraction();
    
    /*!
     * @brief  When computing terrain-space error values,the bounding sphere radius of a vertex can 
     *         be taken into account in order to avoid that refinement gets stuck at a coarse 
     *         level (since vertex error values are not nested).
     *         If a vertex data container with bound sphere radii has been specified in the 
     *         constructor,the radius fraction can be set.
     * 
     * The following equation is used when the radius is affecting error value computation:
     * <pre>
     *       adjustedError := max(error, radius / fraction)
     * </pre>
     * where \c adjustedError  is the computed error value,\c error  is the raw error value as 
     * computed by the aggregated error metric,\c radius  is the bounding sphere radius of the 
     * vertex and \c fraction  is the radius fraction value set by this property.
     * 
     * The default value is \c 0 .
     * 
     * @param value <b>[>=0]</b>  The new radius fraction value.Set to \c 0  to disable the radius 
     * computation.
     */
    void SetRadiusFraction(float32 value);
    
    /*!
     * @brief  The terrain-space tolerance for error values.
     * 
     * The default value is <c>1.0f</c>.
     * 
     * @return <b>[>0]</b>  The terrain-space tolerance.
     */
    float32 GetTolerance();
    
    /*!
     * @brief  The terrain-space tolerance for error values.
     * 
     * The default value is <c>1.0f</c>.
     * 
     * @param value <b>[>0]</b>  The terrain-space tolerance.
     */
    void SetTolerance(float32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ScreenSpaceVisibilityCriterion.
     */
    TerrainSpaceVisibilityCriterion();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void BeginMeshAction(IProvider* provider);
    
    virtual bool ComputeVisibility(int32 v, int32 g, int32 a);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The used error metric.
     */
    Ptr<IErrorMetric> errorMetric;
    
    /*!
     * @brief  Vertex bounding sphere radii.
     */
    Ptr<IVertexData> radius;
    
    /*!
     * @brief  Reciprocal value of #radiusFraction.
     */
    float32 radiusFactor;
    
    /*!
     * @brief  The current radius fraction value.
     * 
     * @see #GetRadiusFraction
     */
    float32 radiusFraction;
    
    /*!
     * @brief  The screen-space tolerance for projected error values.
     */
    float32 tolerance;
    
    /*!
     * @brief  The square value of #tolerance.
     */
    float32 toleranceSqr;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<TerrainSpaceVisibilityCriterion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1EE6B343;
    
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
      if ((ptr = IVisibilityCriterion::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
