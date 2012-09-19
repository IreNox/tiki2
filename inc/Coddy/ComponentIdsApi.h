////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_COMPONENTIDSAPI_H
#define CLODDY_API_COMPONENTIDSAPI_H

#include "CodeX/System.h"

// Declare class ::Cloddy::API::ComponentIdsApi.

namespace Cloddy { namespace API
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  This class defines component ID constants for the components that exist in the 
   *         CloddyAPI.
   * 
   * For each component used in the CloddyAPI,a component ID is declared as a static constant in 
   * this class.A component ID is a unique 64-bit integer value.
   * 
   * Component ID constants that start with \c Req_  indicate mandatory components which must 
   * always be specified when creating a CLOD mesh.Constants starting with \c Opt_  are only needed 
   * under certain circumstances;see the respective source documentation for details.
   * 
   * See the ComponentIdsKernel class for a list of unused component IDs which can be used for 
   * additional components defined by the application.
   * 
   * @see ComponentIdsKernel
   * @see IProvider
   */
  class ComponentIdsApi
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  An IErrorMetric object.
     * 
     * The following components in the CloddySDK use this component (\e opt  means that the 
     * semantic will be used if present,\e req  means that the semantic must be present):
     *   - \e req  - ScreenSpaceVisibilityCriterion
     *   - \e req  - TerrainSpaceVisibilityCriterion
     */
    static const int64 Opt_ErrorMetric = (int64) 0x895861EDE0E4CECULL;
    
    /*!
     * @brief  An ILighting object.
     * 
     * This component can be used to apply a lighting term when computing vertex errors during 
     * refinement.This way,the lighting parameters can affect the mesh structure (dark resp. 
     * shadowed areas are rendered with less triangles,lit areas are rendered with more triangles).
     * 
     * The following components in the CloddySDK use this component (\e opt  means that the 
     * semantic will be used if present,\e req  means that the semantic must be present):
     *   - \e opt  - DefaultErrorMetric
     *   - \e opt  - LightedColorErrorMetricComponent
     */
    static const int64 Opt_Lighting = (int64) 0x82CCD40ED7E1A01ULL;
    
    /*!
     * @brief  An #Opt_PerspectiveProjection object.
     * 
     * The following components in the CloddySDK use this component (\e opt  means that the 
     * semantic will be used if present,\e req  means that the semantic must be present):
     *   - \e req  - FrustumCulling
     *   - \e req  - ScreenSpaceVisibilityCriterion
     */
    static const int64 Opt_PerspectiveProjection = (int64) 0xC1BE0570C885B5FULL;
    
    /*!
     * @brief  An IVertexFormat object.
     * 
     * The following components in the CloddySDK use this component (\e opt  means that the 
     * semantic will be used if present,\e req  means that the semantic must be present):
     *   - \e req  - VertexFactory
     */
    static const int64 Opt_VertexLayout = (int64) 0x268F8BB258D5032AULL;
    
    /*!
     * @brief  A CameraPosition object that represents the position of the scene camera in 
     *         terrain-space.
     * 
     * This component must be specified for all CLOD meshes.
     */
    static const int64 Req_CameraPosition = (int64) 0x204FDC9F1D4750AULL;
    
    /*!
     * @brief  An IGeometry object.
     * 
     * This component must be specified for all CLOD meshes.
     */
    static const int64 Req_Geometry = (int64) 0x27640368300ABF7ULL;
    
    /*!
     * @brief  An IHeightmap object.
     * 
     * This component must be specified for all terrain CLOD meshes.
     */
    static const int64 Req_Heightmap = (int64) 0x5AC19EFA61DCAE3ULL;
    
    /*!
     * @brief  An IVertexDataCollection object that holds the application vertex data containers.
     */
    static const int64 Req_VertexDataCollection = (int64) 0x2ED05381D8ABE674ULL;
  };
  
} } 

#endif
