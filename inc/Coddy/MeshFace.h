////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_MESHFACE_H
#define CLODDY_KERNEL_MESHFACE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Kernel::MeshFace.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of CLOD mesh faces.
   * 
   * <pre>
   *     .         +----o----o------+
   *     .        /|    | Z+ |     /|
   *     .       / |    o----o    / |
   *     .      /  |             /  o
   *     .     /   |  o----o    /  /|
   *     .    /    | / Y- /    /  / |      Y- |  / Z+
   *     .   +------o----o----+  oX+o         | /
   *     .   |  o  |          |  | /|         |/
   *     .   | /|  |          |  |/ |  X- ----O---- X+
   *     .   |/ |  |          |  o  |        /|
   *     .   oX-o  +--o----o--|-----+       / |
   *     .   | /  /  / Y+ /   |    /    Z- /  | Y+
   *     .   |/  /  o----o    |   /
   *     .   o  /             |  /
   *     .   | /  o----o      | /
   *     .   |/   | Z- |      |/
   *     .   +----o----o------+
   * </pre>
   */
  enum MeshFace
  {
    /*!
     * @brief  The left face (X-)of a CLOD terrain mesh.
     * 
     * Meshes that use a sphere as base geometry possess all six faces.Meshes that use a square as 
     * base geometry only have the #MeshFace_Front face.
     * <pre>
     *     .         +----------------+
     *     .        /|               /|
     *     .       /#|              / |
     *     .      /##|             /  |
     *     .     /###|            /   |
     *     .    /####|           /    |      Y- |  / Z+
     *     .   +----------------+     |         | /
     *     .   |#####|          |     |         |/
     *     .   |#####|          |     |  X- ----O---- X+
     *     .   |#####|          |     |        /|
     *     .   |#####+----------|-----+       / |
     *     .   |####/           |    /    Z- /  | Y+
     *     .   |###/            |   /
     *     .   |##/             |  /
     *     .   |#/              | /
     *     .   |/               |/
     *     .   +----------------+
     * </pre>
     */
    MeshFace_Left = 0,
    
    /*!
     * @brief  The right face (X+)of a CLOD terrain mesh.
     * 
     * Meshes that use a sphere as base geometry possess all six faces.Meshes that use a square as 
     * base geometry only have the #MeshFace_Front face.
     * <pre>
     *     .         +----------------+
     *     .        /|               /|
     *     .       / |              /#|
     *     .      /  |             /##|
     *     .     /   |            /###|
     *     .    /    |           /####|      Y- |  / Z+
     *     .   +----------------+#####|         | /
     *     .   |     |          |#####|         |/
     *     .   |     |          |#####|  X- ----O---- X+
     *     .   |     |          |#####|        /|
     *     .   |     +----------|#####+       / |
     *     .   |    /           |####/    Z- /  | Y+
     *     .   |   /            |###/
     *     .   |  /             |##/
     *     .   | /              |#/
     *     .   |/               |/
     *     .   +----------------+
     * </pre>
     */
    MeshFace_Right = 1,
    
    /*!
     * @brief  The top face (Y-)of a CLOD terrain mesh.
     * 
     * Meshes that use a sphere as base geometry possess all six faces.Meshes that use a square as 
     * base geometry only have the #MeshFace_Front face.
     * <pre>
     *     .         +----------------+
     *     .        /################/|
     *     .       /################/ |
     *     .      /################/  |
     *     .     /################/   |
     *     .    /################/    |      Y- |  / Z+
     *     .   +----------------+     |         | /
     *     .   |     |          |     |         |/
     *     .   |     |          |     |  X- ----O---- X+
     *     .   |     |          |     |        /|
     *     .   |     +----------|-----+       / |
     *     .   |    /           |    /    Z- /  | Y+
     *     .   |   /            |   /
     *     .   |  /             |  /
     *     .   | /              | /
     *     .   |/               |/
     *     .   +----------------+
     * </pre>
     */
    MeshFace_Top = 2,
    
    /*!
     * @brief  The bottom face (Y+)of a CLOD terrain mesh.
     * 
     * Meshes that use a sphere as base geometry possess all six faces.Meshes that use a square as 
     * base geometry only have the #MeshFace_Front face.
     * <pre>
     *     .         +----------------+
     *     .        /|               /|
     *     .       / |              / |
     *     .      /  |             /  |
     *     .     /   |            /   |
     *     .    /    |           /    |      Y- |  / Z+
     *     .   +----------------+     |         | /
     *     .   |     |          |     |         |/
     *     .   |     |          |     |  X- ----O---- X+
     *     .   |     |          |     |        /|
     *     .   |     +----------|-----+       / |
     *     .   |    /###########|####/    Z- /  | Y+
     *     .   |   /############|###/
     *     .   |  /#############|##/
     *     .   | /##############|#/
     *     .   |/###############|/
     *     .   +----------------+
     * </pre>
     */
    MeshFace_Bottom = 3,
    
    /*!
     * @brief  The front face (Z-)of a CLOD terrain mesh.
     * 
     * Meshes that use a sphere as base geometry possess all six faces.Meshes that use a square as 
     * base geometry only have the #MeshFace_Front face.
     * <pre>
     *     .         +----------------+
     *     .        /|               /|
     *     .       / |              / |
     *     .      /  |             /  |
     *     .     /   |            /   |
     *     .    /    |           /    |      Y- |  / Z+
     *     .   +----------------+     |         | /
     *     .   |################|     |         |/
     *     .   |################|     |  X- ----O---- X+
     *     .   |################|     |        /|
     *     .   |################|-----+       / |
     *     .   |################|    /    Z- /  | Y+
     *     .   |################|   /
     *     .   |################|  /
     *     .   |################| /
     *     .   |################|/
     *     .   +----------------+
     * </pre>
     */
    MeshFace_Front = 4,
    
    /*!
     * @brief  The back face (Z+)of a CLOD terrain mesh.
     * 
     * Meshes that use a sphere as base geometry possess all six faces.Meshes that use a square as 
     * base geometry only have the #MeshFace_Front face.
     * <pre>
     *     .         +----------------+
     *     .        /|###############/|
     *     .       / |##############/#|
     *     .      /  |#############/##|
     *     .     /   |############/###|
     *     .    /    |###########/####|      Y- |  / Z+
     *     .   +----------------+#####|         | /
     *     .   |     |##########|#####|         |/
     *     .   |     |##########|#####|  X- ----O---- X+
     *     .   |     |##########|#####|        /|
     *     .   |     +----------|-----+       / |
     *     .   |    /           |    /    Z- /  | Y+
     *     .   |   /            |   /
     *     .   |  /             |  /
     *     .   | /              | /
     *     .   |/               |/
     *     .   +----------------+
     * </pre>
     */
    MeshFace_Back = 5,
    
    /*!
     * @brief  Represents all faces of a CLOD terrain mesh (X-,X+,Y-,Y+,Z- and Z+).
     * 
     * Meshes that use a sphere as base geometry possess all six faces.Meshes that use a square as 
     * base geometry only have the #MeshFace_Front face.
     * <pre>
     *     .         +----------------+
     *     .        /################/|
     *     .       /################/#|
     *     .      /################/##|
     *     .     /################/###|
     *     .    /################/####|      Y- |  / Z+
     *     .   +----------------+#####|         | /
     *     .   |################|#####|         |/
     *     .   |################|#####|  X- ----O---- X+
     *     .   |################|#####|        /|
     *     .   |################|#####+       / |
     *     .   |################|####/    Z- /  | Y+
     *     .   |################|###/
     *     .   |################|##/
     *     .   |################|#/
     *     .   |################|/
     *     .   +----------------+
     * </pre>
     */
    MeshFace_All = 6,
    
    /*!
     * @brief  A volumetric CLOD mesh does not have individual mesh faces.The 
     *         special #MeshFace_Volume mesh face is used in these cases.
     */
    MeshFace_Volume = 7
  };
  
} } 

#endif
