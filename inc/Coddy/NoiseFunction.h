////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_NOISEFUNCTION_H
#define CLODDY_API_PROCEDURAL_NOISEFUNCTION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/INoiseFunction.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced structures.

namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Mat3D; } } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Mat4D; } } } }
namespace Cloddy { namespace Core { namespace Math { namespace Vectors { struct Vec3D; } } } }

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Procedural { class ICellularCombiner; } } }
namespace Cloddy { namespace API { namespace Util { namespace Curves { class ICurve; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerializable; } } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Cellular1; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Constant; } } }
namespace Cloddy { namespace API { namespace Procedural { class NoiseFunction_Perlin; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare class ::Cloddy::API::Procedural::NoiseFunction.

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
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerializableBase;
  using Cloddy::Core::IO::Serialization::Serializer;
  
  /*!
   * @brief  Base class for noise functions.
   * 
   * A noise function computes a pseudo-random scalar value for a given 3D input vector,where same 
   * input vectors will result in the same scalar value being computed.
   * 
   * <b>Perlin Noise</b> 
   * 
   * A gradient-based noise function that produces smooth noise values.
   * 
   * <b>Cellular Noise</b> 
   * 
   * <b>Multifractal Noise</b> 
   * 
   *   -  \b Octaves 
   *   -  \b Amplitude 
   *   The amplitude is the factor by which the noise value resulting from consecutive evaluations 
   *   of the inner noise function is scaled.
   *   The noise value produced by the evaluation of the inner noise function is scaled by a power 
   *   of the amplitude value:
   *   <pre>
   *             .   Octave | Factor
   *             .   -------+--------------
   *             .        0 | amplitude^0
   *             .        1 | amplitude^1
   *             .        2 | amplitude^2
   *             .      ... | ...
   *             .        n | amplitude^n
   *   </pre>
   *   
   *   A good default value is <c>0.5</c>.
   *   -  \b Frequency 
   *   The frequency is the factor by which the input coordinates are scaled between consecutive 
   *   evaluations of the inner noise function.
   *   The input \c X ,\c Y  and \c Z  coordinates provided for this noise function are scaled by a 
   *   power of the frequency for each evaluation of the inner noise function:
   *   <pre>
   *             .   Octave | Factor
   *             .   -------+--------------
   *             .        0 | frequency^0
   *             .        1 | frequency^1
   *             .        2 | frequency^2
   *             .      ... | ...
   *             .        n | frequency^n  
   *   </pre>
   *   
   *   The good default value is <c>2.0</c>.
   *   - \b Offset 
   *   - \b Gain 
   */
  class NoiseFunction : public SerializableBase, public virtual INoiseFunction
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  A noise function that computes distance based cellular noise of order one.
     */
    static const StaticPtr<INoiseFunction> Cellular1;
    
    /*!
     * @brief  A noise function that always returns <c>1.0</c>.
     */
    static const StaticPtr<INoiseFunction> One;
    
    /*!
     * @brief  A noise function that computes perlin noise.
     */
    static const StaticPtr<INoiseFunction> Perlin;
    
    /*!
     * @brief  A noise function that always returns <c>0.0</c>.
     */
    static const StaticPtr<INoiseFunction> Zero;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a noise function that computes cellular noise values using the given 
     *         combiner function for the F1 and F2 distance values.
     * 
     * @param combiner <b>[not-null]</b>  The combiner function to use.
     * 
     * @return <b>[not-null]</b>  The noise function.
     */
    static Ptr<INoiseFunction> Cellular2(ICellularCombiner* combiner);
    
    /*!
     * @brief  Creates a noise function that computes cellular noise values using the given 
     *         combiner function for the F1,F2 and F3 distance values.
     * 
     * @param combiner <b>[not-null]</b>  The combiner function to use.
     * 
     * @return <b>[not-null]</b>  The noise function.
     */
    static Ptr<INoiseFunction> Cellular3(ICellularCombiner* combiner);
    
    /*!
     * @brief  Creates a noise function that computes cellular noise values using the given 
     *         combiner function for the F1,F2,F3 and F4 distance values.
     * 
     * @param combiner <b>[not-null]</b>  The combiner function to use.
     * 
     * @return <b>[not-null]</b>  The noise function.
     */
    static Ptr<INoiseFunction> Cellular4(ICellularCombiner* combiner);
    
    /*!
     * @brief  Returns a noise function that returns a constant value.
     * 
     * @param value The constant value.
     * 
     * @return <b>[not-null]</b>  The noise function.
     */
    static Ptr<INoiseFunction> Constant(float64 value);
    
    virtual Ptr<INoiseFunction> Abs();
    
    virtual Ptr<INoiseFunction> Add(float64 value);
    
    virtual Ptr<INoiseFunction> Add(INoiseFunction* function);
    
    virtual Ptr<INoiseFunction> Atan();
    
    virtual Ptr<INoiseFunction> Blend(INoiseFunction* second, INoiseFunction* factor, float64 from, float64 to);
    
    virtual Ptr<INoiseFunction> Clamp(float64 min, float64 max);
    
    virtual float64 Compute(const Vec3D& v);
    
    virtual float64 Compute(float64 x, float64 y, float64 z) = 0;
    
    virtual Ptr<INoiseFunction> Cos();
    
    virtual Ptr<INoiseFunction> Curve(ICurve* curve, float64 min, float64 max);
    
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data);
    
    virtual Ptr<INoiseFunction> Div(float64 divisor);
    
    virtual Ptr<INoiseFunction> Div(INoiseFunction* divisor);
    
    virtual Ptr<INoiseFunction> DivInv(float64 dividend);
    
    virtual Ptr<INoiseFunction> Log(float64 basis);
    
    virtual Ptr<INoiseFunction> Log(INoiseFunction* basis);
    
    virtual Ptr<INoiseFunction> LogInv(float64 value);
    
    virtual Ptr<INoiseFunction> Max(float64 value);
    
    virtual Ptr<INoiseFunction> Max(INoiseFunction* function);
    
    virtual Ptr<INoiseFunction> Min(float64 value);
    
    virtual Ptr<INoiseFunction> Min(INoiseFunction* function);
    
    virtual Ptr<INoiseFunction> Mul(float64 factor);
    
    virtual Ptr<INoiseFunction> Mul(INoiseFunction* factor);
    
    virtual Ptr<INoiseFunction> MultiAbs(int32 octaves, float64 amplitude, float64 frequency);
    
    virtual Ptr<INoiseFunction> MultiMul(int32 octaves, float64 amplitude, float64 frequency, float64 offset);
    
    virtual Ptr<INoiseFunction> MultiRidged(int32 octaves, float64 amplitude, float64 frequency, float64 offset, float64 gain);
    
    virtual Ptr<INoiseFunction> MultiSum(int32 octaves, float64 amplitude, float64 frequency);
    
    virtual Ptr<INoiseFunction> NaN(float64 nan, float64 neg, float64 pos);
    
    virtual Ptr<INoiseFunction> Neg();
    
    virtual Ptr<INoiseFunction> Perturb(INoiseFunction* function, float64 scale);
    
    virtual Ptr<INoiseFunction> Pow(float64 power);
    
    virtual Ptr<INoiseFunction> Pow(INoiseFunction* power);
    
    virtual Ptr<INoiseFunction> PowInv(float64 value);
    
    virtual void Serialize(Serializer* data);
    
    virtual Ptr<INoiseFunction> Shift(const Vec3D& shift);
    
    virtual Ptr<INoiseFunction> Shift(int32 seed, float64 scale);
    
    virtual Ptr<INoiseFunction> Shift(float64 x, float64 y, float64 z);
    
    virtual Ptr<INoiseFunction> Shift(int32 seed);
    
    virtual Ptr<INoiseFunction> Sin();
    
    virtual Ptr<INoiseFunction> Sqr();
    
    virtual Ptr<INoiseFunction> Sqrt();
    
    virtual Ptr<INoiseFunction> Sub(float64 value);
    
    virtual Ptr<INoiseFunction> Sub(INoiseFunction* function);
    
    virtual Ptr<INoiseFunction> SubInv(float64 value);
    
    virtual Ptr<INoiseFunction> Tan();
    
    virtual Ptr<INoiseFunction> Transform(const Mat3D& matrix);
    
    virtual Ptr<INoiseFunction> Transform(const Mat4D& matrix);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of NoiseFunction.
     * 
     * @param serialType <b>[not-null]</b>  The serial ID.
     */
    NoiseFunction(ISerialTypeInfo* serialType);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field Cellular1.
     */
    static Object* StaticInitializer_Cellular1();
    
    /*!
     * @brief Static initializer function for field One.
     */
    static Object* StaticInitializer_One();
    
    /*!
     * @brief Static initializer function for field Perlin.
     */
    static Object* StaticInitializer_Perlin();
    
    /*!
     * @brief Static initializer function for field Zero.
     */
    static Object* StaticInitializer_Zero();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<NoiseFunction> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCE8E8AD1;
    
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
      if ((ptr = SerializableBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = INoiseFunction::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
