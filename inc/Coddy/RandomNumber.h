////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_SYSTEM_RANDOMNUMBER_H
#define CLODDY_CORE_SYSTEM_RANDOMNUMBER_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::System::RandomNumber.

namespace Cloddy { namespace Core { namespace System
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A generator for pseudo random numbers.
   */
  class RandomNumber : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of RandomNumber.
     * 
     * @param seed The random number seed value to use.
     */
    RandomNumber(int32 seed);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a random boolean value.
     * 
     * @return The random value.
     */
    bool Bool();
    
    /*!
     * @brief  Returns a random 32-bit floating-point number in the range <c>[0..1]</c>.
     * 
     * @return <b>[0..1]</b>  The random number.
     */
    float32 Float32();
    
    /*!
     * @brief  Returns a random 32-bit floating-point number in the given range.
     * 
     * @param min Lower bound of range.
     * @param max Upper bound of range.
     * 
     * @return <b>[0..1]</b>  The random number.
     */
    float32 Float32(float32 min, float32 max);
    
    /*!
     * @brief  Returns a random 64-bit floating-point number in the range <c>[0..1]</c>.
     * 
     * @return <b>[0..1]</b>  The random number.
     */
    float64 Float64();
    
    /*!
     * @brief  Returns a random 64-bit floating-point number in the given range.
     * 
     * @param min Lower bound of range.
     * @param max Upper bound of range.
     * 
     * @return <b>[0..1]</b>  The random number.
     */
    float64 Float64(float64 min, float64 max);
    
    /*!
     * @brief  Returns a random 32-bit integer positive number.
     * 
     * @return <b>[>=0]</b>  The random number.
     */
    int32 Int32();
    
    /*!
     * @brief  Returns a random 32-bit integer number in the given range.
     * 
     * @param min The minimum value,inclusive.
     * @param max The maximum value,inclusive.
     * 
     * @return <b>[>=0]</b>  The random number.
     */
    int32 Int32(int32 min, int32 max);
    
    /*!
     * @brief  Returns a random 64-bit integer positive number.
     * 
     * @return <b>[>=0]</b>  The random number.
     */
    int64 Int64();
    
    /*!
     * @brief  Returns a random 32-bit integer number in the given range.
     * 
     * @param min The minimum value,inclusive.
     * @param max The maximum value,inclusive.
     * 
     * @return <b>[>=0]</b>  The random number.
     */
    int64 Int64(int64 min, int64 max);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The random number buffer.
     */
    Array<int32> buffer;
    
    /*!
     * @brief  Current buffer index.
     */
    int32 bufferIndex;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Generates a 32-bit random number.
     * 
     * @return The random number.
     */
    int32 Generate();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<RandomNumber> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5B344378;
    
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
      return (void*) 0;
    }
  };
  
} } } 

#endif
