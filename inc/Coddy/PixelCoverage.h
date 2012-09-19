////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_IMAGING_PIXELCOVERAGE_H
#define CLODDY_API_IMAGING_PIXELCOVERAGE_H

#include "CodeX/System.h"

// Declare enumeration ::Cloddy::API::Imaging::PixelCoverage.

namespace Cloddy { namespace API { namespace Imaging
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Enumeration of pixel coverage semantics.
   * 
   * @see PixelCoverageImage
   */
  enum PixelCoverage
  {
    /*!
     * @brief  Each image pixel represents an area in two-dimensional space.
     * 
     * <pre>
     *     .      0   1   2   3   4   5
     *     .    +---+---+---+---+---+---+
     *     .  0 |###|###|###|###|###|###|
     *     .    +---+---+---+---+---+---+
     *     .  1 |###|###|###|###|###|###|
     *     .    +---+---+---+---+---+---+
     *     .  2 |###|###|###|###|###|###|
     *     .    +---+---+---+---+---+---+
     *     .  3 |###|###|###|###|###|###|
     *     .    +---+---+---+---+---+---+
     *     .
     *     .  ### := Pixel area
     * </pre>
     */
    PixelCoverage_PixelIsArea = 0,
    
    /*!
     * @brief  Each image pixel represents a point in two-dimensional space.
     * 
     * <pre>
     *     .    0   1   2   3   4   5   6
     *     .  0 #---#---#---#---#---#---#
     *     .    |   |   |   |   |   |   |
     *     .  1 #---#---#---#---#---#---#
     *     .    |   |   |   |   |   |   |
     *     .  2 #---#---#---#---#---#---#
     *     .    |   |   |   |   |   |   |
     *     .  3 #---#---#---#---#---#---#
     *     .    |   |   |   |   |   |   |
     *     .  4 #---#---#---#---#---#---#
     *     . 
     *     .  # := Pixel point
     * </pre>
     */
    PixelCoverage_PixelIsPoint = 1
  };
  
} } } 

#endif
