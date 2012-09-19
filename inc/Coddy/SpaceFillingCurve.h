////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATASETS_SPACEFILLINGCURVE_H
#define CLODDY_API_DATASETS_SPACEFILLINGCURVE_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/Vec2I.h"
#include "Cloddy/Vec3I.h"

// Declare class ::Cloddy::API::Datasets::SpaceFillingCurve.

namespace Cloddy { namespace API { namespace Datasets
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec2I;
  using Cloddy::Core::Math::Vectors::Vec3I;
  
  /*!
   * @brief  Implements a bijective mapping from two- or three-dimensional map coordinates onto 
   *         one-dimensional indices unsing hilbert space-filling curves.
   * 
   * The static \c Map  methods provide a mapping from a two-dimensional map of size 
   * <c>2^n *2^n</c> (where <c>0 &lt;=n &lt;=20</c>)to a one-dimensional index in the range 
   * <c>[0..2^(2*n)-1]</c>.The static method #Unmap2D provides the respective inverse mapping.
   * 
   * TODO:Set 2D coord range to [0..2^28 - 1]
   */
  class SpaceFillingCurve
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Maximum coordinate value produced by #Unmap2D and accepted by \c Map2D .
     */
    static const int32 MaxCoord2D = 0xFFFFF;
    
    /*!
     * @brief  Maximum coordinate value produced by #Unmap3D and accepted by \c Map3D .
     */
    static const int32 MaxCoord3D = 0x1FFFFF;
    
    /*!
     * @brief  Maximum index value produced by \c Map2D  and accepted by #Unmap2D.
     */
    static const int64 MaxIndex2D = (int64) 0xFFFFFFFFFFULL;
    
    /*!
     * @brief  Maximum index value produced by \c Map3D  and accepted by #Unmap3D.
     */
    static const int64 MaxIndex3D = (int64) 0x7FFFFFFFFFFFFFFFULL;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Maps the given two-dimensional coordinates to an one-dimensional index value.
     * 
     * The \e v .X and \e v .Y coordinates must lie within the range [0..#MaxCoord2D].
     * 
     * The returned index will be in range [0..#MaxIndex2D].
     * 
     * Additionally,the following condition will always be true:
     * <pre>
     *       Map(x,y) &lt; 2^(2 * floor(log2(max(x,y))) + 2)
     * </pre>
     * where \c x  and \c y  are the two-dimensional map coordinates.
     * 
     * @param v The coordinates.
     * 
     * @return The index value.
     * 
     * @see #Unmap2D
     */
    static int64 Map2D(const Vec2I& v);
    
    /*!
     * @brief  Maps the given two-dimensional coordinates to an one-dimensional index value.
     * 
     * The \e x  and \e y  coordinates must lie within the range [0..#MaxCoord2D].
     * 
     * The returned index will be in range [0..#MaxIndex2D].
     * 
     * @param x X-component of coordinates.
     * @param y Y-component of coordinates.
     * 
     * @return The index value.
     * 
     * @see #Unmap2D
     */
    static int64 Map2D(int32 x, int32 y);
    
    /*!
     * @brief  Maps the given three-dimensional coordinates to an one-dimensional index value.
     * 
     * The \e v .X,\e v .Y and \e v .Z coordinates must lie within the range [0..#MaxCoord2D].
     * 
     * The returned index will be in range [0..#MaxIndex2D].
     * 
     * @param v The coordinates.
     * 
     * @return The index value.
     * 
     * @see #Unmap2D
     */
    static int64 Map3D(const Vec3I& v);
    
    /*!
     * @brief  Maps the given three-dimensional coordinates to an one-dimensional index value.
     * 
     * The \e x ,\e y  and \e z  coordinates must lie within the range [0..#MaxCoord2D].
     * 
     * The returned index will be in range [0..#MaxIndex2D].
     * 
     * @param x X-component of coordinates.
     * @param y Y-component of coordinates.
     * @param z Z-component of coordinates.
     * 
     * @return The index value.
     * 
     * @see #Unmap2D
     */
    static int64 Map3D(int32 x, int32 y, int32 z);
    
    /*!
     * @brief  Unmaps the given linear index value to a two-dimensional set of map coordinates.
     * 
     * The given \e index  value must lie within the range [0..#MaxIndex2D].
     * 
     * The returned coordinates will be within the range [0..#MaxCoord2D].
     * 
     * @param index The index value.
     * 
     * @return The map coordinates.
     * 
     * @see #Map2D(const Vec2I&)
     * @see #Map2D(int32,int32)
     */
    static Vec2I Unmap2D(int64 index);
    
    static Vec3I Unmap3D(int64 index);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constants
    // ---------------------------------------------------------------------------------------------
  private:
    
    static const int32 O7 = 0x7;
    
    static const int32 O70 = 0x38;
    
    static const int32 O700 = 0x1C0;
    
    static const int32 O77 = 0x3F;
    
    static const int32 O777 = 0x1FF;
    
    static const int32 O7777 = 0xFFF;
    
    static const int32 O77777 = 0x7FFF;
    
    static const int32 O777777 = 0x3FFFF;
    
    static const int32 O777777777 = 0x7FFFFFF;
    
    static const int64 O777777777777 = (int64) 0xFFFFFFFFFULL;
    
    static const int64 O777777777777777 = (int64) 0x1FFFFFFFFFFFULL;
    
    static const int64 O777777777777777777 = (int64) 0x3FFFFFFFFFFFFFULL;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
    
    static const Array<int16> XyToIdx;
    
    static const Array<int16> XyToState;
    
    static const Array<int8> IdxToXy;
    
    static const Array<int16> XyzToIdx;
    
    static const Array<int16> XyzToState;
    
    static const Array<int8> IdxToXyz;
  };
  
} } } 

#endif
