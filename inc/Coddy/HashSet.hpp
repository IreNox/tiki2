////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHSET_HPP
#define CLODDY_CORE_COLLECTIONS_HASHSET_HPP

#include "Cloddy/HashSet.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/ArrayUtilGeneric.hpp"
#include "Cloddy/CollectionBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "Cloddy/HashDictionary_Keys_Enumerator.hpp"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/LowLevel.h"
#include "Cloddy/Maths.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;
using namespace CodeX::System;

// Use referenced classes.

using Cloddy::Core::Math::Maths;
using Cloddy::Core::System::ArrayUtilGeneric;
using Cloddy::Core::System::LowLevel;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
int32 HashSet<T>::GetCount()
{
  return countUsedNodes;
}

template<class T>
Ptr<IEnumerator<T> > HashSet<T>::GetEnumerator()
{
  return new HashDictionary_Keys_Enumerator<T>(hashtable, nodeKeys, nodeNext);
}

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of HashDictionary.
 * 
 * @param initialCapacity <b>[>=0]</b>  The inhitial capacity of the dictionary,in key/value pairs.
 */
template<class T>
HashSet<T>::HashSet(int32 initialCapacity)
{
  // Initialize all primitive fields to default values.
  
  this->countUsedBuckets = 0;
  this->countUsedNodes = 0;
  this->mask = 0;
  this->nodeFree = 0;
  
#ifdef _DEBUG
  if (initialCapacity < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("HashSet.HashSet"), ZSTRING("initialCapacity"), 0);
#endif
  
  if (initialCapacity < 12) initialCapacity = 12;
  
  // Number of buckets is smallest power of two that is 125% of maximum number of key/value pairs.
  
  hashtable = Array<int32>((int32) (Maths::NextPowerOfTwo(initialCapacity * 5 / 4))).Zero();
  mask = hashtable.Length() - 1;
  
  for (int32 i = 0; i < hashtable.Length(); i++)
    hashtable[i] = -1;
  
  // Initialize value nodes.
  
  nodeKeys = Array<typename T::Out>(initialCapacity);
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

template<class T>
bool HashSet<T>::Add(typename T::In element)
{
  int32 bucketIdx;
  int32 currentNode;
  
  // Need to grow hashtable?
  
  if (countUsedBuckets > 0 && countUsedNodes / countUsedBuckets > 4) GrowHashtable();
  
  bucketIdx = HashCode(element) & mask;
  currentNode = hashtable[bucketIdx];
  
  // Linked list of hash bucket is empty?
  
  if (currentNode == -1) 
  {
    // Fetch free value node.
    
    currentNode = PopFree();
    
    // Store key/value pair.
    
    nodeKeys[currentNode] = element;
    
    // Append value node to linked list of hash bucket.
    
    hashtable[bucketIdx] = currentNode;
    nodeNext[currentNode] = -1;
    
    countUsedBuckets++;
    
    return true;
  }
  
  // Linked list of hash bucket is not empty.
  
  while (true)
  {
    int32 nextNode;
    
    // A value node with matching key already exists?
    
    if (T::Equals(nodeKeys[currentNode], element)) return false;
    
    // Advance to next value node in linked list.
    
    nextNode = nodeNext[currentNode];
    
    // No more value nodes in linked list? Add a new value node with the given key/value pair.
    
    if (nextNode == -1) 
    {
      int32 newNode;
      
      // Fetch free value node.
      
      newNode = PopFree();
      
      // Store key/value pair.
      
      nodeKeys[newNode] = element;
      
      // Append value node to linked list of hash bucket.
      
      nodeNext[currentNode] = newNode;
      nodeNext[newNode] = -1;
      
      return true;
    }
    
    currentNode = nextNode;
  }
}

template<class T>
void HashSet<T>::Clear()
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
    nodeKeys[i] = T::Default();
  
  countUsedBuckets = 0;
  countUsedNodes = 0;
}

template<class T>
bool HashSet<T>::Contains(typename T::In element)
{
  // Find hash bucket for key and search the linked list of value nodes for a matching key.
  
  for (int32 idx = hashtable[HashCode(element) & mask]; idx != -1; idx = nodeNext[idx])
  {
    // A value node with matching key already exists?
    
    if (T::Equals(nodeKeys[idx], element)) return true;
  }
  
  // Key has not been found in hash map.
  
  return false;
}

template<class T>
bool HashSet<T>::Remove(typename T::In element)
{
  int32 bucketIdx;
  int32 prev;
  
  // Find hash bucket for key.
  
  bucketIdx = HashCode(element) & mask;
  prev = -1;
  
  // Search the linked list of value nodes for a matching key.
  
  for (int32 idx = hashtable[bucketIdx]; idx != -1; prev = idx, idx = nodeNext[idx])
  {
    // A value node with matching key already exists?
    
    if (!T::Equals(nodeKeys[idx], element)) continue;
    
    // Remove value node from linked list of hash bucket.
    
    if (prev == -1) 
    {
      if ((hashtable[bucketIdx] = nodeNext[idx]) == -1) countUsedBuckets--;
    }
    else nodeNext[prev] = nodeNext[idx];
    
    // Add node to free list.
    
    PushFree(idx);
    
    return true;
  }
  
  return false;
}

template<class T>
Array<typename T::Out> HashSet<T>::ToArrayCopy(Array<typename T::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("HashSet.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("HashSet.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  for (int32 i = 0; i < hashtable.Length(); i++)
  {
    int32 idx;
    
    idx = hashtable[i];
    
    while (idx >= 0)
    {
      array[offset++] = nodeKeys[idx];
      idx = nodeNext[idx];
    }
  }
  
  return array;
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
template<class T>
int32 HashSet<T>::HashCode(typename T::In key)
{
  return LowLevel::Hash32(T::Hash(key));
}

template<class T>
void HashSet<T>::GrowHashtable()
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

template<class T>
void HashSet<T>::GrowNodeStorage()
{
  int32 idx;
  
  idx = nodeNext.Length();
  
  // Grow node storage arrays.
  
  nodeKeys = ArrayUtilGeneric<T>::GrowUntil(nodeKeys, nodeKeys.Length(), nodeKeys.Length() + 1);
  nodeNext = ArrayUtilGeneric<Prm<int32> >::GrowTo(nodeNext, nodeNext.Length(), nodeKeys.Length());
  
  // Update linked list of free nodes.
  
  for (int32 i = idx; i < nodeKeys.Length() - 1; i++)
    nodeNext[i] = i + 1;
  
  nodeNext[nodeKeys.Length() - 1] = -1;
  nodeFree = idx;
}

/*!
 * @brief  Fetches an unused storage node.
 * 
 * @return Index of storage node.
 */
template<class T>
int32 HashSet<T>::PopFree()
{
  int32 free;
  
  // Need to grow node storage?
  
  if (nodeFree == -1) GrowNodeStorage();
  
  free = nodeFree;
  nodeFree = nodeNext[nodeFree];
  
  countUsedNodes++;
  
  return free;
}

template<class T>
void HashSet<T>::PushFree(int32 idx)
{
  nodeNext[idx] = nodeFree;
  nodeFree = idx;
  
  countUsedNodes--;
}

} } } 

#endif
