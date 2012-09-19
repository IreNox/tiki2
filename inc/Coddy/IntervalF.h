////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_INTERVALF_H
#define CLODDY_CORE_MATH_INTERVALF_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::IntervalF.

namespace Cloddy { namespace Core { namespace Math
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A closed number interval with 32-bit floating-point precision.
   */
  struct IntervalF : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Start of number interval (inclusive).
     */
    float32 From;
    
    /*!
     * @brief  Is this number interval empty?
     * 
     * @return \c true  if this interval is empty,\c false  if it is not.
     */
    bool IsEmpty() const;
    
    /*!
     * @brief  Length of this number interval.
     * 
     * @return The interval length.
     */
    float32 GetLength() const;
    
    /*!
     * @brief  End of number interval (inclusive).
     */
    float32 To;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of IntervalF.
     * 
     * @param from Start of number interval (inclusive).
     * @param to End of number interval (inclusive).
     */
    IntervalF(float32 from, float32 to);
    
    IntervalF();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Clamps the given value to <c>[From..To]</c>.
     * 
     * @param value The value to clamp.
     * 
     * @return The clamped value.
     */
    float32 Clamp(float32 value) const;
    
    /*!
     * @brief  Returns if this interval contains the given value.
     * 
     * @param value The value.
     * 
     * @return \c true  if \e value  lies within this interval,\c false  if it does not.
     */
    bool Contains(float32 value) const;
    
    /*!
     * @brief  Returns if this interval contains the given interval.
     * 
     * @param interval The interval.
     * 
     * @return \c true  if \e interval  lies completely within this interval,\c false  if it does 
     * not.
     */
    bool Contains(const IntervalF& interval) const;
    
    /*!
     * @brief  Denormalizes the given value from <c>[0..1]</c> to <c>[From..To]</c>.
     * 
     * @param value The normalized value.
     * 
     * @return The interval value.
     */
    float32 Denormalize(float32 value) const;
    
    /*!
     * @brief  Computes the intersection between this number interval and the given one.
     * 
     * @param interval The interval.
     * 
     * @return The resulting interval.
     */
    IntervalF Intersection(const IntervalF& interval) const;
    
    /*!
     * @brief  Returns if this interval intersects with the given one.
     * 
     * @param interval The interval.
     * 
     * @return \c true  if this interval and the given one intersect,\c false  if not.
     */
    bool Intersects(const IntervalF& interval) const;
    
    /*!
     * @brief  Normalizes the given value from <c>[From..To]</c>to <c>[0..1]</c>.
     * 
     * @param value The interval value.
     * 
     * @return The normalized value.
     */
    float32 Normalize(float32 value) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    IntervalF(const IntervalF& other);
    
    IntervalF& operator=(const IntervalF& other);
  };
  
} } } 

#endif
