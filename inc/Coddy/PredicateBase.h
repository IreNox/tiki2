////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_PREDICATEBASE_H
#define CLODDY_CORE_COLLECTIONS_PREDICATEBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IPredicate.h"

// Declare class ::Cloddy::Core::Collections::PredicateBase.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class T>
  class PredicateBase : public virtual IPredicate<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual Ptr<IPredicate<T> > And(IPredicate<T>* other);
    
    virtual bool Evaluate(typename T::In element) = 0;
    
    virtual Ptr<IPredicate<T> > Not();
    
    virtual Ptr<IPredicate<T> > Or(IPredicate<T>* other);
    
    virtual Ptr<IPredicate<T> > XOr(IPredicate<T>* other);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<PredicateBase<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xA9106C44;
    
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
      if ((ptr = IPredicate<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
