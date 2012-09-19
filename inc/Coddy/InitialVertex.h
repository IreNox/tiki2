////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_INITIALVERTEX_H
#define CLODDY_KERNEL_INITIALVERTEX_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Kernel::InitialVertex.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of initial mesh vertices.
   */
  enum InitialVertex
  {
    /*!
     * @brief  The top-left initial vertex (indicated by <c>[+]</c> below)for CLOD meshes that use 
     *         the BaseGeometry::BaseGeometry_Square base geometry.
     * 
     * <pre>
     *     [+]---------+           Y-
     *     |          |           |            left   = X-
     *     |          |           |            right  = X+
     *     |          |     X- ---O--- X+      top    = Y-
     *     |          |           |            bottom = Y+
     *     |          |           |
     *     +----------+           Y+
     * </pre>
     */
    InitialVertex_SquareTopLeft = 0,
    
    /*!
     * @brief  The top-right initial vertex (indicated by <c>[+]</c> below)for CLOD meshes that use 
     *         the BaseGeometry::BaseGeometry_Square base geometry.
     * 
     * <pre>
     *     +---------[+]          Y-
     *     |          |           |            left   = X-
     *     |          |           |            right  = X+
     *     |          |     X- ---O--- X+      top    = Y-
     *     |          |           |            bottom = Y+
     *     |          |           |
     *     +----------+           Y+
     * </pre>
     */
    InitialVertex_SquareTopRight = 1,
    
    /*!
     * @brief  The bottom-left initial vertex (indicated by <c>[+]</c> below)for CLOD meshes that 
     *         use the BaseGeometry::BaseGeometry_Square base geometry.
     * 
     * <pre>
     *     .    +----------+           Y-
     *     .    |          |           |            left   = X-
     *     .    |          |           |            right  = X+
     *     .    |          |     X- ---O--- X+      top    = Y-
     *     .    |          |           |            bottom = Y+
     *     .    |          |           |
     *     .   [+]---------+           Y+
     * </pre>
     */
    InitialVertex_SquareBottomLeft = 2,
    
    /*!
     * @brief  The bottom-right initial vertex (indicated by <c>[+]</c> below)for CLOD meshes that 
     *         use the BaseGeometry::BaseGeometry_Square base geometry.
     * 
     * <pre>
     *     +----------+           Y-
     *     |          |           |            left   = X-
     *     |          |           |            right  = X+
     *     |          |     X- ---O--- X+      top    = Y-
     *     |          |           |            bottom = Y+
     *     |          |           |
     *     +---------[+]          Y+
     * </pre>
     */
    InitialVertex_SquareBottomRight = 3,
    
    /*!
     * @brief  The left-top-front initial vertex (indicated by <c>[+]</c> below)for CLOD meshes 
     *         that use the BaseGeometry::BaseGeometry_Sphere base geometry.
     * 
     * <pre>
     *     .     base cube:     right-handed cs:    
     *     .       +-------+                     
     *     .      /.      /|        Y- |  / Z+      left   = X-   
     *     .     / .     / |           | /          right  = X+   
     *     .   [+]------+  |           |/           top    = Y- 
     *     .    |  .....|..+    X- ----O---- X+     bottom = Y+
     *     .    | .     | /           /|            front  = Z-  
     *     .    |.      |/           / |            back   = Z+
     *     .    +-------+        Z- /  | Y+         
     * </pre>
     */
    InitialVertex_SphereLeftTopFront = 4,
    
    /*!
     * @brief  The left-top-back initial vertex (indicated by <c>[+]</c> below)for CLOD meshes that 
     *         use the BaseGeometry::BaseGeometry_Sphere base geometry.
     * 
     * <pre>
     *     .   base cube:      right-handed cs:    
     *     .     [+]------+                     
     *     .     /.      /|        Y- |  / Z+      left   = X-   
     *     .    / .     / |           | /          right  = X+   
     *     .   +-------+  |           |/           top    = Y- 
     *     .   |  .....|..+    X- ----O---- X+     bottom = Y+
     *     .   | .     | /           /|            front  = Z-  
     *     .   |.      |/           / |            back   = Z+
     *     .   +-------+        Z- /  | Y+         
     * </pre>
     */
    InitialVertex_SphereLeftTopBack = 5,
    
    /*!
     * @brief  The right-top-front initial vertex (indicated by <c>[+]</c> below)for CLOD meshes 
     *         that use the BaseGeometry::BaseGeometry_Sphere base geometry.
     * 
     * <pre>
     *     .   base cube:      right-handed cs:    
     *     .      +-------+                     
     *     .     /.      /|        Y- |  / Z+      left   = X-   
     *     .    / .     / |           | /          right  = X+   
     *     .   +------[+] |           |/           top    = Y- 
     *     .   |  .....|..+    X- ----O---- X+     bottom = Y+
     *     .   | .     | /           /|            front  = Z-  
     *     .   |.      |/           / |            back   = Z+
     *     .   +-------+        Z- /  | Y+         
     * </pre>
     */
    InitialVertex_SphereRightTopFront = 6,
    
    /*!
     * @brief  The right-top-back initial vertex (indicated by <c>[+]</c> below)for CLOD meshes 
     *         that use the BaseGeometry::BaseGeometry_Sphere base geometry.
     * 
     * <pre>
     *     .   base cube:      right-handed cs:    
     *     .      +------[+]                    
     *     .     /.      /|        Y- |  / Z+      left   = X-   
     *     .    / .     / |           | /          right  = X+   
     *     .   +-------+  |           |/           top    = Y- 
     *     .   |  .....|..+    X- ----O---- X+     bottom = Y+
     *     .   | .     | /           /|            front  = Z-  
     *     .   |.      |/           / |            back   = Z+
     *     .   +-------+        Z- /  | Y+         
     * </pre>
     */
    InitialVertex_SphereRightTopBack = 7,
    
    /*!
     * @brief  The left-bottom-front initial vertex (indicated by <c>[+]</c> below)for CLOD meshes 
     *         that use the BaseGeometry::BaseGeometry_Sphere base geometry.
     * 
     * <pre>
     *     .    base cube:      right-handed cs:    
     *     .       +-------+                     
     *     .      /.      /|        Y- |  / Z+      left   = X-   
     *     .     / .     / |           | /          right  = X+   
     *     .    +-------+  |           |/           top    = Y- 
     *     .    |  .....|..+    X- ----O---- X+     bottom = Y+
     *     .    | .     | /           /|            front  = Z-  
     *     .    |.      |/           / |            back   = Z+
     *     .   [+]------+        Z- /  | Y+         
     * </pre>
     */
    InitialVertex_SphereLeftBottomFront = 8,
    
    /*!
     * @brief  The left-bottom-back initial vertex (indicated by <c>[+]</c> below)for CLOD meshes 
     *         that use the BaseGeometry::BaseGeometry_Sphere base geometry.
     * 
     * <pre>
     *     .   base cube:      right-handed cs:    
     *     .      +-------+                     
     *     .     /.      /|        Y- |  / Z+      left   = X-   
     *     .    / .     / |           | /          right  = X+   
     *     .   +-------+  |           |/           top    = Y- 
     *     .   | [+]...|..+    X- ----O---- X+     bottom = Y+
     *     .   | .     | /           /|            front  = Z-  
     *     .   |.      |/           / |            back   = Z+
     *     .   +-------+        Z- /  | Y+         
     * </pre>
     */
    InitialVertex_SphereLeftBottomBack = 9,
    
    /*!
     * @brief  The right-bottom-front initial vertex (indicated by <c>[+]</c> below)for CLOD meshes 
     *         that use the BaseGeometry::BaseGeometry_Sphere base geometry.
     * 
     * <pre>
     *     .   base cube:      right-handed cs:    
     *     .      +-------+                     
     *     .     /.      /|        Y- |  / Z+      left   = X-   
     *     .    / .     / |           | /          right  = X+   
     *     .   +-------+  |           |/           top    = Y- 
     *     .   |  .....|..+    X- ----O---- X+     bottom = Y+
     *     .   | .     | /           /|            front  = Z-  
     *     .   |.      |/           / |            back   = Z+
     *     .   +------[+]       Z- /  | Y+         
     * </pre>
     */
    InitialVertex_SphereRightBottomFront = 10,
    
    /*!
     * @brief  The right-bottom-back initial vertex (indicated by <c>[+]</c> below)for CLOD meshes 
     *         that use the BaseGeometry::BaseGeometry_Sphere base geometry.
     * 
     * <pre>
     *     .   base cube:      right-handed cs:    
     *     .      +-------+                     
     *     .     /.      /|        Y- |  / Z+      left   = X-   
     *     .    / .     / |           | /          right  = X+   
     *     .   +-------+  |           |/           top    = Y- 
     *     .   |  .....|.[+]   X- ----O---- X+     bottom = Y+
     *     .   | .     | /           /|            front  = Z-  
     *     .   |.      |/           / |            back   = Z+
     *     .   +-------+        Z- /  | Y+         
     * </pre>
     */
    InitialVertex_SphereRightBottomBack = 11
  };
  
} } 

#endif
