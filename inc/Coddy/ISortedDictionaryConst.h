////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ISORTEDDICTIONARYCONST_H
#define CLODDY_CORE_COLLECTIONS_ISORTEDDICTIONARYCONST_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.h"

// Include referenced interfaces.

#include "Cloddy/IDictionaryConst.h"

// Declare interface ::Cloddy::Core::Collections::ISortedDictionaryConst.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for immutable dictionaries that store their keys in order.
   */
  template<class TKey, class TValue>
  class NO_VTABLE ISortedDictionaryConst : public virtual IDictionaryConst<TKey, TValue>
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the maximum entry of this dictionary.
     * 
     * @return The maximum entry.
     */
    virtual DictionaryEntry<TKey, TValue> GetMaximumEntry() = 0;
    
    /*!
     * @brief  Returns the maximum key of this dictionary.
     * 
     * @return The maximum key.
     */
    virtual typename TKey::Out GetMaximumKey() = 0;
    
    /*!
     * @brief  Returns the minimum entry of this dictionary.
     * 
     * @return The minimum entry.
     */
    virtual DictionaryEntry<TKey, TValue> GetMinimumEntry() = 0;
    
    /*!
     * @brief  Returns the minimum key of this dictionary.
     * 
     * @return The minimum key.
     */
    virtual typename TKey::Out GetMinimumKey() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISortedDictionaryConst<TKey, TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC583A1D5;
    
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
      if ((ptr = IDictionaryConst<TKey, TValue>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
