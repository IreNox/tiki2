////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_FRACTION_H
#define CLODDY_CORE_MATH_FRACTION_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Math { class Fraction_Serializer; } } }

// Declare class ::Cloddy::Core::Math::Fraction.

namespace Cloddy { namespace Core { namespace Math
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  /*!
   * @brief  This struct represents a fraction with 32-bit integer numerator and denominator.
   */
  struct Fraction : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The fraction <c>1 /1</c>.
     */
    static const Fraction One;
    
    /*!
     * @brief  The fraction <c>1 /2</c>.
     */
    static const Fraction OneHalf;
    
    /*!
     * @brief  The fraction <c>1 /100</c>.
     */
    static const Fraction OnePercent;
    
    /*!
     * @brief  The fraction <c>1 /4</c>.
     */
    static const Fraction OneQuarter;
    
    /*!
     * @brief  The serialization helper object for values of Fraction.
     */
    static const StaticPtr<IStructSerializer<Val<Fraction> > > Serializer;
    
    /*!
     * @brief  The fraction <c>0 /1</c>.
     */
    static const Fraction Zero;
    
    /*!
     * @brief  The denominator of the fraction.
     */
    int32 Denominator;
    
    /*!
     * @brief  Does this fraction have the value \c 1 ?
     * 
     * @return \c true  if this fraction is equal to one,\c false  if it is not.
     */
    bool IsOne() const;
    
    /*!
     * @brief  Does this fraction have the value \c 0 ?
     * 
     * @return \c true  if this fraction is equal to zero,\c false  if it is not.
     */
    bool IsZero() const;
    
    /*!
     * @brief  The numerator of the fraction.
     */
    int32 Numerator;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Fraction.
     * 
     * The denominator will be set to \c 1 .
     * 
     * @param numerator The numerator of the fraction.
     */
    Fraction(int32 numerator);
    
    /*!
     * @brief  Creates a new instance of Fraction.
     * 
     * @param numerator The numerator of the fraction.
     * @param denominator The denominator of the fraction.
     */
    Fraction(int32 numerator, int32 denominator);
    
    Fraction();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a Fraction value that represents the given floating point value.
     * 
     * @param value The floating point value.
     * 
     * @return The fraction value.
     */
    static Fraction FromD(float64 value);
    
    /*!
     * @brief  Returns a Fraction value that represents the given floating point value.
     * 
     * @param value The floating point value.
     * 
     * @return The fraction value.
     */
    static Fraction FromF(float32 value);
    
    /*!
     * @brief  Returns a Fraction value that represents the given 64-bit integer fraction.
     * 
     * @param numerator The 64-bit integer numerator.
     * @param denominator The 64-bit integer denominator.
     * 
     * @return The resulting fraction.
     */
    static Fraction FromL(int64 numerator, int64 denominator);
    
    /*!
     * @brief  Adds the given value to this fraction.
     * 
     * @param value The value.
     * 
     * @return The resulting fraction.
     */
    Fraction Add(int32 value) const;
    
    /*!
     * @brief  Adds the given fraction to this fraction.
     * 
     * @param fraction The fraction.
     * 
     * @return The resulting fraction.
     */
    Fraction Add(const Fraction& fraction) const;
    
    /*!
     * @brief  Divides this fraction by the given scalar value.
     * 
     * @param value The scale value.
     * 
     * @return The resulting fraction.
     */
    Fraction Div(int32 value) const;
    
    /*!
     * @brief  Divides this fraction by the given fraction.
     * 
     * @param fraction The fraction.
     * 
     * @return The resulting fraction.
     */
    Fraction Div(const Fraction& fraction) const;
    
    /*!
     * @brief  Divides the given value by this fraction.
     * 
     * @param value The value.
     * 
     * @return The result.
     */
    int32 DivByThis(int32 value) const;
    
    /*!
     * @brief  Multiplies this fraction with the given scalar value.
     * 
     * @param value The scale value.
     * 
     * @return The resulting fraction.
     */
    Fraction Mul(int32 value) const;
    
    /*!
     * @brief  Multiplies this fraction with the given fraction.
     * 
     * @param fraction The fraction.
     * 
     * @return The resulting fraction.
     */
    Fraction Mul(const Fraction& fraction) const;
    
    /*!
     * @brief  Multiplies the given value with this fraction.
     * 
     * @param value The value.
     * 
     * @return The result.
     */
    int32 MulByThis(int32 value) const;
    
    /*!
     * @brief  Negates this fraction.
     * 
     * @return The resulting fraction.
     */
    Fraction Neg() const;
    
    /*!
     * @brief  Returns the reciprocal value of this fraction.
     * 
     * @return The resulting fraction.
     */
    Fraction Reciprocal() const;
    
    /*!
     * @brief  Subtracts the given value from this fraction.
     * 
     * @param value The value.
     * 
     * @return The resulting fraction.
     */
    Fraction Sub(int32 value) const;
    
    /*!
     * @brief  Subtracts the given fraction from this fraction.
     * 
     * @param fraction The fraction.
     * 
     * @return The resulting fraction.
     */
    Fraction Sub(const Fraction& fraction) const;
    
    /*!
     * @brief  Converts this fraction into a 64-bit floating point value.
     * 
     * @return The floating point value.
     */
    float64 ToD() const;
    
    /*!
     * @brief  Converts this fraction into a 32-bit floating point value.
     * 
     * @return The floating point value.
     */
    float32 ToF() const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Fraction(const Fraction& other);
    
    Fraction& operator=(const Fraction& other);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field Serializer.
     */
    static Object* StaticInitializer_Serializer();
  };
  
} } } 

#endif
