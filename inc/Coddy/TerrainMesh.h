////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_TERRAINMESH_H
#define CLODDY_API_TERRAINMESH_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::TerrainMesh.

namespace Cloddy { namespace API
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of Terrain CLOD meshes.
   */
  enum TerrainMesh
  {
    /*!
     * @brief  The CLOD mesh of a Terrain that is used for rendering.
     */
    TerrainMesh_Render = 0,
    
    /*!
     * @brief  The CLOD mesh of a Terrain that is used for collision detection.
     */
    TerrainMesh_Collision = 1
  };
  
} } 

#endif
