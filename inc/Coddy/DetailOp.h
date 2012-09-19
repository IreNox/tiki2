////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_BRUSHES_DETAILOP_H
#define CLODDY_API_HEIGHTMAPS_BRUSHES_DETAILOP_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Heightmaps::Brushes::DetailOp.

namespace Cloddy { namespace API { namespace Heightmaps { namespace Brushes
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of detail channel value operations.
   */
  enum DetailOp
  {
    /*!
     * @brief  Sums the source and target detail components.
     */
    DetailOp_Add = 0,
    
    /*!
     * @brief  Sets the target detail components.
     */
    DetailOp_Set = 1,
    
    /*!
     * @brief  Subtracts the target color components from the source detail components.
     */
    DetailOp_Subtract = 2,
    
    /*!
     * @brief  Multiplies the components of source and target detail.
     */
    DetailOp_Modulate = 3,
    
    /*!
     * @brief  Computes the component wise minimum of source and target detail.
     */
    DetailOp_Minimum = 4,
    
    /*!
     * @brief  Computes the component wise maximum of source and target detail.
     */
    DetailOp_Maximum = 5
  };
  
} } } } 

#endif
