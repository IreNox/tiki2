////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_HPP
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_HPP

#include "Cloddy/HashDictionary.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.hpp"

// Include referenced interfaces.

#include "Cloddy/ICollectionConst.h"
#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/ISet.h"
#include "Cloddy/ISetConst.h"

// Include referenced classes.

#include "Cloddy/ArrayUtilGeneric.hpp"
#include "CodeX/ErrorInfo.h"
#include "Cloddy/HashDictionary_Entries.hpp"
#include "Cloddy/HashDictionary_Keys.hpp"
#include "Cloddy/HashDictionary_Values.hpp"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/LowLevel.h"
#include "Cloddy/Maths.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using Cloddy::Core::Math::Maths;
using Cloddy::Core::System::ArrayUtilGeneric;
using Cloddy::Core::System::LowLevel;
using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
int32 HashDictionary<TKey, TValue>::GetCount()
{
  return countUsedNodes;
}

template<class TKey, class TValue>
Ptr<ISetConst<Val<DictionaryEntry<TKey, TValue> > > > HashDictionary<TKey, TValue>::GetEntries()
{
  return new HashDictionary_Entries<TKey, TValue>(this);
}

template<class TKey, class TValue>
Ptr<ISetConst<TKey> > HashDictionary<TKey, TValue>::GetKeys()
{
  return new HashDictionary_Keys<TKey, TValue>(this);
}

template<class TKey, class TValue>
Ptr<ICollectionConst<TValue> > HashDictionary<TKey, TValue>::GetValues()
{
  return new HashDictionary_Values<TKey, TValue>(this);
}

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of HashDictionary.
 */
template<class TKey, class TValue>
HashDictionary<TKey, TValue>::HashDictionary()
{
  // Initialize all primitive fields to default values.
  
  this->countUsedBuckets = 0;
  this->countUsedNodes = 0;
  this->mask = 0;
  this->nodeFree = 0;
  
  int32 initialCapacity;
  
  initialCapacity = 12;
  
  // Number of buckets is smallest power of two that is 125% of maximum number of key/value pairs.
  
  hashtable = Array<int32>((int32) (Maths::NextPowerOfTwo(initialCapacity * 5 / 4))).Zero();
  mask = hashtable.Length() - 1;
  
  for (int32 i = 0; i < hashtable.Length(); i++)
    hashtable[i] = -1;
  
  // Initialize value nodes.
  
  nodeKeys = Array<typename TKey::Out>(initialCapacity);
  nodeValues = Array<typename TValue::Out>(initialCapacity);
  nodeNext = Array<int32>(initialCapacity).Zero();
  
  // Initialize list of free values nodes.
  
  nodeFree = 0;
  
  for (int32 i = 0; i < initialCapacity - 1; i++)
    nodeNext[i] = i + 1;
  
  nodeNext[initialCapacity - 1] = -1;
}

/*!
 * @brief  Creates a new instance of HashDictionary.
 * 
 * @param initialCapacity <b>[>=0]</b>  The inhitial capacity of the dictionary,in key/value pairs.
 */
template<class TKey, class TValue>
HashDictionary<TKey, TValue>::HashDictionary(int32 initialCapacity)
{
  // Initialize all primitive fields to default values.
  
  this->countUsedBuckets = 0;
  this->countUsedNodes = 0;
  this->mask = 0;
  this->nodeFree = 0;
  
#ifdef _DEBUG
  if (initialCapacity < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("HashDictionary.HashDictionary"), ZSTRING("initialCapacity"), 0);
#endif
  
  if (initialCapacity < 12) initialCapacity = 12;
  
  // Number of buckets is smallest power of two that is 125% of maximum number of key/value pairs.
  
  hashtable = Array<int32>((int32) (Maths::NextPowerOfTwo(initialCapacity * 5 / 4))).Zero();
  mask = hashtable.Length() - 1;
  
  for (int32 i = 0; i < hashtable.Length(); i++)
    hashtable[i] = -1;
  
  // Initialize value nodes.
  
  nodeKeys = Array<typename TKey::Out>(initialCapacity);
  nodeValues = Array<typename TValue::Out>(initialCapacity);
  nodeNext = Array<int32>(initialCapacity).Zero();
  
  // Initialize list of free values nodes.
  
  nodeFree = 0;
  
  for (int32 i = 0; i < initialCapacity - 1; i++)
    nodeNext[i] = i + 1;
  
  nodeNext[initialCapacity - 1] = -1;
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
void HashDictionary<TKey, TValue>::Clear()
{
  // Reset hash buckets.
  
  for (int32 i = 0; i < hashtable.Length(); i++)
    hashtable[i] = -1;
  
  // Reset list of free nodes.
  
  nodeFree = 0;
  
  for (int32 i = 0; i < nodeNext.Length() - 1; i++)
    nodeNext[i] = i + 1;
  
  nodeNext[nodeNext.Length() - 1] = -1;
  
  // Clear all object references.
  
  for (int32 i = 0; i < nodeKeys.Length(); i++)
  {
    nodeKeys[i] = TKey::Default();
    nodeValues[i] = TValue::Default();
  }
  
  countUsedBuckets = 0;
  countUsedNodes = 0;
}

template<class TKey, class TValue>
bool HashDictionary<TKey, TValue>::Contains(typename TKey::In key)
{
  // Find hash bucket for key and search the linked list of value nodes for a matching key.
  
  for (int32 idx = hashtable[HashCode(key) & mask]; idx != -1; idx = nodeNext[idx])
  {
    // A value node with matching key already exists?
    
    if (TKey::Equals(nodeKeys[idx], key)) return true;
  }
  
  // Key has not been found in hash map.
  
  return false;
}

template<class TKey, class TValue>
typename TValue::Out HashDictionary<TKey, TValue>::Get(typename TKey::In key, typename TValue::In defaultValue)
{
  // Find hash bucket for key and search the linked list of value nodes for a matching key.
  
  for (int32 idx = hashtable[HashCode(key) & mask]; idx != -1; idx = nodeNext[idx])
  {
    // A value node with matching key already exists?
    
    if (TKey::Equals(nodeKeys[idx], key)) return nodeValues[idx];
  }
  
  // Key has not been found in hash map.
  
  return defaultValue;
}

template<class TKey, class TValue>
typename TValue::Out HashDictionary<TKey, TValue>::Put(typename TKey::In key, typename TValue::In value)
{
  int32 bucketIdx;
  int32 currentNode;
  
  // Need to grow hashtable?
  
  if (countUsedBuckets > 0 && countUsedNodes / countUsedBuckets > 4) GrowHashtable();
  
  bucketIdx = HashCode(key) & mask;
  currentNode = hashtable[bucketIdx];
  
  // Linked list of hash bucket is empty?
  
  if (currentNode == -1) 
  {
    // Fetch free value node.
    
    currentNode = PopFree();
    
    // Store key/value pair.
    
    nodeKeys[currentNode] = key;
    nodeValues[currentNode] = value;
    
    // Append value node to linked list of hash bucket.
    
    hashtable[bucketIdx] = currentNode;
    nodeNext[currentNode] = -1;
    
    countUsedBuckets++;
    
    return TValue::Default();
  }
  
  // Linked list of hash bucket is not empty.
  
  while (true)
  {
    int32 nextNode;
    
    // A value node with matching key already exists?
    
    if (TKey::Equals(nodeKeys[currentNode], key)) 
    {
      typename TValue::Out previous;
      
      // Update value and return.
      
      previous = nodeValues[currentNode];
      nodeValues[currentNode] = value;
      
      return previous;
    }
    
    // Advance to next value node in linked list.
    
    nextNode = nodeNext[currentNode];
    
    // No more value nodes in linked list? Add a new value node with the given key/value pair.
    
    if (nextNode == -1) 
    {
      int32 newNode;
      
      // Fetch free value node.
      
      newNode = PopFree();
      
      // Store key/value pair.
      
      nodeKeys[newNode] = key;
      nodeValues[newNode] = value;
      
      // Append value node to linked list of hash bucket.
      
      nodeNext[currentNode] = newNode;
      nodeNext[newNode] = -1;
      
      return TValue::Default();
    }
    
    currentNode = nextNode;
  }
}

template<class TKey, class TValue>
typename TValue::Out HashDictionary<TKey, TValue>::Remove(typename TKey::In key)
{
  int32 bucketIdx;
  int32 prev;
  
  // Find hash bucket for key.
  
  bucketIdx = HashCode(key) & mask;
  prev = -1;
  
  // Search the linked list of value nodes for a matching key.
  
  for (int32 idx = hashtable[bucketIdx]; idx != -1; prev = idx, idx = nodeNext[idx])
  {
    typename TValue::Out value;
    
    // A value node with matching key already exists?
    
    if (!TKey::Equals(nodeKeys[idx], key)) continue;
    
    // Remove value node from linked list of hash bucket.
    
    if (prev == -1) 
    {
      if ((hashtable[bucketIdx] = nodeNext[idx]) == -1) countUsedBuckets--;
    }
    else nodeNext[prev] = nodeNext[idx];
    
    // Clear node value.
    
    value = nodeValues[idx];
    nodeValues[idx] = TValue::Default();
    
    // Add node to free list.
    
    PushFree(idx);
    
    return value;
  }
  
  return TValue::Default();
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Fetches an unused storage node.
 * 
 * @return Index of storage node.
 */
template<class TKey, class TValue>
int32 HashDictionary<TKey, TValue>::PopFree()
{
  int32 free;
  
  // Need to grow node storage?
  
  if (nodeFree == -1) GrowNodeStorage();
  
  free = nodeFree;
  nodeFree = nodeNext[nodeFree];
  
  countUsedNodes++;
  
  return free;
}

// -------------------------------------------------------------------------------------------------
// Private / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Computes a hash value for the given key.
 * 
 * @param key The key value.
 * 
 * @return The hash value.
 */
template<class TKey, class TValue>
int32 HashDictionary<TKey, TValue>::HashCode(typename TKey::In key)
{
  return LowLevel::Hash32(TKey::Hash(key));
}

template<class TKey, class TValue>
void HashDictionary<TKey, TValue>::GrowHashtable()
{
  Array<int32> hashtable;
  
  // Create new hashtable array.
  
  hashtable = Array<int32>(this->hashtable.Length() * 2).Zero();
  mask = hashtable.Length() - 1;
  
  for (int32 i = 0; i < hashtable.Length(); i++)
    hashtable[i] = -1;
  
  // Re-hash all existing value nodes.
  
  countUsedBuckets = 0;
  
  for (int32 i = 0; i < this->hashtable.Length(); i++)
  {
    int32 idx;
    
    // Visit all non-empty hashtable buckets.
    
    idx = this->hashtable[i];
    
    while (idx >= 0)
    {
      int32 next;
      int32 bucket;
      
      next = nodeNext[idx];
      bucket = HashCode(nodeKeys[idx]) & mask;
      
      if ((nodeNext[idx] = hashtable[bucket]) == -1) countUsedBuckets++;
      
      hashtable[bucket] = idx;
      idx = next;
    }
  }
  
  this->hashtable = hashtable;
}

template<class TKey, class TValue>
void HashDictionary<TKey, TValue>::GrowNodeStorage()
{
  int32 idx;
  
  idx = nodeNext.Length();
  
  // Grow node storage arrays.
  
  nodeKeys = ArrayUtilGeneric<TKey>::GrowUntil(nodeKeys, nodeKeys.Length(), nodeKeys.Length() + 1);
  nodeValues = ArrayUtilGeneric<TValue>::GrowTo(nodeValues, nodeValues.Length(), nodeKeys.Length());
  nodeNext = ArrayUtilGeneric<Prm<int32> >::GrowTo(nodeNext, nodeNext.Length(), nodeKeys.Length());
  
  // Update linked list of free nodes.
  
  for (int32 i = idx; i < nodeKeys.Length() - 1; i++)
    nodeNext[i] = i + 1;
  
  nodeNext[nodeKeys.Length() - 1] = -1;
  nodeFree = idx;
}

template<class TKey, class TValue>
void HashDictionary<TKey, TValue>::PushFree(int32 idx)
{
  nodeNext[idx] = nodeFree;
  nodeFree = idx;
  
  countUsedNodes--;
}

} } } 

#endif
