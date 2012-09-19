////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_DICTIONARYENTRY_H
#define CLODDY_CORE_COLLECTIONS_DICTIONARYENTRY_H

#include "CodeX/System.h"

// Declare class ::Cloddy::Core::Collections::DictionaryEntry.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Represents a single key/value pair stored in an IDictionary instance.
   */
  template<class TKey, class TValue>
  struct DictionaryEntry : StructType
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  The entry key.
     */
    typename TKey::Out Key;
    
    /*!
     * @brief  The entry value.
     */
    typename TValue::Out Value;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of DictionaryEntry.
     * 
     * @param key The entry key.
     * @param value The entry value.
     */
    DictionaryEntry(typename TKey::In key, typename TValue::In value);
    
    DictionaryEntry();
    
    // ---------------------------------------------------------------------------------------------
    //  Copy constructor and copy assignment operator
    // ---------------------------------------------------------------------------------------------
  public:
    
    DictionaryEntry(const DictionaryEntry<TKey, TValue>& other);
    
    DictionaryEntry<TKey, TValue>& operator=(const DictionaryEntry<TKey, TValue>& other);
  };
  
} } } 

#endif
