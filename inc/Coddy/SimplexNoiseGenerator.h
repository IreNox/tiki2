////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_SIMPLEXNOISEGENERATOR_H
#define CLODDY_API_PROCEDURAL_SIMPLEXNOISEGENERATOR_H

#include "CodeX/System.h"

// Declare class ::Cloddy::API::Procedural::SimplexNoiseGenerator.

namespace Cloddy { namespace API { namespace Procedural
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  This class is a generator for three dimensional simplex based perlin noise.
   */
  class SimplexNoiseGenerator
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Computes a simplex noise value.
     * 
     * @param x Input X-coordinate.
     * @param y Input Y-coordinate.
     * @param z Input Z-coordinate.
     * 
     * @return The noise value.
     */
    static float64 Compute(float64 x, float64 y, float64 z);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Noise gradient vectors,premultiplied with 32.
     */
    static const Array<int32> Grad;
    
    /*!
     * @brief  Precomputed permutation table.
     */
    static const Array<int32> Perm;
    
    /*!
     * @brief  Precomputed permutation table.
     */
    static const Array<int32> PermMod12;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes the dot product between the given vector and the specified gradient vector.
     * 
     * @param g Index of the gradient vector.
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The dot product.
     */
    static float64 Dot3(int32 g, float64 x, float64 y, float64 z);
  };
  
} } } 

#endif
