////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ICOLLECTIONCONST_H
#define CLODDY_CORE_COLLECTIONS_ICOLLECTIONCONST_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"

// Declare interface ::Cloddy::Core::Collections::ICollectionConst.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent a read-only collection of elements.
   * 
   * Subclasses are free to implement set semantics,ie. equal elements are stored only once.
   */
  template<class T>
  class NO_VTABLE ICollectionConst : public virtual IEnumerable<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of elements in this collection.
     * 
     * @return <b>[>=0]</b>  The numer of elements.
     */
    virtual int32 GetCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns if this collection contains the given element.
     * 
     * @param element The element.
     * 
     * @return \c true  if \e element  is contained in this collection,\c false  if not.
     */
    virtual bool Contains(typename T::In element) = 0;
    
    /*!
     * @brief  Returns if this collection contains all given elements.
     * 
     * @param elements <b>[not-null]</b>  The elements.
     * 
     * @return \c true  if all elements are contained in this collection,\c false  if not.
     */
    virtual bool ContainsAll(IEnumerable<T>* elements) = 0;
    
    /*!
     * @brief  Returns if this collection contains none of the given elements.
     * 
     * @param elements <b>[not-null]</b>  The elements.
     * 
     * @return \c true  if no elements are contained in this collection,\c false  if not.
     */
    virtual bool ContainsNone(IEnumerable<T>* elements) = 0;
    
    /*!
     * @brief  Returns if this collection contains at least one of the given elements.
     * 
     * @param elements <b>[not-null]</b>  The elements.
     * 
     * @return \c true  if at least one element is contained in this collection,\c false  if not.
     */
    virtual bool ContainsSome(IEnumerable<T>* elements) = 0;
    
    /*!
     * @brief  Returns the elements of this collection as an array.
     * 
     * The elements in this collection will be copied into the given array,starting at the array 
     * index specified by \e offset .
     * 
     * @param array <b>[not-null]</b>  The output array.
     * @param offset <b>[>=0]</b>  Offset into \e array .
     * 
     * @return <b>[not-null]</b>  The filled \e array .
     */
    virtual Array<typename T::Out> ToArrayCopy(Array<typename T::Out> array, int32 offset) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICollectionConst<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB8DEC3C2;
    
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
      if ((ptr = IEnumerable<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
