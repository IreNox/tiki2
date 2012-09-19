////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREE_ENUMERATOR_HPP
#define CLODDY_CORE_COLLECTIONS_TREE_ENUMERATOR_HPP

#include "Cloddy/Tree_Enumerator.h"

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

template<class T>
typename T::Out Tree_Enumerator<T>::GetCurrent()
{
  return values[current];
}

// -------------------------------------------------------------------------------------------------
// Protected / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
void Tree_Enumerator<T>::DisposeManaged()
{
  left = null;
  right = null;
  stack = null;
  values = null;
  
  EnumeratorBase<T>::DisposeManaged();
}

template<class T>
bool Tree_Enumerator<T>::DoNext()
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
 * @param values The node values.
 */
template<class T>
Tree_Enumerator<T>::Tree_Enumerator(int32 root, Array<int32> left, Array<int32> right, Array<typename T::Out> values)
{
  // Initialize all primitive fields to default values.
  
  this->current = 0;
  this->next = 0;
  
  try
  {
    this->left = left;
    this->right = right;
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
