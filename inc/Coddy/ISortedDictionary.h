////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ISORTEDDICTIONARY_H
#define CLODDY_CORE_COLLECTIONS_ISORTEDDICTIONARY_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.h"

// Include referenced interfaces.

#include "Cloddy/IDictionary.h"
#include "Cloddy/ISortedDictionaryConst.h"

// Declare interface ::Cloddy::Core::Collections::ISortedDictionary.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for mutable dictionaries that store their keys in order.
   */
  template<class TKey, class TValue>
  class NO_VTABLE ISortedDictionary : public virtual IDictionary<TKey, TValue>, public virtual ISortedDictionaryConst<TKey, TValue>
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Removes the maximum entry from this dictionary.
     * 
     * @return The removed entry.
     */
    virtual DictionaryEntry<TKey, TValue> RemoveMaximumEntry() = 0;
    
    /*!
     * @brief  Removes the maximum key from this dictionary.
     * 
     * @return The removed key.
     */
    virtual typename TKey::Out RemoveMaximumKey() = 0;
    
    /*!
     * @brief  Removes the minimum entry from this dictionary..
     * 
     * @return The removed entry.
     */
    virtual DictionaryEntry<TKey, TValue> RemoveMinimumEntry() = 0;
    
    /*!
     * @brief  Removes the minimum key from this dictionary..
     * 
     * @return The removed key.
     */
    virtual typename TKey::Out RemoveMinimumKey() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISortedDictionary<TKey, TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x4B74C10E;
    
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
      if ((ptr = IDictionary<TKey, TValue>::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ISortedDictionaryConst<TKey, TValue>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
