////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_MATHS_H
#define CLODDY_CORE_MATH_MATHS_H

#include "CodeX/System_Native.h"

// Include referenced structures.

#include "Cloddy/Vec3D.h"
#include "Cloddy/Vec3I.h"
#include "Cloddy/Vec4I.h"

// Declare class ::Cloddy::Core::Math::Maths.

namespace Cloddy { namespace Core { namespace Math
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Vec3D;
  using Cloddy::Core::Math::Vectors::Vec3I;
  using Cloddy::Core::Math::Vectors::Vec4I;
  
  /*!
   * @brief  Provides some commonly used math functions.
   */
  class Maths
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constants
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Factor for converting radians to degrees.
     */
    static const float64 DegreesToRadians;
    
    /*!
     * @brief  Maximum value of a 32-bit floating-point.
     */
    static const float64 MaxDouble;
    
    /*!
     * @brief  Maximum value of a 32-bit floating-point.
     */
    static const float32 MaxFloat;
    
    /*!
     * @brief  Maximum value of a 32-bit signed integer.
     */
    static const int32 MaxInt = 2147483647;
    
    /*!
     * @brief  Maximum value of a 64-bit signed integer.
     */
    static const int64 MaxLong = (int64) 9223372036854775807LL;
    
    /*!
     * @brief  Minimum value of a 32-bit floating-point.
     */
    static const float64 MinDouble;
    
    /*!
     * @brief  Minimum value of a 32-bit floating-point.
     */
    static const float32 MinFloat;
    
    /*!
     * @brief  Minimum value of a 32-bit signed integer.
     */
    static const int32 MinInt = 0x80000000;
    
    /*!
     * @brief  Minimum value of a 64-bit signed integer.
     */
    static const int64 MinLong = ((int64) -9223372036854775807LL - 1);
    
    /*!
     * @brief  The value of \c PI .
     */
    static const float64 Pi;
    
    /*!
     * @brief  The value of <c>PI *0.5</c>.
     */
    static const float64 PiHalf;
    
    /*!
     * @brief  The value of <c>PI *2</c>.
     */
    static const float64 PiTwo;
    
    /*!
     * @brief  Factor for converting radians to degrees.
     */
    static const float64 RadiansToDegrees;
    
    /*!
     * @brief  The square root of <c>0.5</c>.
     */
    static const float64 Sqrt05;
    
    /*!
     * @brief  The square root of \c 2 .
     */
    static const float64 Sqrt2;
    
    /*!
     * @brief  The square root of \c 3 .
     */
    static const float64 Sqrt3;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the 64-bit floating point value for:not-a-number.
     * 
     * @return The NaN value.
     */
    static float64 GetNanD();
    
    /*!
     * @brief  Returns the 32-bit floating point value for:not-a-number.
     * 
     * @return The NaN value.
     */
    static float32 GetNanF();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the absolute of the given value.
     * 
     * @param value The value.
     * 
     * @return <b>[>=0]</b>  The absolute value.
     */
    static float64 AbsD(float64 value);
    
    /*!
     * @brief  Returns the absolute of the given value.
     * 
     * @param value The value.
     * 
     * @return <b>[>=0]</b>  The absolute value.
     */
    static float32 AbsF(float32 value);
    
    /*!
     * @brief  Returns the absolute of the given value.
     * 
     * @param value The value.
     * 
     * @return <b>[>=0]</b>  The absolute value.
     */
    static int32 AbsI(int32 value);
    
    /*!
     * @brief  Returns the absolute of the given value.
     * 
     * @param value The value.
     * 
     * @return <b>[>=0]</b>  The absolute value.
     */
    static int64 AbsL(int64 value);
    
    /*!
     * @brief  Returns the angle whose cosine is the specified number.
     * 
     * @param v The number.
     * 
     * @return The angle in radians.
     */
    static float64 Acos(float64 v);
    
    /*!
     * @brief  Computes the area of the given triangle.
     * 
     * @param x1 X-coordinate of first vertex of triangle.
     * @param y1 Y-coordinate of first vertex of triangle.
     * @param z1 Z-coordinate of first vertex of triangle.
     * @param x2 X-coordinate of second vertex of triangle.
     * @param y2 Y-coordinate of second vertex of triangle.
     * @param z2 Z-coordinate of second vertex of triangle.
     * @param x3 X-coordinate of third vertex of triangle.
     * @param y3 Y-coordinate of third vertex of triangle.
     * @param z3 Z-coordinate of third vertex of triangle.
     * 
     * @return The area of the triangle.
     */
    static float64 AreaD(float64 x1, float64 y1, float64 z1, float64 x2, float64 y2, float64 z2, float64 x3, float64 y3, float64 z3);
    
    /*!
     * @brief  Computes the area of the given triangle.
     * 
     * @param x1 X-coordinate of first vertex of triangle.
     * @param y1 Y-coordinate of first vertex of triangle.
     * @param z1 Z-coordinate of first vertex of triangle.
     * @param x2 X-coordinate of second vertex of triangle.
     * @param y2 Y-coordinate of second vertex of triangle.
     * @param z2 Z-coordinate of second vertex of triangle.
     * @param x3 X-coordinate of third vertex of triangle.
     * @param y3 Y-coordinate of third vertex of triangle.
     * @param z3 Z-coordinate of third vertex of triangle.
     * 
     * @return The area of the triangle.
     */
    static float32 AreaF(float32 x1, float32 y1, float32 z1, float32 x2, float32 y2, float32 z2, float32 x3, float32 y3, float32 z3);
    
    /*!
     * @brief  Returns the angle whose sine is the specified number.
     * 
     * @param v The number.
     * 
     * @return The angle in radians.
     */
    static float64 Asin(float64 v);
    
    /*!
     * @brief  Returns the angle whose tangent is the specified number.
     * 
     * @param v A number representing a tangent.
     * 
     * @return The angle,in radians.
     */
    static float64 Atan(float64 v);
    
    /*!
     * @brief  Returns the angle whose tangent is the quotient of two specified numbers.
     * 
     * @param y The Y-coordinate of a point.
     * @param x The X-coordinate of a point.
     * 
     * @return An angle,in radians.
     */
    static float64 Atan2(float64 y, float64 x);
    
    /*!
     * @brief  Converts the given cartesian coordinates into spherical coordinates.
     * 
     * The components of the returned vector have the following semantic:
     * <pre>
     *     spherical.X := radius (distance to origin).
     *     spherical.Y := azimuthal angle (angle from positive X-axis in radians) in the range [-PI..PI].
     *     spherical.Z := polar angle (angle from positive Z-axis in radians) in the range [0..PI]. 
     * </pre>
     * 
     * @param cartesian The cartesion coordinates.
     * 
     * @return The spherical coordinates.
     */
    static Vec3D CartesianToSpherical(const Vec3D& cartesian);
    
    /*!
     * @brief  Converts the given cartesian coordinates into spherical coordinates.
     * 
     * The components of the returned vector have the following semantic:
     * <pre>
     *     spherical.X := radius (distance to origin).
     *     spherical.Y := azimuthal angle (angle from positive X-axis in radians) in the range [-PI..PI].
     *     spherical.Z := polar angle (angle from positive Z-axis in radians) in the range [0..PI]. 
     * </pre>
     * 
     * @param x The cartesian X-coordinate.
     * @param y The cartesian Y-coordinate.
     * @param z The cartesian Z-coordinate.
     * 
     * @return The spherical coordinates.
     */
    static Vec3D CartesianToSpherical(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Mixes the first and second value using a Catmull-Rom spline.
     * 
     * @param a Zeroth float value.
     * @param b First float value.
     * @param c Second float value.
     * @param d Third float value.
     * @param f Mix factor.
     * 
     * @return The mixed value.
     */
    static float64 CatmullRomD(float64 a, float64 b, float64 c, float64 d, float64 f);
    
    /*!
     * @brief  Mixes the first and second value using a Catmull-Rom spline.
     * 
     * @param a Zeroth float value.
     * @param b First float value.
     * @param c Second float value.
     * @param d Third float value.
     * @param f Mix factor.
     * 
     * @return The mixed value.
     */
    static float32 CatmullRomF(float32 a, float32 b, float32 c, float32 d, float32 f);
    
    /*!
     * @brief  Mixes the first and second 16-bit value using a discrete Catmull-Rom spline.
     * 
     * @param a Zeroth 16-bit value in the range [0..65535].
     * @param b First 16-bit value in the range [0..65535].
     * @param c Second 16-bit value in the range [0..65535].
     * @param d Third 16-bit value in the range [0..65535].
     * @param f Mix factor in the range <c>[0..65536]</c>.
     * 
     * @return <b>[0..65535]</b>  The mixed 16-bit value.
     */
    static int32 CatmullRomI16(int32 a, int32 b, int32 c, int32 d, int32 f);
    
    /*!
     * @brief  Mixes the first and second 32-bit values using a discrete Catmull-Rom spline.
     * 
     * @param a Zeroth 32-bit value.
     * @param b First 32-bit value.
     * @param c Second 32-bit value.
     * @param d Third 32-bit value.
     * @param f Mix factor in the range <c>[0..65536]</c>.
     * 
     * @return The mixed 32-bit value.
     */
    static int32 CatmullRomI32(int32 a, int32 b, int32 c, int32 d, int32 f);
    
    /*!
     * @brief  Mixes the first and second 8-bit value using a discrete Catmull-Rom spline.
     * 
     * @param a Zeroth 8-bit value in the range [0..255].
     * @param b First 8-bit value in the range [0..255].
     * @param c Second 8-bit value in the range [0..255].
     * @param d Third 8-bit value in the range [0..255].
     * @param f Mix factor in the range <c>[0..65536]</c>.
     * 
     * @return <b>[0..255]</b>  The mixed 8-bit value.
     */
    static int32 CatmullRomI8(int32 a, int32 b, int32 c, int32 d, int32 f);
    
    /*!
     * @brief  Returns the smallest integer greater than or equal to the specified double-precision 
     *         floating-point number.
     * 
     * @param number A double-precision floating-point number.
     * 
     * @return The smallest integer greater than or equal to \e number .
     */
    static float64 CeilingD(float64 number);
    
    /*!
     * @brief  Returns the smallest integer greater than or equal to the specified single-precision 
     *         floating-point number.
     * 
     * @param number A single-precision floating-point number.
     * 
     * @return The smallest integer greater than or equal to \e number .
     */
    static float32 CeilingF(float32 number);
    
    /*!
     * @brief  Clamps the given value.
     * 
     * @param value The value.
     * @param lower Lower boundary to clamp to.
     * @param upper Upper boundary to clamp to.
     * 
     * @return The clamped value.
     */
    static float64 ClampD(float64 value, float64 lower, float64 upper);
    
    /*!
     * @brief  Clamps the given value.
     * 
     * @param value The value.
     * @param lower Lower boundary to clamp to.
     * @param upper Upper boundary to clamp to.
     * 
     * @return The clamped value.
     */
    static float32 ClampF(float32 value, float32 lower, float32 upper);
    
    /*!
     * @brief  Clamps the given value.
     * 
     * @param value The value.
     * @param lower Lower boundary to clamp to.
     * @param upper Upper boundary to clamp to.
     * 
     * @return The clamped value.
     */
    static int32 ClampI(int32 value, int32 lower, int32 upper);
    
    /*!
     * @brief  Clamps the given value.
     * 
     * @param value The value.
     * @param lower Lower boundary to clamp to.
     * @param upper Upper boundary to clamp to.
     * 
     * @return The clamped value.
     */
    static int64 ClampL(int64 value, int64 lower, int64 upper);
    
    /*!
     * @brief  Returns the cosine of the specified angle.
     * 
     * @param radians An angle,measured in radians.
     * 
     * @return The cosine of \e radians .
     */
    static float64 Cos(float64 radians);
    
    /*!
     * @brief  Computes the hyperbolic cosine of the given value.
     * 
     * @param v The value.
     * 
     * @return The hyperbolic cosine of \e v .
     */
    static float64 Cosh(float64 v);
    
    /*!
     * @brief  Returns e raised to the specified power.
     * 
     * @param power A number specifying a power.
     * 
     * @return The resulting value.
     */
    static float64 Exp(float64 power);
    
    /*!
     * @brief  Computes the integer floor value of the given double value.
     * 
     * @param x The double value.
     * 
     * @return The integer floor value.
     */
    static int64 FastFloorD(float64 x);
    
    /*!
     * @brief  Computes the integer floor value of the given float value.
     * 
     * @param x The float value.
     * 
     * @return The integer floor value.
     */
    static int32 FastFloorF(float32 x);
    
    /*!
     * @brief  Computes the floor value of the given value.
     * 
     * @param v The value.
     * 
     * @return The floor value.
     */
    static float64 FloorD(float64 v);
    
    /*!
     * @brief  Computes the floor value of the given value.
     * 
     * @param v The value.
     * 
     * @return The floor value.
     */
    static float32 FloorF(float32 v);
    
    /*!
     * @brief  Checks if the given floating point number is NaN (not-a-number).
     * 
     * @param number The number.
     * 
     * @return \c true  if \e number  is NaN,\c false  if not.
     */
    static bool IsNanD(float64 number);
    
    /*!
     * @brief  Checks if the given floating point number is NaN (not-a-number).
     * 
     * @param number The number.
     * 
     * @return \c true  if \e number  is NaN,\c false  if not.
     */
    static bool IsNanF(float32 number);
    
    /*!
     * @brief  Checks if the given value is a power of two.
     * 
     * A value \e v  that satisfies the equation <i>v =2^n</i> with <i>0 &lt; n &lt; 31</i> is said 
     * to be a power of two.
     * 
     * @param v An integer value.
     * 
     * @return true if \e v  is a power of two,false if not.
     */
    static bool IsPowerOfTwo(int32 v);
    
    /*!
     * @brief  Computes the length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The vector length.
     */
    static float64 LengthD(float64 x, float64 y);
    
    /*!
     * @brief  Computes the length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The vector length.
     */
    static float64 LengthD(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Computes the length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The vector length.
     */
    static float32 LengthF(float32 x, float32 y);
    
    /*!
     * @brief  Computes the length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The vector length.
     */
    static float32 LengthF(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Computes the square length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The square vector length.
     */
    static float64 LengthSqrD(float64 x, float64 y);
    
    /*!
     * @brief  Computes the square length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The square vector length.
     */
    static float64 LengthSqrD(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Computes the square length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * 
     * @return The square vector length.
     */
    static float32 LengthSqrF(float32 x, float32 y);
    
    /*!
     * @brief  Computes the square length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The square vector length.
     */
    static float32 LengthSqrF(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Returns the natural (base e)logarithm of a specified number.
     * 
     * @param number A number whose logarithm is to be found.
     * 
     * @return Positive The natural logarithm of \e number .
     */
    static float64 Log(float64 number);
    
    /*!
     * @brief  Returns the discrete logarithm of base two of the given value.
     * 
     * The discrete logarithm of base two is computed as follows:
     * 
     * <c>log2 :=floor(log(v)/log(2))</c> 
     * 
     * @param v <b>[>0]</b>  The value.
     * 
     * @return <b>[0..30]</b>  The discrete logarithm of \e v .
     */
    static int32 Log2(int32 v);
    
    /*!
     * @brief  Returns the maximum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * 
     * @return The maximum value.
     */
    static float64 MaxD(float64 a, float64 b);
    
    /*!
     * @brief  Returns the maximum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * @param c Third value.
     * 
     * @return The maximum value.
     */
    static float64 MaxD(float64 a, float64 b, float64 c);
    
    /*!
     * @brief  Returns the maximum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * 
     * @return The maximum value.
     */
    static float32 MaxF(float32 a, float32 b);
    
    /*!
     * @brief  Returns the maximum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * @param c Third value.
     * 
     * @return The maximum value.
     */
    static float32 MaxF(float32 a, float32 b, float32 c);
    
    /*!
     * @brief  Returns the maximum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * 
     * @return The maximum value.
     */
    static int32 MaxI(int32 a, int32 b);
    
    /*!
     * @brief  Returns the maximum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * @param c Third value.
     * 
     * @return The maximum value.
     */
    static int32 MaxI(int32 a, int32 b, int32 c);
    
    /*!
     * @brief  Returns the maximum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * 
     * @return The maximum value.
     */
    static int64 MaxL(int64 a, int64 b);
    
    /*!
     * @brief  Returns the maximum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * @param c Third value.
     * 
     * @return The maximum value.
     */
    static int64 MaxL(int64 a, int64 b, int64 c);
    
    /*!
     * @brief  Returns the minimum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * 
     * @return The maximum value.
     */
    static float64 MinD(float64 a, float64 b);
    
    /*!
     * @brief  Returns the minimum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * @param c Third value.
     * 
     * @return The maximum value.
     */
    static float64 MinD(float64 a, float64 b, float64 c);
    
    /*!
     * @brief  Returns the minimum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * 
     * @return The maximum value.
     */
    static float32 MinF(float32 a, float32 b);
    
    /*!
     * @brief  Returns the minimum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * @param c Third value.
     * 
     * @return The maximum value.
     */
    static float32 MinF(float32 a, float32 b, float32 c);
    
    /*!
     * @brief  Returns the minimum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * 
     * @return The maximum value.
     */
    static int32 MinI(int32 a, int32 b);
    
    /*!
     * @brief  Returns the minimum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * @param c Third value.
     * 
     * @return The maximum value.
     */
    static int32 MinI(int32 a, int32 b, int32 c);
    
    /*!
     * @brief  Returns the minimum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * 
     * @return The maximum value.
     */
    static int64 MinL(int64 a, int64 b);
    
    /*!
     * @brief  Returns the minimum of the given values.
     * 
     * @param a First value.
     * @param b Second value.
     * @param c Third value.
     * 
     * @return The maximum value.
     */
    static int64 MinL(int64 a, int64 b, int64 c);
    
    /*!
     * @brief  Computes the module of <c>x /y</c>.
     * 
     * @param x The dividend.
     * @param y The divisor.
     * 
     * @return The modulo.
     */
    static float64 ModD(float64 x, float64 y);
    
    /*!
     * @brief  Computes the module of <c>x /y</c>.
     * 
     * @param x The dividend.
     * @param y The divisor.
     * 
     * @return The modulo.
     */
    static float32 ModF(float32 x, float32 y);
    
    /*!
     * @brief  Returns the smallest power of two that is greater than or equal to the given value.
     * 
     * @param v The value.
     * 
     * @return <b>[>=1]</b>  The next power of two.
     */
    static int64 NextPowerOfTwo(int32 v);
    
    /*!
     * @brief  Packs the given 8-bit integer values into a 32-bit floating-point value.
     * 
     * @param a <b>[0..255]</b>  First integer value to pack.
     * @param b <b>[0..255]</b>  Second integer value to pack.
     * @param c <b>[0..255]</b>  Third integer value to pack.
     * 
     * @return The packed floating-point value.
     * 
     * @see #Unpack3
     */
    static float32 Pack(int32 a, int32 b, int32 c);
    
    /*!
     * @brief  Packs the given 6-bit integer values into a 32-bit floating-point value.
     * 
     * @param a <b>[0..63]</b>  First integer value to pack.
     * @param b <b>[0..63]</b>  Second integer value to pack.
     * @param c <b>[0..63]</b>  Third integer value to pack.
     * @param d <b>[0..63]</b>  Third integer value to pack.
     * 
     * @return The packed floating-point value.
     * 
     * @see #Unpack3
     */
    static float32 Pack(int32 a, int32 b, int32 c, int32 d);
    
    /*!
     * @brief  Raises the given value by the specified power.
     * 
     * @param value The value.
     * @param power The power.
     * 
     * @return The resulting value.
     */
    static float64 Pow(float64 value, float64 power);
    
    /*!
     * @brief  Computes the reciprocal length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The reciprocal vector length or \c 0  if all vector components are zero.
     */
    static float64 RLengthD(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Computes the reciprocal length of the given vector.
     * 
     * @param x X-component of vector.
     * @param y Y-component of vector.
     * @param z Z-component of vector.
     * 
     * @return The reciprocal vector length or \c 0  if all vector components are zero.
     */
    static float32 RLengthF(float32 x, float32 y, float32 z);
    
    /*!
     * @brief  Returns the sine of the specified angle.
     * 
     * @param radians An angle,measured in radians.
     * 
     * @return The sine of \e radians .
     */
    static float64 Sin(float64 radians);
    
    /*!
     * @brief  Computes the hyperbolic sine of the given value.
     * 
     * @param v The value.
     * 
     * @return The hyperbolic sine of \e v .
     */
    static float64 Sinh(float64 v);
    
    /*!
     * @brief  Interpolates between the given values.
     * 
     * This method uses the following polynomal:
     * <pre>
     * -2 * f^3 + 3 * f^2
     * </pre>
     * 
     * @param a First value.
     * @param b Second value.
     * @param f Interpolation factor.
     * 
     * @return The interpolated value.
     */
    static float64 SmoothStepD(float64 a, float64 b, float64 f);
    
    /*!
     * @brief  Interpolates between the given values.
     * 
     * This method uses the following polynomal:
     * <pre>
     * -2 * f^3 + 3 * f^2
     * </pre>
     * 
     * @param a First value.
     * @param b Second value.
     * @param f Interpolation factor.
     * 
     * @return The interpolated value.
     */
    static float32 SmoothStepF(float32 a, float32 b, float32 f);
    
    /*!
     * @brief  Interpolates between the given values.
     * 
     * This method uses the following polynomal:
     * <pre>
     * 6 * f^5 - 15 * f^4 + 10 * f^3
     * </pre>
     * 
     * @param a First value.
     * @param b Second value.
     * @param f Interpolation factor.
     * 
     * @return The interpolated value.
     */
    static float64 SmootherStepD(float64 a, float64 b, float64 f);
    
    /*!
     * @brief  Interpolates between the given values.
     * 
     * This method uses the following polynomal:
     * <pre>
     * 6 * f^5 - 15 * f^4 + 10 * f^3
     * </pre>
     * 
     * @param a First value.
     * @param b Second value.
     * @param f Interpolation factor.
     * 
     * @return The interpolated value.
     */
    static float32 SmootherStepF(float32 a, float32 b, float32 f);
    
    /*!
     * @brief  Converts the given spherical coordinates into cartesian coordinates.
     * 
     * The components of the given vector have the following semantic:
     * <pre>
     *     spherical.X := radius (distance to origin).
     *     spherical.Y := azimuthal angle (angle from positive X-axis in radians) in the range [-PI..PI].
     *     spherical.Z := polar angle (angle from positive Z-axis in radians) in the range [0..PI]. 
     * </pre>
     * 
     * @param spherical The spherical coordinates.
     * 
     * @return The cartesian coordinates.
     */
    static Vec3D SphericalToCartesian(const Vec3D& spherical);
    
    /*!
     * @brief  Converts the given spherical coordinates into cartesian coordinates.
     * 
     * The components of the given vector have the following semantic:
     * <pre>
     *     spherical.X := radius (distance to origin).
     *     spherical.Y := azimuthal angle (angle from positive X-axis in radians) in the range [-PI..PI].
     *     spherical.Z := polar angle (angle from positive Z-axis in radians) in the range [0..PI]. 
     * </pre>
     * 
     * @param x The spherical X-coordinate.
     * @param y The spherical Y-coordinate.
     * @param z The spherical Z-coordinate.
     * 
     * @return The cartesian coordinates.
     */
    static Vec3D SphericalToCartesian(float64 x, float64 y, float64 z);
    
    /*!
     * @brief  Returns the square of the given number.
     * 
     * @param number The number.
     * 
     * @return The square value.
     */
    static float64 SqrD(float64 number);
    
    /*!
     * @brief  Returns the square of the given number.
     * 
     * @param number The number.
     * 
     * @return The square value.
     */
    static float32 SqrF(float32 number);
    
    /*!
     * @brief  Returns the square root of a specified number.
     * 
     * @param number A number.
     * 
     * @return The positive square root of \e number .
     */
    static float64 SqrtD(float64 number);
    
    /*!
     * @brief  Returns the square root of a specified number.
     * 
     * @param number A number.
     * 
     * @return The positive square root of \e number .
     */
    static float32 SqrtF(float32 number);
    
    /*!
     * @brief  Computes the integer square root of the given value.
     * 
     * The integer square root is defined as <c>floor(sqrt(v))</c>.
     * 
     * @param value The input value.
     * 
     * @return The integer square root of \e value .
     */
    static int32 SqrtI(int32 value);
    
    /*!
     * @brief  Computes the integer square root of the given value.
     * 
     * The integer square root is defined as <c>floor(sqrt(v))</c>.
     * 
     * @param value The input value.
     * 
     * @return The integer square root of \e value .
     */
    static int64 SqrtL(int64 value);
    
    /*!
     * @brief  Returns the tangent of the specified angle.
     * 
     * @param radians An angle,measured in radians.
     * 
     * @return The tangent of \e radians .
     */
    static float64 Tan(float64 radians);
    
    /*!
     * @brief  Computes the hyperbolic tangent of the given value.
     * 
     * @param v The value.
     * 
     * @return The hyperbolic tangent of \e v .
     */
    static float64 Tanh(float64 v);
    
    /*!
     * @brief  Converts the given angle value from radians to degrees.
     * 
     * @param radians The angle value in radians.
     * 
     * @return The angle value in degrees.
     */
    static float64 ToDegreesD(float64 radians);
    
    /*!
     * @brief  Converts the given angle value from radians to degrees.
     * 
     * @param radians The angle value in radians.
     * 
     * @return The angle value in degrees.
     */
    static float32 ToDegreesF(float32 radians);
    
    /*!
     * @brief  Converts the given angle value from degrees to radians.
     * 
     * @param degrees The angle value in degrees.
     * 
     * @return The angle value in radians.
     */
    static float64 ToRadiansD(float64 degrees);
    
    /*!
     * @brief  Converts the given angle value from degrees to radians.
     * 
     * @param degrees The angle value in degrees.
     * 
     * @return The angle value in radians.
     */
    static float32 ToRadiansF(float32 degrees);
    
    /*!
     * @brief  Mixes the first and second value using an Uniform-B spline.
     * 
     * @param a Zeroth double value.
     * @param b First double value.
     * @param c Second double value.
     * @param d Third double value.
     * @param f Mix factor.
     * 
     * @return The mixed value.
     */
    static float64 UniformB_D(float64 a, float64 b, float64 c, float64 d, float64 f);
    
    /*!
     * @brief  Mixes the first and second value using an Uniform-B spline.
     * 
     * @param a Zeroth float value.
     * @param b First float value.
     * @param c Second float value.
     * @param d Third float value.
     * @param f Mix factor.
     * 
     * @return The mixed value.
     */
    static float32 UniformB_F(float32 a, float32 b, float32 c, float32 d, float32 f);
    
    /*!
     * @brief  Unpacks the given 32-bit floating-point value to three 8-bit integer values.
     * 
     * @param v The packed floating-point value.
     * 
     * @return The unpacked integer values.
     * 
     * @see #Pack(int32,int32,int32)
     */
    static Vec3I Unpack3(float32 v);
    
    /*!
     * @brief  Unpacks the given 32-bit floating-point value to four 6-bit integer values.
     * 
     * @param v The packed floating-point value.
     * 
     * @return The unpacked integer values.
     * 
     * @see #Pack(int32,int32,int32,int32)
     */
    static Vec4I Unpack4(float32 v);
    
    /*!
     * @brief  Performs an unsigned 64-bit integer division.
     * 
     * @param dividend The dividend.
     * @param divisor The divisor.
     * 
     * @return <b>[>=0]</b>  The quotient.
     */
    static int64 UnsignedDivide(int64 dividend, int64 divisor);
  };
  
} } } 

#endif
