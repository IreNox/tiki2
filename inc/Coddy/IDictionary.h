////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_IDICTIONARY_H
#define CLODDY_CORE_COLLECTIONS_IDICTIONARY_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IDictionaryConst.h"

// Declare interface ::Cloddy::Core::Collections::IDictionary.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent a set of key/value pairs.
   */
  template<class TKey, class TValue>
  class NO_VTABLE IDictionary : public virtual IDictionaryConst<TKey, TValue>
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Removes all key/value pairs from the map.
     */
    virtual void Clear() = 0;
    
    /*!
     * @brief  Maps the given value to the specified key.
     * 
     * @param key The key.
     * @param value The value.
     * 
     * @return The previously mapped value.
     */
    virtual typename TValue::Out Put(typename TKey::In key, typename TValue::In value) = 0;
    
    /*!
     * @brief  Removes the mapping for the given key.
     * 
     * @param key The key.
     * 
     * @return The mapped value.
     */
    virtual typename TValue::Out Remove(typename TKey::In key) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDictionary<TKey, TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x83CCCC5F;
    
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
