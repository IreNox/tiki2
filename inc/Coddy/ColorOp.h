////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_COLOROP_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_COLOROP_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Heightmaps::Brushes::ColorOp.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of color operations.
   */
  enum ColorOp
  {
    /*!
     * @brief  Sums the source and target color components.
     */
    ColorOp_Add = 0,
    
    /*!
     * @brief  Subtracts the target color components from the source color components.
     */
    ColorOp_Subtract = 1,
    
    /*!
     * @brief  Multiplies the components of source and target color.
     */
    ColorOp_Modulate = 2,
    
    /*!
     * @brief  Blends the color components of source and target color based on target alpha value.
     */
    ColorOp_Blend = 3,
    
    /*!
     * @brief  Computes the component wise minimum of source and target color.
     */
    ColorOp_Minimum = 4,
    
    /*!
     * @brief  Computes the component wise maximum of source and target color.
     */
    ColorOp_Maximum = 5
  };
  
} } } } 

#endif
