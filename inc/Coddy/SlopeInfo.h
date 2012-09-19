////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_SLOPEINFO_H
#define CLODDY_API_HEIGHTMAPS_SAMPLEBUFFERS_SLOPEINFO_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Geometries { class IGeometry; } } }
namespace Cloddy { namespace Kernel { class IProvider; } }

// Declare class ::Cloddy::API::Heightmaps::SampleBuffers::SlopeInfo.

namespace Cloddy { namespace API { namespace Heightmaps { namespace SampleBuffers
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Geometries::IGeometry;
  using Cloddy::Kernel::IProvider;
  
  /*!
   * @brief  The SlopeInfo structure stores additional information that is needed for computing 
   *         terrain slope values for heightmap samples.
   */
  struct SlopeInfo : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  A SlopeInfo value where both scale factors are <c>1.0f</c>.
     */
    static const SlopeInfo One;
    
    /*!
     * @brief  The horizontal scale factor.
     * 
     * The horizontal scale factor is applied to the local coordinates of a heightmap sample.The 
     * scaled coordinates are then used in the slope computation.
     */
    float32 ScaleHorizontal;
    
    /*!
     * @brief  The vertical scale factor.
     * 
     * The elevation value of a heightmap sample is normalized to the range <c>[0..1]</c> and then 
     * multiplied with the vertical scale factor before it is used in the slope computation.
     */
    float32 ScaleVertical;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SlopeInfo.
     * 
     * @param scaleHorizontal <b>[>0]</b>  The horizontal scale factor (see #ScaleHorizontal).
     * @param scaleVertical <b>[>0]</b>  The vertical scale factor (see #ScaleVertical).
     */
    SlopeInfo(float32 scaleHorizontal, float32 scaleVertical);
    
    SlopeInfo();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes a SlopeInfo value from the given IGeometry object.
     * 
     * @param geometry <b>[not-null]</b>  The geometry object.
     * 
     * @return The slope info value.
     */
    static SlopeInfo FromGeometry(IGeometry* geometry);
    
    /*!
     * @brief  Computes a SlopeInfo value from the ComponentIdsApi::Req_Geometry component stored 
     *         in the given IProvider.
     * 
     * @param provider <b>[not-null]</b>  The provider object.
     * 
     * @return The slope info value.
     */
    static SlopeInfo FromProvider(IProvider* provider);
    
    /*!
     * @brief  Computes the terrain slope angle for the given elevationd elta.
     * 
     * @param elevationDelta The elevation delta value (see HeightmapSample::MaxValue).This value 
     * can be negative.
     * 
     * @return <b>[0..90]</b>  The terrain slope angle.
     */
    float32 ComputeSlopeAngle(int32 elevationDelta) const;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Combined scale factor for slope computation.
     */
    float64 scale;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    SlopeInfo(const SlopeInfo& other);
    
    SlopeInfo& operator=(const SlopeInfo& other);
  };
  
} } } } 

#endif
