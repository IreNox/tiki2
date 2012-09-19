////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_LISTBASE_H
#define CLODDY_CORE_COLLECTIONS_LISTBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/CollectionBase.h"

// Declare class ::Cloddy::Core::Collections::ListBase.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Abstract base class for IList implementations.
   */
  template<class T>
  class ListBase : public CollectionBase<T>, public virtual IList<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool Contains(typename T::In element);
    
    virtual typename T::Out GetAt(int32 index) = 0;
    
    virtual int32 IndexOf(typename T::In element) = 0;
    
    virtual void InsertAt(int32 index, typename T::In element) = 0;
    
    virtual typename T::Out RemoveAt(int32 index) = 0;
    
    virtual void RemoveRange(int32 index, int32 count) = 0;
    
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
    public: typedef Ptr<ListBase<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5CC4A989;
    
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
      if ((ptr = CollectionBase<T>::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IList<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
