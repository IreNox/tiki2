////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_REGIONERRORMETRICCOMPONENT_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_COMPONENTS_REGIONERRORMETRICCOMPONENT_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetricComponent.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegion; } } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components { class ErrorTerm; } } } } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::Components::RegionErrorMetricComponent.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics { namespace Components
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::Spatial::ITerrainSpaceRegion;
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  The RegionErrorMetricComponent class is an implementation of the IErrorMetricComponent 
   *         interface that uses an ITerrainSpaceRegion object that defines regions of interest in 
   *         terrain-space.Mesh refinement inside these regions is performed using the 
   *         aggregated IErrorMetricComponent object;no refinement is performed outside these 
   *         regions,which leaves these regions with minimal detail.
   * 
   * This class is typically used for generating collision meshes for physics simulation.The 
   * application defines regions of interest based on the position and velocities of bodies in the 
   * simulation.
   * 
   * The following vertex data semantics are used by this class (\e opt  means that the semantic 
   * will be used if present,\e req  means that the semantic must be present):
   *   - \e req  - Semantic::Position
   *   - \e req  - Semantic::Radius
   */
  class RegionErrorMetricComponent : public virtual IErrorMetricComponent
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The aggregated IErrorMetricComponent object.
     * 
     * @return <b>[not-null]</b>  The error metric component to use.
     */
    Ptr<IErrorMetricComponent> GetErrorMetricComponent();
    
    /*!
     * @brief  The aggregated IErrorMetricComponent object.
     * 
     * @param value <b>[not-null]</b>  The error metric component to use.
     */
    void SetErrorMetricComponent(IErrorMetricComponent* value);
    
    /*!
     * @brief  The terrain-space region of interest.
     * 
     * @return <b>[not-null]</b>  The terrain space region to use.
     */
    Ptr<ITerrainSpaceRegion> GetRegion();
    
    /*!
     * @brief  The terrain-space region of interest.
     * 
     * @param value <b>[not-null]</b>  The terrain space region to use.
     */
    void SetRegion(ITerrainSpaceRegion* value);
    
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
     * @brief  The aggregated IErrorMetricComponent object.
     */
    Ptr<IErrorMetricComponent> errorMetricComponent;
    
    /*!
     * @brief  Vertex positions,in terrain-space.
     */
    Ptr<IVertexData> position;
    
    /*!
     * @brief  Vertex bounding sphere radii,in terrain-space.
     */
    Ptr<IVertexData> radius;
    
    /*!
     * @brief  The terrain-space region of interest.
     */
    Ptr<ITerrainSpaceRegion> region;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Asserts that an error metric and a terrain space region object have been specified 
     *         via #GetErrorMetricComponent and #GetRegion.
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
    public: typedef Ptr<RegionErrorMetricComponent> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x87526F4D;
    
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
