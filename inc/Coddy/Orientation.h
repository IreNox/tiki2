////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_ORIENTATION_H
#define CLODDY_KERNEL_ORIENTATION_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::Kernel::Orientation.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of triangle orientations for triangulation of CLOD meshes.
   */
  enum Orientation
  {
    /*!
     * @brief  Triangulation will produce triangle strips with triangles being oriented in 
     *         clockwise orientation.
     */
    Orientation_Clockwise = 0,
    
    /*!
     * @brief  Triangulation will produce triangle strips with triangles being oriented in 
     *         counter-clockwise orientation.
     */
    Orientation_CounterClockwise = 1
  };
  
} } 

#endif
