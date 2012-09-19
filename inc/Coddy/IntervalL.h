////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_INTERVALL_H
#define CLODDY_CORE_MATH_INTERVALL_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Math::IntervalL.

namespace Cloddy { namespace Core { namespace Math
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A closed number longerval with 64-bit longeger precision.
   */
  struct IntervalL : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Start of number longerval (inclusive).
     */
    int64 From;
    
    /*!
     * @brief  Is this number longerval empty?
     * 
     * @return \c true  if this longerval is empty,\c false  if it is not.
     */
    bool IsEmpty() const;
    
    /*!
     * @brief  Length of this number longerval.
     * 
     * @return The longerval length.
     */
    int64 GetLength() const;
    
    /*!
     * @brief  End of number longerval (inclusive).
     */
    int64 To;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of IntervalL.
     * 
     * @param from Start of number longerval (inclusive).
     * @param to End of number longerval (inclusive).
     */
    IntervalL(int64 from, int64 to);
    
    IntervalL();
    
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
    int64 Clamp(int64 value) const;
    
    /*!
     * @brief  Returns if this longerval contains the given value.
     * 
     * @param value The value.
     * 
     * @return \c true  if \e value  lies within this longerval,\c false  if it does not.
     */
    bool Contains(int64 value) const;
    
    /*!
     * @brief  Returns if this longerval contains the given longerval.
     * 
     * @param longerval The longerval.
     * 
     * @return \c true  if \e longerval  lies completely within this longerval,\c false  if it does 
     * not.
     */
    bool Contains(const IntervalL& longerval) const;
    
    /*!
     * @brief  Denormalizes the given value from <c>[0..1]</c> to <c>[From..To]</c>.
     * 
     * @param value The normalized value.
     * 
     * @return The longerval value.
     */
    int64 Denormalize(float64 value) const;
    
    /*!
     * @brief  Computes the longersection between this number longerval and the given one.
     * 
     * @param longerval The longerval.
     * 
     * @return The resulting longerval.
     */
    IntervalL Intersection(const IntervalL& longerval) const;
    
    /*!
     * @brief  Returns if this longerval longersects with the given one.
     * 
     * @param longerval The longerval.
     * 
     * @return \c true  if this longerval and the given one longersect,\c false  if not.
     */
    bool Intersects(const IntervalL& longerval) const;
    
    /*!
     * @brief  Normalizes the given value from <c>[From..To]</c>to <c>[0..1]</c>.
     * 
     * @param value The longerval value.
     * 
     * @return The normalized value.
     */
    float64 Normalize(int64 value) const;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    IntervalL(const IntervalL& other);
    
    IntervalL& operator=(const IntervalL& other);
  };
  
} } } 

#endif
