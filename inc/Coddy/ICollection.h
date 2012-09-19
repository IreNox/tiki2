////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ICOLLECTION_H
#define CLODDY_CORE_COLLECTIONS_ICOLLECTION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICollectionConst.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerable; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IPredicate; } } }

// Declare interface ::Cloddy::Core::Collections::ICollection.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent a collection of elements.
   * 
   * Subclasses are free to implement set semantics,ie. equal elements are stored only once.
   */
  template<class T>
  class NO_VTABLE ICollection : public virtual ICollectionConst<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Adds the given element to this collection..
     * 
     * @param element The element to add.
     * 
     * @return \c true  if the collection has changed,\c false  if not.
     */
    virtual bool Add(typename T::In element) = 0;
    
    /*!
     * @brief  Adds the given elements to this collection.
     * 
     * @param elements <b>[not-null]</b>  The elements to add.
     * 
     * @return \c true  if the collection has changed,\c false  if not.
     */
    virtual bool AddAll(IEnumerable<T>* elements) = 0;
    
    /*!
     * @brief  Removes all elements from this collection.
     */
    virtual void Clear() = 0;
    
    /*!
     * @brief  Removes the given element from this collection.
     * 
     * @param element The element to remove.
     * 
     * @return \c true  if the collection has changed,\c false  if not.
     */
    virtual bool Remove(typename T::In element) = 0;
    
    /*!
     * @brief  Removes the given elements from this collection.
     * 
     * @param elements <b>[not-null]</b>  The elements to remove.
     * 
     * @return \c true  if the collection has changed,\c false  if not.
     */
    virtual bool RemoveAll(IEnumerable<T>* elements) = 0;
    
    /*!
     * @brief  Removes all elements from this collection for which the given predicate evaluates to 
     *         \c true .
     * 
     * @param predicate <b>[not-null]</b>  The predicate to use.
     * 
     * @return \c true  if the collection has changed,\c false  if not.
     */
    virtual bool RemoveAll(IPredicate<T>* predicate) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICollection<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x286ED1B1;
    
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
      if ((ptr = ICollectionConst<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
