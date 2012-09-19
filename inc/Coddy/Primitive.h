////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_RENDERING_PRIMITIVE_H
#define CLODDY_API_RENDERING_PRIMITIVE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Rendering::Primitive.

namespace Cloddy { namespace API { namespace Rendering
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of graphic primitives.
   */
  enum Primitive
  {
    /*!
     * @brief  A point list.
     */
    Primitive_PointList = 0,
    
    /*!
     * @brief  A line strip.
     */
    Primitive_LineStrip = 1,
    
    /*!
     * @brief  A line list.
     */
    Primitive_LineList = 2,
    
    /*!
     * @brief  A triangle strip.
     */
    Primitive_TriangleStrip = 3,
    
    /*!
     * @brief  A triangle fan.
     */
    Primitive_TriangleFan = 4,
    
    /*!
     * @brief  A triangle list.
     */
    Primitive_TriangleList = 5
  };
  
} } } 

#endif
