////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREESET_HPP
#define CLODDY_CORE_COLLECTIONS_TREESET_HPP

#include "Cloddy/TreeSet.h"

// Include referenced enumerations.

#include "CodeX/DisposalPolicy.h"

// Include referenced interfaces.

#include "Cloddy/IDeque.h"
#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/ISet.h"

// Include referenced classes.

#include "Cloddy/ArrayList.hpp"
#include "Cloddy/ArrayUtilGeneric.hpp"
#include "Cloddy/CollectionBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/Maths.h"
#include "Cloddy/Tree_Enumerator.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;
using namespace CodeX::System;

// Use referenced classes.

using Cloddy::Core::Math::Maths;
using Cloddy::Core::System::ArrayUtilGeneric;

// -------------------------------------------------------------------------------------------------
// Public / Attributes
// -------------------------------------------------------------------------------------------------

template<class T>
int32 TreeSet<T>::GetCount()
{
  return CountNodes(root);
}

template<class T>
Ptr<IEnumerator<T> > TreeSet<T>::GetEnumerator()
{
  return new Tree_Enumerator<T>(root, left, right, values);
}

template<class T>
typename T::Out TreeSet<T>::GetMaximum()
{
  int32 next;
  int32 node;
  
  node = -1;
  next = root;
  
  while (next >= 0)
  {
    next = right[node = next];
  }
  
  return node == -1 ? T::Default() : values[node];
}

template<class T>
typename T::Out TreeSet<T>::GetMinimum()
{
  int32 next;
  int32 node;
  
  node = -1;
  next = root;
  
  while (next >= 0)
  {
    next = left[node = next];
  }
  
  return node == -1 ? T::Default() : values[node];
}

// -------------------------------------------------------------------------------------------------
// Public / Constructors
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Creates a new instance of TreeSet.
 */
template<class T>
TreeSet<T>::TreeSet()
{
  // Initialize all primitive fields to default values.
  
  this->capacity = 0;
  this->free = 0;
  this->root = 0;
  
  root = -1;
  free = -1;
}

/*!
 * @brief  Creates a new instance of TreeSet.
 * 
 * @param initialCapacity <b>[>=0]</b>  The initial capacity of the set,in values.
 */
template<class T>
TreeSet<T>::TreeSet(int32 initialCapacity)
{
  // Initialize all primitive fields to default values.
  
  this->capacity = 0;
  this->free = 0;
  this->root = 0;
  
#ifdef _DEBUG
  if (initialCapacity < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("TreeSet.TreeSet"), ZSTRING("initialCapacity"), 0);
#endif
  
  root = -1;
  free = -1;
  
  EnsureCapacity(initialCapacity);
}

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool TreeSet<T>::Add(typename T::In element)
{
  int32 n;
  
  if ((n = root) >= 0) 
  {
    int32 result;
    
    // Perform binary search tree insertion.
    
    result = T::Compare(element, values[n]);
    
    if (result < 0) 
    {
      if (Insert_XL(left[n], element)) 
      {
        count[n]++;
        
        return true;
      }
    }
    else if (result > 0) 
    {
      if (Insert_XR(right[n], element)) 
      {
        count[n]++;
        
        return true;
      }
    }
    
    return false;
  }
  
  // Create new tree node.
  
  root = CreateNode(element);
  
  return true;
}

template<class T>
void TreeSet<T>::Clear()
{
  // Clear root node.
  
  root = -1;
  
  // Add all nodes to the free list.
  
  free = -1;
  
  for (int32 i = capacity - 1; i >= 0; i--)
    PushFree(i);
}

template<class T>
bool TreeSet<T>::Contains(typename T::In element)
{
  return Find(root, element);
}

template<class T>
int32 TreeSet<T>::CountValuesInRange(typename T::In from, typename T::In to)
{
  return CountValuesInRange(root, from, to);
}

template<class T>
Array<typename T::Out> TreeSet<T>::GetValuesInRange(typename T::In from, typename T::In to)
{
  Ptr<IList<T> > list;
  
  list = new ArrayList<T>();
  
  GetValuesInRange(root, from, to, list);
  
  return list->ToArray();
}

template<class T>
bool TreeSet<T>::Remove(typename T::In element)
{
  return root >= 0 && Delete_X(element);
}

template<class T>
typename T::Out TreeSet<T>::RemoveMaximum()
{
  typename T::Out value;
  
  value = GetMaximum();
  
  Remove(value);
  
  return value;
}

template<class T>
typename T::Out TreeSet<T>::RemoveMinimum()
{
  typename T::Out value;
  
  value = GetMinimum();
  
  Remove(value);
  
  return value;
}

template<class T>
Array<typename T::Out> TreeSet<T>::ToArrayCopy(Array<typename T::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("TreeSet.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("TreeSet.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  Array<typename T::Out> temp;
  
  valuesArray = array;
  
  ToArrayInternal(root, offset);
  
  temp = valuesArray;
  valuesArray = null;
  
  return temp;
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
template<class T>
void TreeSet<T>::Balance_L(int32 n, int32 p)
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
template<class T>
void TreeSet<T>::Balance_R(int32 n, int32 p)
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
template<class T>
void TreeSet<T>::Balance_X()
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
template<class T>
int32 TreeSet<T>::CountNodes(int32 n)
{
  return n >= 0 ? count[n] : 0;
}

template<class T>
int32 TreeSet<T>::CountValuesInRange(int32 node, typename T::In from, typename T::In to)
{
  int32 count;
  int32 a;
  int32 b;
  
  if (node == -1) return 0;
  
  a = T::Compare(values[node], from);
  b = T::Compare(values[node], to);
  count = a >= 0 && b < 0 ? 1 : 0;
  
  if (a > 0) count += CountValuesInRange(left[node], from, to);
  if (b < 0) count += CountValuesInRange(right[node], from, to);
  
  return count;
}

/*!
 * @brief  Creates a new tree node.
 * 
 * @param value The node value.
 * 
 * @return The index of the created tree node.
 */
template<class T>
int32 TreeSet<T>::CreateNode(typename T::In value)
{
  int32 n;
  
  // Grow storage arrays if necessary.
  
  if (free == -1) EnsureCapacity(GetCount() + 1);
  
  // Fetch node from free list.
  
  free = right[n = free];
  
  // Initialize node.
  
  values[n] = value;
  left[n] = right[n] = -1;
  count[n] = 1;
  
  return n;
}

/*!
 * @brief  Searches the given value and deletes,starting at the given node.
 * 
 * @param n The tree node (left child of \e p ).
 * @param p The parent of \e n .
 * @param value The value to delete.
 * 
 * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
 */
template<class T>
bool TreeSet<T>::Delete_L(int32 n, int32 p, typename T::In value)
{
  int32 result;
  
  result = T::Compare(value, values[n]);
  
  if (result < 0) 
  {
    // Search left subtree.
    
    if (left[n] >= 0) 
    {
      if (Delete_L(left[n], n, value)) 
      {
        count[p]--;
        
        Balance_L(n, p);
        
        return true;
      }
    }
  }
  else if (result > 0) 
  {
    // Search right subtree.
    
    if (right[n] >= 0) 
    {
      if (Delete_R(right[n], n, value)) 
      {
        count[p]--;
        
        Balance_L(n, p);
        
        return true;
      }
    }
  }
  else 
  {
    // Remove tree node.
    
    Remove_L(n, p);
    
    count[p]--;
    
    return true;
  }
  
  return false;
}

/*!
 * @brief  Searches the given value and deletes,starting at the given node.
 * 
 * @param n The tree node (right child of \e p ).
 * @param p The parent of \e n .
 * @param value The value to delete.
 * 
 * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
 */
template<class T>
bool TreeSet<T>::Delete_R(int32 n, int32 p, typename T::In value)
{
  int32 result;
  
  result = T::Compare(value, values[n]);
  
  if (result < 0) 
  {
    // Search left subtree.
    
    if (left[n] >= 0) 
    {
      if (Delete_L(left[n], n, value)) 
      {
        count[p]--;
        
        Balance_R(n, p);
        
        return true;
      }
    }
  }
  else if (result > 0) 
  {
    // Search right subtree.
    
    if (right[n] >= 0) 
    {
      if (Delete_R(right[n], n, value)) 
      {
        count[p]--;
        
        Balance_R(n, p);
        
        return true;
      }
    }
  }
  else 
  {
    // Remove root node.
    
    Remove_R(n, p);
    
    count[p]--;
    
    return true;
  }
  
  return false;
}

/*!
 * @brief  Searches the given value and deletes,starting from the root node.
 * 
 * @param value The value to delete.
 * 
 * @return \c true  if the value has been deleted,\c false  if it is not contained in the tree.
 */
template<class T>
bool TreeSet<T>::Delete_X(typename T::In value)
{
  int32 root;
  int32 result;
  
  root = this->root;
  result = T::Compare(value, values[root]);
  
  if (result < 0) 
  {
    // Search left subtree.
    
    if (left[root] >= 0) 
    {
      if (Delete_L(left[root], root, value)) 
      {
        Balance_X();
        
        return true;
      }
    }
  }
  else if (result > 0) 
  {
    // Search right subtree.
    
    if (right[root] >= 0) 
    {
      if (Delete_R(right[root], root, value)) 
      {
        Balance_X();
        
        return true;
      }
    }
  }
  else 
  {
    // Remove root node.
    
    Remove_X();
    
    return true;
  }
  
  return false;
}

/*!
 * @brief  Ensures that the set has at least the given capacity.
 * 
 * @param newCapacity The minimum required capacity.
 */
template<class T>
void TreeSet<T>::EnsureCapacity(int32 newCapacity)
{
  // Compute new conservative capacity value.
  
  newCapacity = Maths::MaxI(capacity * 3 / 2, Maths::MaxI(12, newCapacity));
  
  if (newCapacity <= capacity) return;
  
  // Allocate new storage arrays.
  
  values = ArrayUtilGeneric<T>::GrowTo(values, capacity, newCapacity);
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
 * @param value The value to find.
 * 
 * @return \c true  if the value has been found,\c false  if not.
 */
template<class T>
bool TreeSet<T>::Find(int32 n, typename T::In value)
{
  int32 result;
  
  if (n < 0) return false;
  
  result = T::Compare(value, values[n]);
  
  if (result < 0) return Find(left[n], value);
  if (result > 0) return Find(right[n], value);
  
  return true;
}

template<class T>
void TreeSet<T>::GetValuesInRange(int32 node, typename T::In from, typename T::In to, IList<T>* list)
{
  int32 a;
  int32 b;
  
  if (node == -1) return;
  
  a = T::Compare(values[node], from);
  b = T::Compare(values[node], to);
  
  if (a > 0) GetValuesInRange(left[node], from, to, list);
  if (a >= 0 && b < 0) list->Add(values[node]);
  if (b < 0) GetValuesInRange(right[node], from, to, list);
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Left child of \e p  or \c null .
 * @param p Left child of \e g .
 * @param g Grand parent of \e n .
 * @param value The value to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class T>
bool TreeSet<T>::Insert_LL(int32 n, int32 p, int32 g, typename T::In value)
{
  if (n >= 0) 
  {
    int32 result;
    
    // Perform binary search tree insertion.
    
    result = T::Compare(value, values[n]);
    
    if (result < 0) 
    {
      if (Insert_LL(left[n], n, p, value)) 
      {
        count[n]++;
        
        Balance_L(p, g);
        
        return true;
      }
    }
    else if (result > 0) 
    {
      if (Insert_LR(right[n], n, p, value)) 
      {
        count[n]++;
        
        Balance_L(p, g);
        
        return true;
      }
    }
    
    return false;
  }
  
  // Create new tree node.
  
  n = CreateNode(value);
  left[p] = n;
  
  return true;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Right child of \e p  or \c null .
 * @param p Left child of \e g .
 * @param g Grand parent of \e n .
 * @param value The value to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class T>
bool TreeSet<T>::Insert_LR(int32 n, int32 p, int32 g, typename T::In value)
{
  if (n >= 0) 
  {
    int32 result;
    
    // Perform binary search tree insertion.
    
    result = T::Compare(value, values[n]);
    
    if (result < 0) 
    {
      if (Insert_RL(left[n], n, p, value)) 
      {
        count[n]++;
        
        Balance_L(p, g);
        
        return true;
      }
    }
    else if (result > 0) 
    {
      if (Insert_RR(right[n], n, p, value)) 
      {
        count[n]++;
        
        Balance_L(p, g);
        
        return true;
      }
    }
    
    return false;
  }
  
  // Create new tree node.
  
  n = CreateNode(value);
  right[p] = n;
  
  if (left[p] < 0) Rotate_LL(p, g);
  
  return true;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Left child of \e p  or \c null .
 * @param p Right child of \e g .
 * @param g Grand parent of \e n .
 * @param value The value to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class T>
bool TreeSet<T>::Insert_RL(int32 n, int32 p, int32 g, typename T::In value)
{
  if (n >= 0) 
  {
    int32 result;
    
    // Perform binary search tree insertion.
    
    result = T::Compare(value, values[n]);
    
    if (result < 0) 
    {
      if (Insert_LL(left[n], n, p, value)) 
      {
        count[n]++;
        
        Balance_R(p, g);
        
        return true;
      }
    }
    else if (result > 0) 
    {
      if (Insert_LR(right[n], n, p, value)) 
      {
        count[n]++;
        
        Balance_R(p, g);
        
        return true;
      }
    }
    
    return false;
  }
  
  // Create new tree node.
  
  n = CreateNode(value);
  left[p] = n;
  
  if (right[p] < 0) Rotate_RR(p, g);
  
  return true;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Right child of \e p  or \c null .
 * @param p Right child of \e g .
 * @param g Grand parent of \e n .
 * @param value The value to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class T>
bool TreeSet<T>::Insert_RR(int32 n, int32 p, int32 g, typename T::In value)
{
  if (n >= 0) 
  {
    int32 result;
    
    // Perform binary search tree insertion.
    
    result = T::Compare(value, values[n]);
    
    if (result < 0) 
    {
      if (Insert_RL(left[n], n, p, value)) 
      {
        count[n]++;
        
        Balance_R(p, g);
        
        return true;
      }
    }
    else if (result > 0) 
    {
      if (Insert_RR(right[n], n, p, value)) 
      {
        count[n]++;
        
        Balance_R(p, g);
        
        return true;
      }
    }
    
    return false;
  }
  
  // Create new tree node.
  
  n = CreateNode(value);
  right[p] = n;
  
  return true;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Left child of #root or \c null .
 * @param value The value to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class T>
bool TreeSet<T>::Insert_XL(int32 n, typename T::In value)
{
  if (n >= 0) 
  {
    int32 result;
    
    // Perform binary search tree insertion.
    
    result = T::Compare(value, values[n]);
    
    if (result < 0) 
    {
      if (Insert_LL(left[n], n, root, value)) 
      {
        count[n]++;
        
        Balance_X();
        
        return true;
      }
    }
    else if (result > 0) 
    {
      if (Insert_LR(right[n], n, root, value)) 
      {
        count[n]++;
        
        Balance_X();
        
        return true;
      }
    }
    
    return false;
  }
  
  // Create new tree node.
  
  n = CreateNode(value);
  left[root] = n;
  
  return true;
}

/*!
 * @brief  Inserts the given value into the tree.
 * 
 * @param n Right child of #root or \c null .
 * @param value The value to insert.
 * 
 * @return \c true  if the value has been inserted,\c false  if it is already contained in the tree.
 */
template<class T>
bool TreeSet<T>::Insert_XR(int32 n, typename T::In value)
{
  if (n >= 0) 
  {
    int32 result;
    
    // Perform binary search tree insertion.
    
    result = T::Compare(value, values[n]);
    
    if (result < 0) 
    {
      if (Insert_RL(left[n], n, root, value)) 
      {
        count[n]++;
        
        Balance_X();
        
        return true;
      }
    }
    else if (result > 0) 
    {
      if (Insert_RR(right[n], n, root, value)) 
      {
        count[n]++;
        
        Balance_X();
        
        return true;
      }
    }
    
    return false;
  }
  
  // Create new tree node.
  
  n = CreateNode(value);
  right[root] = n;
  
  return true;
}

/*!
 * @brief  Pushes the given storage node to the free list.
 * 
 * @param n The storage node to push.
 */
template<class T>
void TreeSet<T>::PushFree(int32 n)
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
template<class T>
void TreeSet<T>::Remove_L(int32 n, int32 p)
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
template<class T>
void TreeSet<T>::Remove_R(int32 n, int32 p)
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
template<class T>
void TreeSet<T>::Remove_X()
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
template<class T>
void TreeSet<T>::RotateCount_L(int32 n)
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
template<class T>
void TreeSet<T>::RotateCount_R(int32 n)
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
template<class T>
void TreeSet<T>::Rotate_LL(int32 n, int32 p)
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
template<class T>
void TreeSet<T>::Rotate_LR(int32 n, int32 p)
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
template<class T>
void TreeSet<T>::Rotate_RL(int32 n, int32 p)
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
template<class T>
void TreeSet<T>::Rotate_RR(int32 n, int32 p)
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
template<class T>
void TreeSet<T>::Rotate_XL()
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
template<class T>
void TreeSet<T>::Rotate_XR()
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
 * @brief  Performs an inorder traversal of the tree and writes the node values into #valuesArray.
 * 
 * @param node The current node.
 * @param index The current array index.
 * 
 * @return The resulting array index.
 */
template<class T>
int32 TreeSet<T>::ToArrayInternal(int32 node, int32 index)
{
  if (node >= 0) 
  {
    index = ToArrayInternal(left[node], index);
    valuesArray[index++] = values[node];
    index = ToArrayInternal(right[node], index);
  }
  
  return index;
}

} } } 

#endif
