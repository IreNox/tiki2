////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_REGIONERRORMETRIC_H
#define CLODDY_API_VISIBILITYCRITERIA_ERRORMETRICS_REGIONERRORMETRIC_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IErrorMetric.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Spatial { class ITerrainSpaceRegion; } } } }
namespace Cloddy { namespace API { namespace VertexData { class IVertexData; } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Declare class ::Cloddy::API::VisibilityCriteria::ErrorMetrics::RegionErrorMetric.

namespace Cloddy { namespace API { namespace VisibilityCriteria { namespace ErrorMetrics
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::Spatial::ITerrainSpaceRegion;
  using Cloddy::API::VertexData::IVertexData;
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  The RegionErrorMetric class is an implementation of the IErrorMetric interface that 
   *         uses an ITerrainSpaceRegion object define regions of interest in terrain-space.Mesh 
   *         refinement inside these regions is performed using the aggregated IErrorMetric object;
   *         no refinement is performed outside these regions,which leaves these regions with 
   *         minimal detail.
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
  class RegionErrorMetric : public virtual IErrorMetric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The aggregated IErrorMetric object.
     * 
     * @return <b>[not-null]</b>  The error metric to use.
     */
    Ptr<IErrorMetric> GetErrorMetric();
    
    /*!
     * @brief  The aggregated IErrorMetric object.
     * 
     * @param value <b>[not-null]</b>  The error metric to use.
     */
    void SetErrorMetric(IErrorMetric* value);
    
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
    
    virtual float64 ComputeVertexError(int32 v, int32 g, int32 a);
    
    virtual void EndMeshAction();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The aggregated IErrorMetric object.
     */
    Ptr<IErrorMetric> errorMetric;
    
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
     *         via #GetErrorMetric and #GetRegion.
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
    public: typedef Ptr<RegionErrorMetric> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x803781BE;
    
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
