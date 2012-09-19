////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_ENTRIES_ENUMERATOR_HPP
#define CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_ENTRIES_ENUMERATOR_HPP

#include "Cloddy/TreeDictionary_Entries_Enumerator.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.hpp"

// Include referenced interfaces.

#include "Cloddy/IDeque.h"
#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/ISet.h"

// Include referenced classes.

#include "Cloddy/ArrayDeque.hpp"
#include "Cloddy/EnumeratorBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
DictionaryEntry<TKey, TValue> TreeDictionary_Entries_Enumerator<TKey, TValue>::GetCurrent()
{
  return DictionaryEntry<TKey, TValue>(keys[current], values[current]);
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
void TreeDictionary_Entries_Enumerator<TKey, TValue>::DisposeManaged()
{
  left = null;
  right = null;
  stack = null;
  keys = null;
  values = null;
  
  EnumeratorBase<Val<DictionaryEntry<TKey, TValue> > >::DisposeManaged();
}

template<class TKey, class TValue>
bool TreeDictionary_Entries_Enumerator<TKey, TValue>::DoNext()
{
  int32 idx;
  
  if (next < 0) 
  {
    this->Dispose();
    
    return false;
  }
  
  current = next;
  
  if ((idx = right[next]) >= 0) 
  {
    next = idx;
    
    while ((idx = left[next]) >= 0)
    {
      stack->PushLast(next);
      
      next = idx;
    }
  }
  else next = stack->PopLast();
  
  return true;
}

// -------------------------------------------------------------------------------------------------
// Private / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of Tree_Enumerator.
 * 
 * @param root The root node.
 * @param left Left child nodes.
 * @param right Right child nodes.
 * @param keys The node keys.
 * @param values The node values.
 */
template<class TKey, class TValue>
TreeDictionary_Entries_Enumerator<TKey, TValue>::TreeDictionary_Entries_Enumerator(int32 root, Array<int32> left, Array<int32> right, Array<typename TKey::Out> keys, Array<typename TValue::Out> values)
{
  // Initialize all primitive fields to default values.
  
  this->current = 0;
  this->next = 0;
  
  try
  {
    this->left = left;
    this->right = right;
    this->keys = keys;
    this->values = values;
    
    // Initialize traversal state machine.
    
    stack = new ArrayDeque<Prm<int32> >();
    
    stack->PushLast(-1);
    
    current = -1;
    
    if ((next = root) >= 0) 
    {
      int32 idx;
      
      while ((idx = left[next]) >= 0)
      {
        stack->PushLast(next);
        
        next = idx;
      }
    }
  }
  catch (...)
  {
    this->Dispose();
    
    throw ;
  }
}

} } } 

#endif
