////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ILISTCONST_H
#define CLODDY_CORE_COLLECTIONS_ILISTCONST_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICollectionConst.h"

// Declare interface ::Cloddy::Core::Collections::IListConst.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent a read-only list of elements.
   */
  template<class T>
  class NO_VTABLE IListConst : public virtual ICollectionConst<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the element at the given list index.
     * 
     * @param index <b>[0..ICollectionConst::GetCount-1]</b>  The list index.
     * 
     * @return The element.
     */
    virtual typename T::Out GetAt(int32 index) = 0;
    
    /*!
     * @brief  Returns the list index of the given element.
     * 
     * @param element The element.
     * 
     * @return The list index or \c -1  if the element is not contained in the list.
     */
    virtual int32 IndexOf(typename T::In element) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IListConst<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5AF5DB6A;
    
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
