////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ARRAYBUILDER_H
#define CLODDY_CORE_COLLECTIONS_ARRAYBUILDER_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }

// Declare class ::Cloddy::Core::Collections::ArrayBuilder.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for building arrays.
   */
  template<class T>
  class ArrayBuilder : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of ArrayBuilder.
     * 
     * @return <b>[not-null]</b>  The creates ArrayBuilder object.
     */
    static Ptr<ArrayBuilder<T> > New();
    
    /*!
     * @brief  Creates a new instance of ArrayBuilder.
     * 
     * @param initialCapacity <b>[>=0]</b>  The initial capacity to assume.
     * 
     * @return <b>[not-null]</b>  The creates ArrayBuilder object.
     */
    static Ptr<ArrayBuilder<T> > New(int32 initialCapacity);
    
    /*!
     * @brief  Appends a new element to the array being built.
     * 
     * @param element The element to append.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<ArrayBuilder<T> > Add(typename T::In element);
    
    /*!
     * @brief  Returns the built array.
     * 
     * @return <b>[not-null]</b>  The array.
     */
    Array<typename T::Out> Get();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of ArrayBuilder.
     * 
     * @param initialCapacity <b>[>=0]</b>  The initial capacity
     */
    ArrayBuilder(int32 initialCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The initial capacity to assume.
     */
    int32 initialCapacity;
    
    /*!
     * @brief  The dynaminc list used during building.
     */
    Ptr<IList<T> > list;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ArrayBuilder<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF770CFB0;
    
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
