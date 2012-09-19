////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_CELLULARCOMBINER_H
#define CLODDY_API_PROCEDURAL_CELLULARCOMBINER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICellularCombiner.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Procedural { class CellularCombiner_F2; } } }
namespace Cloddy { namespace API { namespace Procedural { class CellularCombiner_F3; } } }
namespace Cloddy { namespace API { namespace Procedural { class CellularCombiner_F4; } } }

// Declare class ::Cloddy::API::Procedural::CellularCombiner.

namespace Cloddy { namespace API { namespace Procedural
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Serialization::SerializableBase;
  
  /*!
   * @brief  Abstract base class for combiner functions of cellular noise distance values.
   */
  class CellularCombiner : public SerializableBase, public virtual ICellularCombiner
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  A combiner function that returns the F2 distance value.
     */
    static const StaticPtr<ICellularCombiner> F2;
    
    /*!
     * @brief  A combiner function that returns the F3 distance value.
     */
    static const StaticPtr<ICellularCombiner> F3;
    
    /*!
     * @brief  A combiner function that returns the F3 distance value.
     */
    static const StaticPtr<ICellularCombiner> F4;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a combiner function that uses a linear function.
     * 
     * The returned combiner evaluates the following term:
     * <pre>
     *     noise := a * F1 + b * F2 + c * F3 + d * F4
     * </pre>
     * 
     * @param a Coefficient for F1.
     * @param b Coefficient for F2.
     * @param c Coefficient for F3.
     * @param d Coefficient for F4.
     * 
     * @return <b>[not-null]</b>  The combiner function.
     */
    static Ptr<ICellularCombiner> Linear(float64 a, float64 b, float64 c, float64 d);
    
    /*!
     * @brief  Returns a combiner function that uses a quadratic function.
     * 
     * The returned combiner evaluates the following term:
     * <pre>
     *     noise :=   a2 * F1^2 + a1 * F1 
     *     + b2 * F2^2 + b1 * F2 
     *     + c2 * F3^2 + c1 * F3 
     *     + d2 * F4^2 + d1 * F4
     * </pre>
     * 
     * @param a1 Linear coefficient for F1.
     * @param b1 Linear coefficient for F2.
     * @param c1 Linear coefficient for F3.
     * @param d1 Linear coefficient for F4.
     * @param a2 Quadratic coefficient for F1.
     * @param b2 Quadratic coefficient for F2.
     * @param c2 Quadratic coefficient for F3.
     * @param d2 Quadratic coefficient for F4.
     * 
     * @return <b>[not-null]</b>  The combiner function.
     */
    static Ptr<ICellularCombiner> Square(float64 a1, float64 b1, float64 c1, float64 d1, float64 a2, float64 b2, float64 c2, float64 d2);
    
    virtual float64 Combine(float64 f1, float64 f2);
    
    virtual float64 Combine(float64 f1, float64 f2, float64 f3);
    
    virtual float64 Combine(float64 f1, float64 f2, float64 f3, float64 f4) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of CellularCombiner.
     * 
     * @param serialType <b>[not-null]</b>  The serial ID.
     */
    CellularCombiner(ISerialTypeInfo* serialType);
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief Static initializer function for field F2.
     */
    static Object* StaticInitializer_F2();
    
    /*!
     * @brief Static initializer function for field F3.
     */
    static Object* StaticInitializer_F3();
    
    /*!
     * @brief Static initializer function for field F4.
     */
    static Object* StaticInitializer_F4();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CellularCombiner> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEF3F94E4;
    
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
      if ((ptr = ICellularCombiner::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
