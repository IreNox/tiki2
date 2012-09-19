////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_INOISEFUNCTION_H
#define CLODDY_API_PROCEDURAL_INOISEFUNCTION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Mat3D; } } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Mat4D; } } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3D; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { namespace Curves { class ICurve; } } } }

// Declare interface ::Cloddy::API::Procedural::INoiseFunction.

namespace Cloddy { namespace API { namespace Procedural
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced structures.
  
  using Cloddy::Core::Math::Vectors::Mat3D;
  using Cloddy::Core::Math::Vectors::Mat4D;
  using Cloddy::Core::Math::Vectors::Vec3D;
  
  // Use referenced interfaces.
  
  using Cloddy::API::Util::Curves::ICurve;
  using Cloddy::Core::IO::Serialization::ISerializable;
  
  /*!
   * @brief  Represents a noise function that maps a scalar noise value to a three-dimensional 
   *         input vector.
   */
  class NO_VTABLE INoiseFunction : public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns a noise function that returns the absolute value of this function.
     * 
     * <pre>
     * result := | this |
     * </pre>
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Abs() = 0;
    
    /*!
     * @brief  Returns a noise function that adds the given scalar value to the noise values 
     *         returned by this function.
     * 
     * <pre>
     * result := this + value
     * </pre>
     * 
     * @param value The absolute value to add.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Add(float64 value) = 0;
    
    /*!
     * @brief  Returns a noise function that sums the noise values of the given function and this 
     *         one.
     * 
     * <pre>
     * result := this + function
     * </pre>
     * 
     * @param function <b>[not-null]</b>  The noise function to add.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Add(INoiseFunction* function) = 0;
    
    /*!
     * @brief  Returns a noise function that computes the arcus tangens of the noise values 
     *         returned by this noise function.
     * 
     * <pre>
     * result := atan(this)
     * </pre>
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Atan() = 0;
    
    /*!
     * @brief  Returns a noise function that blends between this noise function and the given one 
     *         using a third blend factor noise function.
     * 
     * @param second <b>[not-null]</b>  The noise function to blend with.
     * @param factor <b>[not-null]</b>  The blend factor noise function.
     * @param from Start of blend interval.
     * @param to End of blend interval.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Blend(INoiseFunction* second, INoiseFunction* factor, float64 from, float64 to) = 0;
    
    /*!
     * @brief  Returns a noise function that clamps the noise values returned by this function to 
     *         the specified number range.
     * 
     * @param min Minimum noise value to return.
     * @param max Maximum noise value to return.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Clamp(float64 min, float64 max) = 0;
    
    /*!
     * @brief  Computes the noise value for the given input vector.
     * 
     * @param v The input vector.
     * 
     * @return The noise value.
     */
    virtual float64 Compute(const Vec3D& v) = 0;
    
    /*!
     * @brief  Computes the noise value for the given input vector.
     * 
     * @param x X-coordinate of input vector.
     * @param y Y-coordinate of input vector.
     * @param z Z-coordinate of input vector.
     * 
     * @return The noise value.
     */
    virtual float64 Compute(float64 x, float64 y, float64 z) = 0;
    
    /*!
     * @brief  Returns a noise function that computes the cosine of the noise values returned by 
     *         this noise function.
     * 
     * <pre>
     * result := cos(this)
     * </pre>
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Cos() = 0;
    
    /*!
     * @brief  Returns a noise function that maps the noise values returned by this noise function 
     *         onto the given curve.
     * 
     * The given curve is assumed to be 1D,so only the CurveSample::PositionX coordinate is used.
     * 
     * @param curve <b>[not-null]</b>  The curve.
     * @param min The noise value to map to the first curve control point.
     * @param max The noise value to map to the last curve control point.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Curve(ICurve* curve, float64 min, float64 max) = 0;
    
    /*!
     * @brief  Returns a noise function that divides the noise values returned by this function by 
     *         the given scalar value.
     * 
     * <pre>
     * result := this / divisor
     * </pre>
     * 
     * @param divisor The scalar divisor value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Div(float64 divisor) = 0;
    
    /*!
     * @brief  Returns a noise function that divides the noise values returned by this function by 
     *         the noise values returned by the given noise function.
     * 
     * <pre>
     * result := this / divisor
     * </pre>
     * 
     * @param divisor <b>[not-null]</b>  The divisor noise function.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Div(INoiseFunction* divisor) = 0;
    
    /*!
     * @brief  Returns a noise function that divides the given scalar value by the noise values 
     *         returned by this noise function.
     * 
     * <pre>
     * result := dividend / this
     * </pre>
     * 
     * @param dividend The scalar dividend value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> DivInv(float64 dividend) = 0;
    
    /*!
     * @brief  Returns a noise function that computes the logarithm of the noise values returned by 
     *         this noise function using the given basis value.
     * 
     * <pre>
     * result := log(this, basis)
     * </pre>
     * 
     * @param basis The logarithm basis value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Log(float64 basis) = 0;
    
    /*!
     * @brief  Returns a noise function that computes the logarithm of the noise values returned by 
     *         this noise function,using the noise values from the given function as the basis.
     * 
     * <pre>
     * result := log(this, basis)
     * </pre>
     * 
     * @param basis <b>[not-null]</b>  The logarithm basis values.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Log(INoiseFunction* basis) = 0;
    
    /*!
     * @brief  Returns a noise function that computes the logarithm of the given scalar value using 
     *         the noise values returned by this noise function as the logarithm basis.
     * 
     * <pre>
     * result := log(value, this)
     * </pre>
     * 
     * @param value The scalar value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> LogInv(float64 value) = 0;
    
    /*!
     * @brief  Returns a noise function that returns the maximum of the given scalar value and the 
     *         noise values returned by this noise function.
     * 
     * <pre>
     * result := max(this, value)
     * </pre>
     * 
     * @param value The scalar maximum value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Max(float64 value) = 0;
    
    /*!
     * @brief  Returns a noise function that returns the maximum of the noise values returned by 
     *         this noise function and the noise values returned by the given noise function.
     * 
     * <pre>
     * result := max(this, function)
     * </pre>
     * 
     * @param function <b>[not-null]</b>  The noise function.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Max(INoiseFunction* function) = 0;
    
    /*!
     * @brief  Returns a noise function that returns the minimum of the given scalar value and the 
     *         noise values returned by this noise function.
     * 
     * <pre>
     * result := min(this, value)
     * </pre>
     * 
     * @param value The scalar minimum value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Min(float64 value) = 0;
    
    /*!
     * @brief  Returns a noise function that returns the minimum of the noise values returned by 
     *         this noise function and the noise values returned by the given noise function.
     * 
     * <pre>
     * result := min(this, function)
     * </pre>
     * 
     * @param function <b>[not-null]</b>  The noise function.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Min(INoiseFunction* function) = 0;
    
    /*!
     * @brief  Returns a noise function that multiplies the noise values returned by this noise 
     *         function with the given scalar value.
     * 
     * <pre>
     * result := this * factor
     * </pre>
     * 
     * @param factor The scalar value to multiply with.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Mul(float64 factor) = 0;
    
    /*!
     * @brief  Returns a noise function that multiplies the noise values returned by this noise 
     *         function with the noise values returned by the given noise function.
     * 
     * <pre>
     * result := this * factor
     * </pre>
     * 
     * @param factor <b>[not-null]</b>  The noise function.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Mul(INoiseFunction* factor) = 0;
    
    /*!
     * @brief  Returns a multifractal noise function based on this noise function.
     * 
     * @param octaves <b>[>=1]</b>  The number of octaves.
     * @param amplitude The initial amplitude.
     * @param frequency The initial frequency.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> MultiAbs(int32 octaves, float64 amplitude, float64 frequency) = 0;
    
    /*!
     * @brief  Returns a multifractal noise function based on this noise function.
     * 
     * @param octaves <b>[>=1]</b>  The number of octaves.
     * @param amplitude The initial amplitude.
     * @param frequency The initial frequency.
     * @param offset Offset to add to noise value after each octave.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> MultiMul(int32 octaves, float64 amplitude, float64 frequency, float64 offset) = 0;
    
    /*!
     * @brief  Returns a multifractal noise function based on this noise function.
     * 
     * @param octaves <b>[>=1]</b>  The number of octaves.
     * @param amplitude The initial amplitude.
     * @param frequency The initial frequency.
     * @param offset The offset value.
     * @param gain The gain value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> MultiRidged(int32 octaves, float64 amplitude, float64 frequency, float64 offset, float64 gain) = 0;
    
    /*!
     * @brief  Returns a multifractal noise function based on this noise function.
     * 
     * @param octaves <b>[>=1]</b>  The number of octaves.
     * @param amplitude The initial amplitude.
     * @param frequency The initial frequency.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> MultiSum(int32 octaves, float64 amplitude, float64 frequency) = 0;
    
    /*!
     * @brief  Returns a noise function that replaces bad number values produced by this noise 
     *         function with the given values.
     * 
     * @param nan The replacement value for NaN (not-a-number).
     * @param neg The replacement value for negative infinity.
     * @param pos The replacement value for positive infinity.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> NaN(float64 nan, float64 neg, float64 pos) = 0;
    
    /*!
     * @brief  Returns a noise function that negates the values returned by this noise function.
     * 
     * <pre>
     * result := -this
     * </pre>
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Neg() = 0;
    
    /*!
     * @brief  Returns a noise function that perturbs the input vector using the given noise 
     *         function before plugging it into this noise function.
     * 
     * <pre>
     * result(V) := this(perturb(V, function, scale))
     * </pre>
     * 
     * @param function <b>[not-null]</b>  The noise function to use for perturbing the input vector.
     * @param scale The perturbation scale factor.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Perturb(INoiseFunction* function, float64 scale) = 0;
    
    /*!
     * @brief  Returns a noise function that raises the noise values returned by this noise 
     *         function to the given power.
     * 
     * <pre>
     * result := this ^ power
     * </pre>
     * 
     * @param power The scalar power value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Pow(float64 power) = 0;
    
    /*!
     * @brief  Returns a noise function that raises the noise values returned by this noise 
     *         function to the power values returned by the given noise function.
     * 
     * <pre>
     * result := this ^ power
     * </pre>
     * 
     * @param power <b>[not-null]</b>  The noise function.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Pow(INoiseFunction* power) = 0;
    
    /*!
     * @brief  Returns a noise function that raises the given scalar value to the power of the 
     *         noise values returned by this noise function.
     * 
     * <pre>
     * result := value ^ this
     * </pre>
     * 
     * @param value The scalar value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> PowInv(float64 value) = 0;
    
    /*!
     * @brief  Returns anoise function that shifts the input coordinates by the given amounts 
     *         before plugging them into this noise function.
     * 
     * @param shift Shift amount,in noise value space.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Shift(const Vec3D& shift) = 0;
    
    /*!
     * @brief  Returns anoise function that shifts the input coordinates by the given amounts 
     *         before plugging them into this noise function.
     * 
     * @param x Shift amount along X-axis,in noise value space.
     * @param y Shift amount along Y-axis,in noise value space.
     * @param z Shift amount along Z-axis,in noise value space.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Shift(float64 x, float64 y, float64 z) = 0;
    
    /*!
     * @brief  Returns anoise function that shifts the input coordinates by random amountsbefore 
     *         plugging them into this noise function.
     * 
     * @param seed Random seed value.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Shift(int32 seed) = 0;
    
    /*!
     * @brief  Returns anoise function that shifts the input coordinates by random amountsbefore 
     *         plugging them into this noise function.
     * 
     * @param seed Random seed value.
     * @param scale Shift scale,in noise space.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Shift(int32 seed, float64 scale) = 0;
    
    /*!
     * @brief  Returns a noise function that computes the sine of the noise values returned by this 
     *         noise function.
     * 
     * <pre>
     * result := sin(this)
     * </pre>
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Sin() = 0;
    
    /*!
     * @brief  Returns a noise function that computes the square value of the noise values returned 
     *         by this noise function.
     * 
     * <pre>
     * result := this ^ 2
     * </pre>
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Sqr() = 0;
    
    /*!
     * @brief  Returns a noise function that computes the square root of the noise values returned 
     *         by this noise function.
     * 
     * <pre>
     * result := this ^ 0.5
     * </pre>
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Sqrt() = 0;
    
    /*!
     * @brief  Returns a noise function that subtracts the given scalar value from the noise values 
     *         returned by this noise function.
     * 
     * <pre>
     * result := this - value
     * </pre>
     * 
     * @param value The scalar value to subtract.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Sub(float64 value) = 0;
    
    /*!
     * @brief  Returns a noise function that subtracts the noise values returned by the given noise 
     *         function from the noise values returned by this noise function.
     * 
     * @param function <b>[not-null]</b>  The noise function.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Sub(INoiseFunction* function) = 0;
    
    /*!
     * @brief  Returns a noise function that subtracts the noise values returned by this noise 
     *         function from the given scalar value.
     * 
     * <pre>
     * result := value - this
     * </pre>
     * 
     * @param value The scalar value to subtract from.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> SubInv(float64 value) = 0;
    
    /*!
     * @brief  Returns a noise function that computes the tangens of the noise values returned by 
     *         this noise function.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Tan() = 0;
    
    /*!
     * @brief  Returns a noise function that transforms the input vector using the given matrix 
     *         before evaluating this noise function.
     * 
     * <pre>
     * result(V) := this(matrix * V)
     * </pre>
     * 
     * @param matrix The transformation matrix.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Transform(const Mat3D& matrix) = 0;
    
    /*!
     * @brief  Returns a noise function that transforms the input vector using the given matrix 
     *         before evaluating this noise function.
     * 
     * <pre>
     * result(V) := this(matrix * V)
     * </pre>
     * 
     * @param matrix The transformation matrix.
     * 
     * @return <b>[not-null]</b>  The resulting noise function.
     */
    virtual Ptr<INoiseFunction> Transform(const Mat4D& matrix) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<INoiseFunction> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEEE5A3D8;
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    protected: virtual void* TryCast(int typeId)
    {
      if (typeId == TypeId) return (void*) this;
      void* ptr;
      if ((ptr = ISerializable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
