////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_HPP
#define CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_HPP

#include "Cloddy/TreeDictionary.h"

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
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/Maths.h"
#include "Cloddy/TreeDictionary_Entries.hpp"
#include "Cloddy/TreeDictionary_Keys.hpp"
#include "Cloddy/TreeDictionary_Values.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using Cloddy::Core::Math::Maths;
using Cloddy::Core::System::ArrayUtilGeneric;
using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::GetCount()
{
  return CountNodes(root);
}

template<class TKey, class TValue>
Ptr<ISetConst<Val<DictionaryEntry<TKey, TValue> > > > TreeDictionary<TKey, TValue>::GetEntries()
{
  return new TreeDictionary_Entries<TKey, TValue>(this);
}

template<class TKey, class TValue>
Ptr<ISetConst<TKey> > TreeDictionary<TKey, TValue>::GetKeys()
{
  return new TreeDictionary_Keys<TKey, TValue>(this);
}

template<class TKey, class TValue>
DictionaryEntry<TKey, TValue> TreeDictionary<TKey, TValue>::GetMaximumEntry()
{
  int32 next;
  int32 node;
  
  node = -1;
  next = root;
  
  while (next >= 0)
  {
    next = right[node = next];
  }
  
  if (node < 0) return DictionaryEntry<TKey, TValue>();
  
  return DictionaryEntry<TKey, TValue>(keys[node], values[node]);
}

template<class TKey, class TValue>
typename TKey::Out TreeDictionary<TKey, TValue>::GetMaximumKey()
{
  int32 next;
  int32 node;
  
  node = -1;
  next = root;
  
  while (next >= 0)
  {
    next = right[node = next];
  }
  
  return node == -1 ? TKey::Default() : keys[node];
}

template<class TKey, class TValue>
DictionaryEntry<TKey, TValue> TreeDictionary<TKey, TValue>::GetMinimumEntry()
{
  int32 next;
  int32 node;
  
  node = -1;
  next = root;
  
  while (next >= 0)
  {
    next = left[node = next];
  }
  
  if (node < 0) return DictionaryEntry<TKey, TValue>();
  
  return DictionaryEntry<TKey, TValue>(keys[node], values[node]);
}

template<class TKey, class TValue>
typename TKey::Out TreeDictionary<TKey, TValue>::GetMinimumKey()
{
  int32 next;
  int32 node;
  
  node = -1;
  next = root;
  
  while (next >= 0)
  {
    next = left[node = next];
  }
  
  return node == -1 ? TKey::Default() : keys[node];
}

template<class TKey, class TValue>
Ptr<ICollectionConst<TValue> > TreeDictionary<TKey, TValue>::GetValues()
{
  return new TreeDictionary_Values<TKey, TValue>(this);
}

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of TreeDictionary.
 */
template<class TKey, class TValue>
TreeDictionary<TKey, TValue>::TreeDictionary()
{
  // Initialize all primitive fields to default values.
  
  this->capacity = 0;
  this->free = 0;
  this->root = 0;
  
  root = -1;
  free = -1;
}

/*!
 * @brief  Creates a new instance of TreeDictionary.
 * 
 * @param initialCapacity <b>[>=0]</b>  The initial capacity of the dictionary,in mapped values.
 */
template<class TKey, class TValue>
TreeDictionary<TKey, TValue>::TreeDictionary(int32 initialCapacity)
{
  // Initialize all primitive fields to default values.
  
  this->capacity = 0;
  this->free = 0;
  this->root = 0;
  
#ifdef _DEBUG
  if (initialCapacity < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("TreeDictionary.TreeDictionary"), ZSTRING("initialCapacity"), 0);
#endif
  
  root = -1;
  free = -1;
  
  EnsureCapacity(initialCapacity);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Clear()
{
  // Clear root node.
  
  root = -1;
  
  // Clear keys and values.
  
  for (int32 i = 0; i < keys.Length(); i++)
    keys[i] = TKey::Default();
  for (int32 i = 0; i < values.Length(); i++)
    values[i] = TValue::Default();
  
  // Add all nodes to the free list.
  
  free = -1;
  
  for (int32 i = capacity - 1; i >= 0; i--)
    PushFree(i);
}

template<class TKey, class TValue>
bool TreeDictionary<TKey, TValue>::Contains(typename TKey::In key)
{
  return FindKey(root, key) >= 0;
}

template<class TKey, class TValue>
typename TValue::Out TreeDictionary<TKey, TValue>::Get(typename TKey::In key, typename TValue::In defaultValue)
{
  int32 n;
  
  n = FindKey(root, key);
  
  return n < 0 ? defaultValue : values[n];
}

template<class TKey, class TValue>
typename TValue::Out TreeDictionary<TKey, TValue>::Put(typename TKey::In key, typename TValue::In value)
{
  int32 n;
  
  if ((n = root) >= 0) 
  {
    int32 compare;
    int32 idx;
    typename TValue::Out result;
    
    // Perform binary search tree insertion.
    
    compare = TKey::Compare(key, keys[n]);
    
    if (compare < 0) idx = Insert_XL(left[n], key);
    else if (compare > 0) idx = Insert_XR(right[n], key);
    else idx = n;
    
    // Overwrite current node.
    
    if (idx < 0) 
    {
      count[n]++;
      
      idx = -1 - idx;
    }
    
    result = values[idx];
    values[idx] = value;
    
    return result;
  }
  
  // Create new tree node.
  
  root = CreateNode(key);
  values[root] = value;
  
  return TValue::Default();
}

template<class TKey, class TValue>
typename TValue::Out TreeDictionary<TKey, TValue>::Remove(typename TKey::In key)
{
  int32 idx;
  typename TValue::Out result;
  
  idx = root < 0 ? -1 : Delete_X(key);
  
  if (idx >= 0) 
  {
    result = values[idx];
    values[idx] = TValue::Default();
  }
  else result = TValue::Default();
  
  return result;
}

template<class TKey, class TValue>
DictionaryEntry<TKey, TValue> TreeDictionary<TKey, TValue>::RemoveMaximumEntry()
{
  typename TKey::Out maximum;
  
  maximum = GetMaximumKey();
  
  return DictionaryEntry<TKey, TValue>(maximum, Remove(maximum));
}

template<class TKey, class TValue>
typename TKey::Out TreeDictionary<TKey, TValue>::RemoveMaximumKey()
{
  typename TKey::Out maximum;
  
  maximum = GetMaximumKey();
  
  Remove(maximum);
  
  return maximum;
}

template<class TKey, class TValue>
DictionaryEntry<TKey, TValue> TreeDictionary<TKey, TValue>::RemoveMinimumEntry()
{
  typename TKey::Out minimum;
  
  minimum = GetMinimumKey();
  
  return DictionaryEntry<TKey, TValue>(minimum, Remove(minimum));
}

template<class TKey, class TValue>
typename TKey::Out TreeDictionary<TKey, TValue>::RemoveMinimumKey()
{
  typename TKey::Out minimum;
  
  minimum = GetMinimumKey();
  
  Remove(minimum);
  
  return minimum;
}

// -------------------------------------------------------------------------------------------------
// Private / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  (Re-)balances the given tree node.
 * 
 * @param n The tree node to balance (left child of \e p ).
 * @param p The parent of \e n .
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Balance_L(int32 n, int32 p)
{
  int32 delta;
  int32 deltaL;
  int32 deltaR;
  int32 countL;
  int32 countR;
  int32 countLL;
  int32 countLR;
  int32 countRL;
  int32 countRR;
  int32 c;
  
  // Compute descendant counts.
  
  if ((c = left[n]) >= 0) 
  {
    countLL = CountNodes(left[c]);
    countLR = CountNodes(right[c]);
    countL = countLL + countLR + 1;
  }
  else countL = countLL = countLR = 0;
  if ((c = right[n]) >= 0) 
  {
    countRL = CountNodes(left[c]);
    countRR = CountNodes(right[c]);
    countR = countRL + countRR + 1;
  }
  else countR = countRL = countRR = 0;
  
  // Compute balance deltas.
  
  delta = Maths::AbsI(countL - countR);
  deltaL = Maths::AbsI(countRR - 1 - countL - countRL);
  deltaR = Maths::AbsI(countLL - 1 - countR - countLR);
  
  // Optimize balance.
  
  if (deltaL < deltaR && deltaL <= delta) Rotate_LL(n, p);
  else if (deltaR < deltaL && deltaR < delta) Rotate_LR(n, p);
}

/*!
 * @brief  (Re-)balances the given tree node.
 * 
 * @param n The tree node to balance (right child of \e p ).
 * @param p The parent of \e n .
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Balance_R(int32 n, int32 p)
{
  int32 delta;
  int32 deltaL;
  int32 deltaR;
  int32 countL;
  int32 countR;
  int32 countLL;
  int32 countLR;
  int32 countRL;
  int32 countRR;
  int32 c;
  
  // Compute descendant counts.
  
  if ((c = left[n]) >= 0) 
  {
    countLL = CountNodes(left[c]);
    countLR = CountNodes(right[c]);
    countL = countLL + countLR + 1;
  }
  else countL = countLL = countLR = 0;
  if ((c = right[n]) >= 0) 
  {
    countRL = CountNodes(left[c]);
    countRR = CountNodes(right[c]);
    countR = countRL + countRR + 1;
  }
  else countR = countRL = countRR = 0;
  
  // Compute balance deltas.
  
  delta = Maths::AbsI(countL - countR);
  deltaL = Maths::AbsI(countRR - 1 - countL - countRL);
  deltaR = Maths::AbsI(countLL - 1 - countR - countLR);
  
  // Optimize balance.
  
  if (deltaL < deltaR && deltaL < delta) Rotate_RL(n, p);
  else if (deltaR < deltaL && deltaR <= delta) Rotate_RR(n, p);
}

/*!
 * @brief  (Re-)balances the tree root node.
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Balance_X()
{
  int32 delta;
  int32 deltaL;
  int32 deltaR;
  int32 countL;
  int32 countR;
  int32 countLL;
  int32 countLR;
  int32 countRL;
  int32 countRR;
  int32 c;
  
  // Compute descendant counts.
  
  if ((c = left[root]) >= 0) 
  {
    countLL = CountNodes(left[c]);
    countLR = CountNodes(right[c]);
    countL = countLL + countLR + 1;
  }
  else countL = countLL = countLR = 0;
  if ((c = right[root]) >= 0) 
  {
    countRL = CountNodes(left[c]);
    countRR = CountNodes(right[c]);
    countR = countRL + countRR + 1;
  }
  else countR = countRL = countRR = 0;
  
  // Compute balance deltas.
  
  delta = Maths::AbsI(countL - countR);
  deltaL = Maths::AbsI(countRR - 1 - countL - countRL);
  deltaR = Maths::AbsI(countLL - 1 - countR - countLR);
  
  // Optimize balance.
  
  if (deltaL < deltaR && deltaL < delta) Rotate_XL();
  else if (deltaR < deltaL && deltaR < delta) Rotate_XR();
}

/*!
 * @brief  Returns the number of nodes in the given subtree.
 * 
 * @param n Root of the subtree.
 * 
 * @return The number of nodes in the subtree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::CountNodes(int32 n)
{
  return n >= 0 ? count[n] : 0;
}

/*!
 * @brief  Creates a new tree node.
 * 
 * @param key The node key.
 * 
 * @return The index of the created tree node.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::CreateNode(typename TKey::In key)
{
  int32 n;
  
  // Grow storage arrays if necessary.
  
  if (free == -1) EnsureCapacity(GetCount() + 1);
  
  // Fetch node from free list.
  
  free = right[n = free];
  
  // Initialize node.
  
  keys[n] = key;
  left[n] = right[n] = -1;
  count[n] = 1;
  
  return n;
}

/*!
 * @brief  Searches the given value and deletes,starting at the given node.
 * 
 * @param n The tree node (left child of \e p ).
 * @param p The parent of \e n .
 * @param key The value to delete.
 * 
 * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::Delete_L(int32 n, int32 p, typename TKey::In key)
{
  int32 idx;
  int32 result;
  
  result = TKey::Compare(key, keys[n]);
  
  if (result < 0) 
  {
    // Search left subtree.
    
    if (left[n] >= 0) 
    {
      if ((idx = Delete_L(left[n], n, key)) >= 0) 
      {
        count[p]--;
        
        Balance_L(n, p);
        
        return idx;
      }
    }
  }
  else if (result > 0) 
  {
    // Search right subtree.
    
    if (right[n] >= 0) 
    {
      if ((idx = Delete_R(right[n], n, key)) >= 0) 
      {
        count[p]--;
        
        Balance_L(n, p);
        
        return idx;
      }
    }
  }
  else 
  {
    // Remove tree node.
    
    Remove_L(n, p);
    
    count[p]--;
    
    return n;
  }
  
  return -1;
}

/*!
 * @brief  Searches the given value and deletes,starting at the given node.
 * 
 * @param n The tree node (right child of \e p ).
 * @param p The parent of \e n .
 * @param key The value to delete.
 * 
 * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::Delete_R(int32 n, int32 p, typename TKey::In key)
{
  int32 idx;
  int32 result;
  
  result = TKey::Compare(key, keys[n]);
  
  if (result < 0) 
  {
    // Search left subtree.
    
    if (left[n] >= 0) 
    {
      if ((idx = Delete_L(left[n], n, key)) >= 0) 
      {
        count[p]--;
        
        Balance_R(n, p);
        
        return idx;
      }
    }
  }
  else if (result > 0) 
  {
    // Search right subtree.
    
    if (right[n] >= 0) 
    {
      if ((idx = Delete_R(right[n], n, key)) >= 0) 
      {
        count[p]--;
        
        Balance_R(n, p);
        
        return idx;
      }
    }
  }
  else 
  {
    // Remove root node.
    
    Remove_R(n, p);
    
    count[p]--;
    
    return n;
  }
  
  return -1;
}

/*!
 * @brief  Searches the given value and deletes,starting from the root node.
 * 
 * @param key The value to delete.
 * 
 * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::Delete_X(typename TKey::In key)
{
  int32 root;
  int32 idx;
  int32 result;
  
  root = this->root;
  result = TKey::Compare(key, keys[root]);
  
  if (result < 0) 
  {
    // Search left subtree.
    
    if (left[root] >= 0) 
    {
      if ((idx = Delete_L(left[root], root, key)) >= 0) 
      {
        Balance_X();
        
        return idx;
      }
    }
  }
  else if (result > 0) 
  {
    // Search right subtree.
    
    if (right[root] >= 0) 
    {
      if ((idx = Delete_R(right[root], root, key)) >= 0) 
      {
        Balance_X();
        
        return idx;
      }
    }
  }
  else 
  {
    // Remove root node.
    
    Remove_X();
    
    return root;
  }
  
  return -1;
}

/*!
 * @brief  Ensures that the set has at least the given capacity.
 * 
 * @param newCapacity The minimum required capacity.
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::EnsureCapacity(int32 newCapacity)
{
  // Compute new conservative capacity value.
  
  newCapacity = Maths::MaxI(capacity * 3 / 2, Maths::MaxI(12, newCapacity));
  
  if (newCapacity <= capacity) return;
  
  // Allocate new storage arrays.
  
  keys = ArrayUtilGeneric<TKey>::GrowTo(keys, capacity, newCapacity);
  values = ArrayUtilGeneric<TValue>::GrowTo(values, capacity, newCapacity);
  left = ArrayUtilGeneric<Prm<int32> >::GrowTo(left, capacity, newCapacity);
  right = ArrayUtilGeneric<Prm<int32> >::GrowTo(right, capacity, newCapacity);
  count = ArrayUtilGeneric<Prm<int32> >::GrowTo(count, capacity, newCapacity);
  
  // Add new storage nodes to free list.
  
  for (int32 i = newCapacity - 1; i >= capacity; i--)
    PushFree(i);
  
  capacity = newCapacity;
}

/*!
 * @brief  Performs a binary search for the given value.
 * 
 * @param n The current node.
 * @param key The value to find.
 * 
 * @return \c true  if the value has been found,\c false  if not.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::FindKey(int32 n, typename TKey::In key)
{
  int32 result;
  
  if (n < 0) return -1;
  
  result = TKey::Compare(key, keys[n]);
  
  if (result < 0) return FindKey(left[n], key);
  if (result > 0) return FindKey(right[n], key);
  
  return n;
}

/*!
 * @brief  Performs a brute-force search for the given value.
 * 
 * @param n The current node.
 * @param value The value to find.
 * 
 * @return \c true  if the value has been found,\c false  if not.
 */
template<class TKey, class TValue>
bool TreeDictionary<TKey, TValue>::FindValue(int32 n, typename TValue::In value)
{
  if (n < 0) return false;
  if (TValue::Equals(value, values[n])) return true;
  
  return FindValue(left[n], value) || FindValue(right[n], value);
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Left child of \e p  or \c null .
 * @param p Left child of \e g .
 * @param g Grand parent of \e n .
 * @param key The key to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::Insert_LL(int32 n, int32 p, int32 g, typename TKey::In key)
{
  if (n >= 0) 
  {
    int32 result;
    int32 idx;
    
    // Perform binary search tree insertion.
    
    result = TKey::Compare(key, keys[n]);
    
    if (result < 0) idx = Insert_LL(left[n], n, p, key);
    else if (result > 0) idx = Insert_LR(right[n], n, p, key);
    else idx = n;
    if (idx < 0) 
    {
      count[n]++;
      
      Balance_L(p, g);
    }
    
    return idx;
  }
  
  // Create new tree node.
  
  n = CreateNode(key);
  left[p] = n;
  
  return -1 - n;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Right child of \e p  or \c null .
 * @param p Left child of \e g .
 * @param g Grand parent of \e n .
 * @param key The key to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::Insert_LR(int32 n, int32 p, int32 g, typename TKey::In key)
{
  if (n >= 0) 
  {
    int32 result;
    int32 idx;
    
    // Perform binary search tree insertion.
    
    result = TKey::Compare(key, keys[n]);
    
    if (result < 0) idx = Insert_RL(left[n], n, p, key);
    else if (result > 0) idx = Insert_RR(right[n], n, p, key);
    else idx = n;
    if (idx < 0) 
    {
      count[n]++;
      
      Balance_L(p, g);
    }
    
    return idx;
  }
  
  // Create new tree node.
  
  n = CreateNode(key);
  right[p] = n;
  
  if (left[p] < 0) Rotate_LL(p, g);
  
  return -1 - n;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Left child of \e p  or \c null .
 * @param p Right child of \e g .
 * @param g Grand parent of \e n .
 * @param key The key to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::Insert_RL(int32 n, int32 p, int32 g, typename TKey::In key)
{
  if (n >= 0) 
  {
    int32 result;
    int32 idx;
    
    // Perform binary search tree insertion.
    
    result = TKey::Compare(key, keys[n]);
    
    if (result < 0) idx = Insert_LL(left[n], n, p, key);
    else if (result > 0) idx = Insert_LR(right[n], n, p, key);
    else idx = n;
    if (idx < 0) 
    {
      count[n]++;
      
      Balance_R(p, g);
    }
    
    return idx;
  }
  
  // Create new tree node.
  
  n = CreateNode(key);
  left[p] = n;
  
  if (right[p] < 0) Rotate_RR(p, g);
  
  return -1 - n;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Right child of \e p  or \c null .
 * @param p Right child of \e g .
 * @param g Grand parent of \e n .
 * @param key The value to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::Insert_RR(int32 n, int32 p, int32 g, typename TKey::In key)
{
  if (n >= 0) 
  {
    int32 result;
    int32 idx;
    
    // Perform binary search tree insertion.
    
    result = TKey::Compare(key, keys[n]);
    
    if (result < 0) idx = Insert_RL(left[n], n, p, key);
    else if (result > 0) idx = Insert_RR(right[n], n, p, key);
    else idx = n;
    if (idx < 0) 
    {
      count[n]++;
      
      Balance_R(p, g);
    }
    
    return idx;
  }
  
  // Create new tree node.
  
  n = CreateNode(key);
  right[p] = n;
  
  return -1 - n;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Left child of #root or \c null .
 * @param key The key to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::Insert_XL(int32 n, typename TKey::In key)
{
  if (n >= 0) 
  {
    int32 result;
    int32 idx;
    
    // Perform binary search tree insertion.
    
    result = TKey::Compare(key, keys[n]);
    
    if (result < 0) idx = Insert_LL(left[n], n, root, key);
    else if (result > 0) idx = Insert_LR(right[n], n, root, key);
    else idx = n;
    if (idx < 0) 
    {
      count[n]++;
      
      Balance_X();
    }
    
    return idx;
  }
  
  // Create new tree node.
  
  n = CreateNode(key);
  left[root] = n;
  
  return -1 - n;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Right child of #root or \c null .
 * @param key The key to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::Insert_XR(int32 n, typename TKey::In key)
{
  if (n >= 0) 
  {
    int32 result;
    int32 idx;
    
    // Perform binary search tree insertion.
    
    result = TKey::Compare(key, keys[n]);
    
    if (result < 0) idx = Insert_RL(left[n], n, root, key);
    else if (result > 0) idx = Insert_RR(right[n], n, root, key);
    else idx = n;
    if (idx < 0) 
    {
      count[n]++;
      
      Balance_X();
    }
    
    return idx;
  }
  
  // Create new tree node.
  
  n = CreateNode(key);
  right[root] = n;
  
  return -1 - n;
}

/*!
 * @brief  Pushes the given storage node to the free list.
 * 
 * @param n The storage node to push.
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::PushFree(int32 n)
{
  right[n] = free;
  free = n;
}

/*!
 * @brief  Removes the given node from the tree.
 * 
 * @param n The node to remove (left child of \e p ).
 * @param p The parent of \e n .
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Remove_L(int32 n, int32 p)
{
  int32 l;
  int32 r;
  int32 c;
  
  l = left[n];
  r = right[n];
  
  if (l >= 0 && r >= 0) 
  {
    // Delete full node.
    
    if (count[l] < count[r]) 
    {
      count[r]--;
      
      Rotate_LL(n, p);
      Remove_L(n, r);
      Balance_L(r, p);
    }
    else 
    {
      count[l]--;
      
      Rotate_LR(n, p);
      Remove_R(n, l);
      Balance_L(l, p);
    }
    
    return;
  }
  if (l < 0 && r < 0) 
  {
    // Delete leaf node.
    
    c = -1;
  }
  else 
  {
    // Delete half node.
    
    c = l < 0 ? r : l;
  }
  
  // Remove node from tree.
  
  left[p] = c;
}

/*!
 * @brief  Removes the given node from the tree.
 * 
 * @param n The node to remove (right child of \e p ).
 * @param p The parent of \e n .
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Remove_R(int32 n, int32 p)
{
  int32 l;
  int32 r;
  int32 c;
  
  l = left[n];
  r = right[n];
  
  if (l >= 0 && r >= 0) 
  {
    // Delete full node.
    
    if (count[l] < count[r]) 
    {
      count[r]--;
      
      Rotate_RL(n, p);
      Remove_L(n, r);
      Balance_R(r, p);
    }
    else 
    {
      count[l]--;
      
      Rotate_RR(n, p);
      Remove_R(n, l);
      Balance_R(l, p);
    }
    
    return;
  }
  if (l < 0 && r < 0) 
  {
    // Delete leaf node.
    
    c = -1;
  }
  else 
  {
    // Delete half node.
    
    c = l < 0 ? r : l;
  }
  
  // Remove node from tree.
  
  right[p] = c;
}

/*!
 * @brief  Removes the root node from the tree.
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Remove_X()
{
  int32 l;
  int32 r;
  int32 c;
  
  l = left[root];
  r = right[root];
  
  if (l >= 0 && r >= 0) 
  {
    // Delete full node.
    
    if (count[l] < count[r]) 
    {
      count[r]--;
      
      Rotate_XL();
      Remove_L(left[r], r);
      Balance_X();
    }
    else 
    {
      count[l]--;
      
      Rotate_XR();
      Remove_R(right[l], l);
      Balance_X();
    }
    
    return;
  }
  if (l < 0 && r < 0) 
  {
    // Delete leaf node.
    
    c = -1;
  }
  else 
  {
    // Delete half node.
    
    c = l < 0 ? r : l;
  }
  
  // Remove node from tree.
  
  root = c;
}

/*!
 * @brief  Updates the node counters for a left rotation on the given node.
 * 
 * <pre>
 *     .          +---+                           +---+        
 *     .     .----| # |----.                 .----| R |
 *     .     |    +---+    |                 |    +---+
 *     .     V             V                 V              
 *     .   +---+         +---+             +---+       
 *     .   | L |    .----| R |  =>    .----| # |----.  
 *     .   +---+    |    +---+        |    +---+    |  
 *     .            V                 V             V          
 *     .          +---+             +---+         +---+        
 *     .          | C |             | L |         | C |        
 *     .          +---+             +---+         +---+        
 *     .   
 *     .   # := The given tree node.
 *     .   L := Left child of # (may exist).
 *     .   R := Right child of # (must exist). 
 *     .   C := Left child of R (may exist).
 * </pre>
 * 
 * @param n The tree node.
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::RotateCount_L(int32 n)
{
  int32 l;
  int32 r;
  int32 rr;
  int32 countL;
  int32 countRR;
  
  l = left[n];
  r = right[n];
  rr = right[r];
  countL = l < 0 ? 0 : count[l];
  countRR = rr < 0 ? 0 : count[rr];
  count[n] -= countRR + 1;
  count[r] += countL + 1;
}

/*!
 * @brief  Updates the node counters for a right rotation on the given node.
 * 
 * <pre>
 *     .          +---+             +---+        
 *     .     .----| # |----.        | L |----.
 *     .     |    +---+    |        +---+    |
 *     .     V             V                 V  
 *     .   +---+         +---+             +---+       
 *     .   | L |----.    | R |  =>    .----| # |----.  
 *     .   +---+    |    +---+        |    +---+    |  
 *     .            V                 V             V          
 *     .          +---+             +---+         +---+        
 *     .          | C |             | C |         | R |        
 *     .          +---+             +---+         +---+        
 *     .   
 *     .   # := The given tree node.
 *     .   L := Left child of # (must exist).
 *     .   R := Right child of # (may exist). 
 *     .   C := Right child of L (may exist).
 * </pre>
 * 
 * @param n The tree node.
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::RotateCount_R(int32 n)
{
  int32 l;
  int32 r;
  int32 ll;
  int32 countR;
  int32 countLL;
  
  l = left[n];
  r = right[n];
  ll = left[l];
  countR = r < 0 ? 0 : count[r];
  countLL = ll < 0 ? 0 : count[ll];
  count[n] -= countLL + 1;
  count[l] += countR + 1;
}

/*!
 * @brief  Performs a left rotation on the given node.
 * 
 * <pre>
 *     .                 +---+                           +---+  
 *     .            .----| P |                      .----| P |  
 *     .            |    +---+                      |    +---+ 
 *     .            V                               V          
 *     .          +---+                           +---+        
 *     .     .----| N |----.                 .----| R |
 *     .     |    +---+    |                 |    +---+
 *     .     V             V    =>           V              
 *     .   +---+         +---+             +---+       
 *     .   | L |    .----| R |        .----| N |----.  
 *     .   +---+    |    +---+        |    +---+    |  
 *     .            V                 V             V          
 *     .          +---+             +---+         +---+        
 *     .          | C |             | L |         | C |        
 *     .          +---+             +---+         +---+        
 *     .   
 *     .   P := Parent of N.
 *     .   N := Left child of P (the given node).
 *     .   L := Left child of N (may exist).
 *     .   R := Right child of N (must exist). 
 *     .   C := Left child of R (may exist).
 * </pre>
 * 
 * @param n Left child of \e p .
 * @param p Parent of \e n .
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Rotate_LL(int32 n, int32 p)
{
  int32 r;
  int32 c;
  
  RotateCount_L(n);
  
  c = left[(r = right[n])];
  right[n] = c;
  left[r] = n;
  left[p] = r;
}

/*!
 * @brief  Performs a right rotation on the given node.
 * 
 * <pre>
 *     .                 +---+             +---+  
 *     .            .----| P |        .----| P |  
 *     .            |    +---+        |    +---+ 
 *     .            V                 V          
 *     .          +---+             +---+        
 *     .     .----| N |----.        | L |----.
 *     .     |    +---+    |        +---+    |
 *     .     V             V    =>           V  
 *     .   +---+         +---+             +---+       
 *     .   | L |----.    | R |        .----| N |----.  
 *     .   +---+    |    +---+        |    +---+    |  
 *     .            V                 V             V          
 *     .          +---+             +---+         +---+        
 *     .          | C |             | C |         | R |        
 *     .          +---+             +---+         +---+        
 *     .   
 *     .   P := Parent of N.
 *     .   N := Left child of P (the given node).
 *     .   L := Left child of N (must exist).
 *     .   R := Right child of N (may exist). 
 *     .   C := Right child of L (may exist).
 * </pre>
 * 
 * @param n Left child of \e p .
 * @param p Parent of \e n .
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Rotate_LR(int32 n, int32 p)
{
  int32 l;
  int32 c;
  
  RotateCount_R(n);
  
  c = right[(l = left[n])];
  left[n] = c;
  right[l] = n;
  left[p] = l;
}

/*!
 * @brief  Performs a left rotation on the given node.
 * 
 * <pre>
 *     .   +---+                           +---+  
 *     .   | P |----.                      | P |----.
 *     .   +---+    |                      +---+    |
 *     .            V                               V          
 *     .          +---+                           +---+        
 *     .     .----| N |----.                 .----| R |
 *     .     |    +---+    |                 |    +---+
 *     .     V             V    =>           V              
 *     .   +---+         +---+             +---+       
 *     .   | L |    .----| R |        .----| N |----.  
 *     .   +---+    |    +---+        |    +---+    |  
 *     .            V                 V             V          
 *     .          +---+             +---+         +---+        
 *     .          | C |             | L |         | C |        
 *     .          +---+             +---+         +---+        
 *     .   
 *     .   P := Parent of N.
 *     .   N := Right child of P (the given node).
 *     .   L := Left child of N (may exist).
 *     .   R := Right child of N (must exist). 
 *     .   C := Left child of R (may exist).
 * </pre>
 * 
 * @param n Right child of \e p .
 * @param p Parent of \e n .
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Rotate_RL(int32 n, int32 p)
{
  int32 r;
  int32 c;
  
  RotateCount_L(n);
  
  c = left[(r = right[n])];
  right[n] = c;
  left[r] = n;
  right[p] = r;
}

/*!
 * @brief  Performs a right rotation on the given node.
 * 
 * <pre>
 *     .   +---+                    +---+  
 *     .   | P |----.               | P |----.
 *     .   +---+    |               +---+    |
 *     .            V                        V          
 *     .          +---+                    +---+        
 *     .     .----| N |----.               | L |----.
 *     .     |    +---+    |               +---+    |
 *     .     V             V    =>                  V  
 *     .   +---+         +---+                    +---+       
 *     .   | L |----.    | R |               .----| N |----.  
 *     .   +---+    |    +---+               |    +---+    |  
 *     .            V                        V             V          
 *     .          +---+                    +---+         +---+        
 *     .          | C |                    | C |         | R |        
 *     .          +---+                    +---+         +---+        
 *     .   
 *     .   P := Parent of N.
 *     .   N := Right child of P (the given node).
 *     .   L := Left child of N (must exist).
 *     .   R := Right child of N (may exist). 
 *     .   C := Right child of L (may exist).
 * </pre>
 * 
 * @param n Right child of \e p .
 * @param p Parent of \e n .
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Rotate_RR(int32 n, int32 p)
{
  int32 l;
  int32 c;
  
  RotateCount_R(n);
  
  c = right[(l = left[n])];
  left[n] = c;
  right[l] = n;
  right[p] = l;
}

/*!
 * @brief  Performs a left rotation on the tree root node.
 * 
 * <pre>
 *     .          +---+                           +---+        
 *     .     .----| N |----.                 .----| R |
 *     .     |    +---+    |                 |    +---+
 *     .     V             V                 V              
 *     .   +---+         +---+             +---+       
 *     .   | L |    .----| R |  =>    .----| N |----.  
 *     .   +---+    |    +---+        |    +---+    |  
 *     .            V                 V             V          
 *     .          +---+             +---+         +---+        
 *     .          | C |             | L |         | C |        
 *     .          +---+             +---+         +---+        
 *     .   
 *     .   N := Tree root node.
 *     .   L := Left child of N (may exist).
 *     .   R := Right child of N (must exist). 
 *     .   C := Left child of R (may exist).
 * </pre>
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Rotate_XL()
{
  int32 r;
  int32 c;
  
  RotateCount_L(root);
  
  c = left[(r = right[root])];
  right[root] = c;
  left[r] = root;
  root = r;
}

/*!
 * @brief  Performs a right rotation on the tree root node.
 * 
 * <pre>
 *     .          +---+             +---+        
 *     .     .----| N |----.        | L |----.
 *     .     |    +---+    |        +---+    |
 *     .     V             V                 V  
 *     .   +---+         +---+             +---+       
 *     .   | L |----.    | R |  =>    .----| N |----.  
 *     .   +---+    |    +---+        |    +---+    |  
 *     .            V                 V             V          
 *     .          +---+             +---+         +---+        
 *     .          | C |             | C |         | R |        
 *     .          +---+             +---+         +---+        
 *     .   
 *     .   N := Tree root node.
 *     .   L := Left child of N (must exist).
 *     .   R := Right child of N (may exist). 
 *     .   C := Right child of L (may exist).
 * </pre>
 */
template<class TKey, class TValue>
void TreeDictionary<TKey, TValue>::Rotate_XR()
{
  int32 l;
  int32 c;
  
  RotateCount_R(root);
  
  c = right[(l = left[root])];
  left[root] = c;
  right[l] = root;
  root = l;
}

/*!
 * @brief  Performs an inorder traversal of the tree and writes the node values into \e array .
 * 
 * @param array The output array.
 * @param node The current node.
 * @param index The current array index.
 * 
 * @return The resulting array index.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::ToEntriesArray(Array<DictionaryEntry<TKey, TValue> > array, int32 node, int32 index)
{
  if (node >= 0) 
  {
    index = ToEntriesArray(array, left[node], index);
    array[index++] = DictionaryEntry<TKey, TValue>(keys[node], values[node]);
    index = ToEntriesArray(array, right[node], index);
  }
  
  return index;
}

/*!
 * @brief  Performs an inorder traversal of the tree and writes the node values into \e array .
 * 
 * @param array The output array.
 * @param node The current node.
 * @param index The current array index.
 * 
 * @return The resulting array index.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::ToKeysArray(Array<typename TKey::Out> array, int32 node, int32 index)
{
  if (node >= 0) 
  {
    index = ToKeysArray(array, left[node], index);
    array[index++] = keys[node];
    index = ToKeysArray(array, right[node], index);
  }
  
  return index;
}

/*!
 * @brief  Performs an inorder traversal of the tree and writes the node values into \e array .
 * 
 * @param array The output array.
 * @param node The current node.
 * @param index The current array index.
 * 
 * @return The resulting array index.
 */
template<class TKey, class TValue>
int32 TreeDictionary<TKey, TValue>::ToValuesArray(Array<typename TValue::Out> array, int32 node, int32 index)
{
  if (node >= 0) 
  {
    index = ToValuesArray(array, left[node], index);
    array[index++] = values[node];
    index = ToValuesArray(array, right[node], index);
  }
  
  return index;
}

} } } 

#endif
