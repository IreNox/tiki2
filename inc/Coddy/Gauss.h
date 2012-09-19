////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_MATH_GAUSS_H
#define CLODDY_CORE_MATH_GAUSS_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class IStructSerializer; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Math { class Gauss_Serializer; } } }

// Declare class ::Cloddy::Core::Math::Gauss.

namespace Cloddy { namespace Core { namespace Math
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::IStructSerializer;
  
  /*!
   * @brief  Helper class for computing samples along a Gaussian distribution curve.
   */
  struct Gauss : StructType
  {
    // Declare friend classes.
    
    friend class Gauss_Serializer;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The serialization helper object for values of Gauss.
     */
    static const StaticPtr<IStructSerializer<Val<Gauss> > > Serializer;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Gauss.
     * 
     * @param expected The expected value.
     * @param deviation <b>[>0]</b>  The mean deviation.
     */
    Gauss(float64 expected, float64 deviation);
    
    /*!
     * @brief  Creates a new instance of Gauss.
     * 
     * @param expected The expected value.
     * @param deviation <b>[>0]</b>  The mean deviation.
     * @param maximum The value to return at x:=\e expected .
     */
    Gauss(float64 expected, float64 deviation, float64 maximum);
    
    Gauss();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Evaluates the Gaussian curve at the given X-coordinate.
     * 
     * @param x The X-coordinate.
     * 
     * @return The resulting Y-coordinate.
     */
    float64 Compute(float64 x) const;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The expected value.
     */
    float64 expected;
    
    /*!
     * @brief  Reciprocal mean deviation.
     */
    float64 rDeviation;
    
    /*!
     * @brief  Final exponent scale factor.
     */
    float64 scale;
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    Gauss(const Gauss& other);
    
    Gauss& operator=(const Gauss& other);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field Serializer.
     */
    static Object* StaticInitializer_Serializer();
  };
  
} } } 

#endif
