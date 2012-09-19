////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_BASEGEOMETRY_H
#define CLODDY_KERNEL_BASEGEOMETRY_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Kernel::BaseGeometry.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of base geometry layouts for CLOD meshes.
   */
  enum BaseGeometry
  {
    /*!
     * @brief  A planar square is used as base geometry for terrains.Elevation is plotted along the 
     *         squares normal vector.
     * 
     * <pre>
     *    +----------edge length----------+
     *    (0,0)         (n/2,0)           (n,0)
     *    O-------O-------O-------O-------O         +
     *    |\\      |      /|\\      |      /|         |
     *    | \\     |     / | \\     |     / |         |
     *    |  \\    |    /  |  \\    |    /  |         |
     *    |   \\   |   /   |   \\   |   /   |         |
     *    |    \\  |  /    |    \\  |  /    |         |
     *    |     \\ | /     |     \\ | /     |         |
     *    |      \\|/      |      \\|/      |         |
     *    O-------O-------O-------O-------O         |
     *    |      /|\\      |      /|\\      |         |
     *    |     / | \\     |     / | \\     |         |
     *    |    /  |  \\    |    /  |  \\    |         e
     *    |   /   |   \\   |   /   |   \\   |         d
     *    |  /    |    \\  |  /    |    \\  |         g
     *    | /     |     \\ | /     |     \\ |         e
     *    |/      |      \\|/      |      \\|
     *    (0,n/2) O---------------O-------O-------O (n,n/2) l
     *    |\\      |      /|\\      |      /|         e
     *    | \\     |     / | \\     |     / |         n
     *    |  \\    |    /  |  \\    |    /  |         g
     *    |   \\   |   /   |   \\   |   /   |         t
     *    |    \\  |  /    |    \\  |  /    |         h
     *    |     \\ | /     |     \\ | /     |         |
     *    |      \\|/      |      \\|/      |         |
     *    O-------O-------O-------O-------O         |
     *    |      /|\\      |      /|\\      |         |
     *    |     / | \\     |     / | \\     |         |
     *    |    /  |  \\    |    /  |  \\    |         |
     *    |   /   |   \\   |   /   |   \\   |         |
     *    |  /    |    \\  |  /    |    \\  |         |
     *    | /     |     \\ | /     |     \\ |         |
     *    |/      |      \\|/      |      \\|         |
     *    O-------O-------O-------O-------O         +
     *    (0,n)         (n/2,n)           (n,n)
     * </pre>
     */
    BaseGeometry_Square = 0,
    
    /*!
     * @brief  A sphere is used as base geometry for terrains.Elevation is plotted along the 
     *         respective surface normal.
     * 
     * The sphere is generated out of a cube by extruding vertices along the respective surface 
     * normal vectors towards the sphere surface.
     */
    BaseGeometry_Sphere = 1,
    
    /*!
     * @brief  The CLOD mesh is volumetric,ie. it does not have a base geometry;instead it directly 
     *         represents the solid regions of a volume dataset.
     */
    BaseGeometry_Volume = 2
  };
  
} } 

#endif
