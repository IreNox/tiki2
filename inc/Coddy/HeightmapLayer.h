////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_HEIGHTMAPLAYER_H
#define CLODDY_API_HEIGHTMAPS_HEIGHTMAPLAYER_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Heightmaps::HeightmapLayer.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of heightmap layers.
   */
  enum HeightmapLayer
  {
    /*!
     * @brief  Invalid heightmap layer.
     */
    HeightmapLayer_None = 0,
    
    /*!
     * @brief  Elevation values (see HeightmapSample::Elevation):
     */
    HeightmapLayer_Elevation = 1,
    
    /*!
     * @brief  Diffuse color values (see HeightmapSample::Diffuse).
     */
    HeightmapLayer_Diffuse = 2,
    
    /*!
     * @brief  Per-vertex displacement vectors (
     *         see HeightmapSample::DisplacementX,HeightmapSample::DisplacementY,HeightmapSample::DisplacementZ).
     */
    HeightmapLayer_Displacement = 4,
    
    /*!
     * @brief  Detail channels \#0 ..\#3 (see HeightmapSample::Detail0).
     */
    HeightmapLayer_Detail0 = 8,
    
    /*!
     * @brief  Detail channels \#4 ..\#7 (see HeightmapSample::Detail1).
     */
    HeightmapLayer_Detail1 = 16,
    
    /*!
     * @brief  Detail channels \#8 ..\#11 (see HeightmapSample::Detail2).
     */
    HeightmapLayer_Detail2 = 32,
    
    /*!
     * @brief  Detail channels \#12 ..\#15 (see HeightmapSample::Detail3).
     */
    HeightmapLayer_Detail3 = 64,
    
    /*!
     * @brief  All heightmap layers.
     */
    HeightmapLayer_All = 127
  };
  
  static inline HeightmapLayer operator|=(HeightmapLayer a, HeightmapLayer b)
  {
    return (HeightmapLayer) ((int32) a | (int32) b);
  }
  
  static inline HeightmapLayer operator&=(HeightmapLayer a, HeightmapLayer b)
  {
    return (HeightmapLayer) ((int32) a & (int32) b);
  }
  
  static inline HeightmapLayer operator^=(HeightmapLayer a, HeightmapLayer b)
  {
    return (HeightmapLayer) ((int32) a ^ (int32) b);
  }
} } } 

#endif
