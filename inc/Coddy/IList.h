////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ILIST_H
#define CLODDY_CORE_COLLECTIONS_ILIST_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICollection.h"
#include "Cloddy/IListConst.h"

// Declare interface ::Cloddy::Core::Collections::IList.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent a list of elements.
   */
  template<class T>
  class NO_VTABLE IList : public virtual ICollection<T>, public virtual IListConst<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Inserts the given element into the list.
     * 
     * @param index <b>[0..ICollectionConst::GetCount]</b>  List index where to insert the element.
     * @param element The element to insert.
     */
    virtual void InsertAt(int32 index, typename T::In element) = 0;
    
    /*!
     * @brief  Removes the element at the given list index.
     * 
     * @param index <b>[0..ICollectionConst::GetCount-1]</b>  The list index.
     * 
     * @return The removed element.
     */
    virtual typename T::Out RemoveAt(int32 index) = 0;
    
    /*!
     * @brief  Removes a range of elements.
     * 
     * @param index <b>[0..ICollectionConst::GetCount]</b>  List index of first element to remove.
     * @param count <b>[0..ICollectionConst::GetCount-index]</b>  Number of subsequent elements to 
     * remove.
     */
    virtual void RemoveRange(int32 index, int32 count) = 0;
    
    /*!
     * @brief  Sets the element at the given list index.
     * 
     * @param index <b>[0..ICollectionConst::GetCount-1]</b>  The list index of the element to set.
     * @param element The new element.
     * 
     * @return The previous element.
     */
    virtual typename T::Out SetAt(int32 index, typename T::In element) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IList<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x43FD9319;
    
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
      if ((ptr = ICollection<T>::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IListConst<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
