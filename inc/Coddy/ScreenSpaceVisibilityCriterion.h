////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_SCREENSPACEVISIBILITYCRITERION_H
#define CLODDY_API_VISIBILITYCRITERIA_SCREENSPACEVISIBILITYCRITERION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IVisibilityCriterion.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { class IErrorMetric; } } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Util { class CameraPosition; } } }
namespace Cloddy { namespace API { namespace Util { class PerspectiveProjection; } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ScreenSpaceVisibilityCriterion.

namespace Cloddy { namespace API { namespace VisibilityCriteria
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::API::VisibilityCriteria::ErrorMetrics::IErrorMetric;
  using Cloddy::Kernel::IProvider;
  using Cloddy::Kernel::IVisibilityCriterion;
  
  // Use referenced classes.
  
  using Cloddy::API::Util::CameraPosition;
  using Cloddy::API::Util::PerspectiveProjection;
  
  /*!
   * @brief  This visibility criterion uses an IErrorMetric to compute terrain-space error values 
   *         and projects these to screen-space.Mesh vertices become visible when their projected 
   *         error value exceeds the configured screen-space tolerance.
   * 
   * The following components of the CloddySDK are used by this class (\e opt  means that the 
   * component will be used if present,\e req  means that the component must be present):
   *   - \e req  - ComponentIdsApi::Opt_ErrorMetric
   *   - \e req  - ComponentIdsApi::Opt_PerspectiveProjection
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e req  - Semantic::Position
   *   - \e opt  - Semantic::Radius
   * 
   * @see ComponentIdsApi
   */
  class ScreenSpaceVisibilityCriterion : public virtual IVisibilityCriterion
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The screen-space tolerance for projected error values.
     * 
     * @return <b>[>0]</b>  The screen-space tolerance.
     */
    float32 GetTolerance();
    
    /*!
     * @brief  The screen-space tolerance for projected error values.
     * 
     * @param value <b>[>0]</b>  The screen-space tolerance.
     */
    void SetTolerance(float32 value);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ScreenSpaceVisibilityCriterion.
     */
    ScreenSpaceVisibilityCriterion();
    
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
     * @brief  Camera position.
     */
    Ptr<CameraPosition> cameraPosition;
    
    /*!
     * @brief  The used error metric.
     */
    Ptr<IErrorMetric> errorMetric;
    
    /*!
     * @brief  Vertex positions.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  The used projection.
     */
    Ptr<PerspectiveProjection> projection;
    
    /*!
     * @brief  Vertex bounding sphere radii.
     */
    Ptr<IVertexData> radius;
    
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
    public: typedef Ptr<ScreenSpaceVisibilityCriterion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE10E5090;
    
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
