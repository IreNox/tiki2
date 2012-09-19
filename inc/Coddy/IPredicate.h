////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_IPREDICATE_H
#define CLODDY_CORE_COLLECTIONS_IPREDICATE_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::Core::Collections::IPredicate.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent a boolean predicate for elements of a given 
   *         type.
   */
  template<class T>
  class NO_VTABLE IPredicate : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns a predicate that is \c true  when this predicate and the given one is 
     *         \c true .
     * 
     * @param other <b>[not-null]</b>  The other predicate.
     * 
     * @return <b>[not-null]</b>  The resulting predicate.
     */
    virtual Ptr<IPredicate<T> > And(IPredicate<T>* other) = 0;
    
    /*!
     * @brief  Evaluates this predicate.
     * 
     * @param element The element.
     * 
     * @return The resulting value.
     */
    virtual bool Evaluate(typename T::In element) = 0;
    
    /*!
     * @brief  Returns a predicate that returns the inverse of this predicate.
     * 
     * @return <b>[not-null]</b>  The resulting predicate.
     */
    virtual Ptr<IPredicate<T> > Not() = 0;
    
    /*!
     * @brief  Returns a predicate that is \c true  when this predicate or the given one is 
     *         \c true  (inclusive or).
     * 
     * @param other <b>[not-null]</b>  The other predicate.
     * 
     * @return <b>[not-null]</b>  The resulting predicate.
     */
    virtual Ptr<IPredicate<T> > Or(IPredicate<T>* other) = 0;
    
    /*!
     * @brief  Returns a predicate that is \c true  when either this predicate or the given one is 
     *         \c true  (exclusive or).
     * 
     * @param other <b>[not-null]</b>  The other predicate.
     * 
     * @return <b>[not-null]</b>  The resulting predicate.
     */
    virtual Ptr<IPredicate<T> > XOr(IPredicate<T>* other) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IPredicate<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xBDB56688;
    
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
