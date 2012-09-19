////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_PREDICATE_HPP
#define CLODDY_CORE_COLLECTIONS_PREDICATE_HPP

#include "Cloddy/Predicate.h"

// Include referenced interfaces.

#include "Cloddy/ICollectionConst.h"
#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/IPredicate.h"
#include "Cloddy/ISet.h"

// Include referenced classes.

#include "CodeX/ErrorInfo.h"
#include "Cloddy/HashSet.hpp"
#include "CodeX/InvalidArgumentException.h"
#include "Cloddy/Predicate_In.hpp"
#include "Cloddy/PredicateBase.hpp"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

/*!
 * @brief  Returns a predicate that checks if an element is contained in the given set of elements.
 * 
 * @param elements <b>[not-null]</b>  The set of element.
 * 
 * @return <b>[not-null]</b>  The predicate.
 */
template<class T>
Ptr<IPredicate<T> > Predicate<T>::In(IEnumerable<T>* elements)
{
#ifdef _DEBUG
  if (elements == null) throw InvalidArgumentException::NotNull(ZSTRING("Predicate.In"), ZSTRING("elements"));
#endif
  
  Ptr<ISet<T> > temp;
  
  temp = new HashSet<T>(12);
  
  temp->AddAll(elements);
  
  return new Predicate_In<T>(temp);
}

/*!
 * @brief  Returns a predicate that checks if an element is contained in the given set of elements.
 * 
 * @param elements <b>[not-null]</b>  The set of element.
 * 
 * @return <b>[not-null]</b>  The predicate.
 */
template<class T>
Ptr<IPredicate<T> > Predicate<T>::In(ICollectionConst<T>* elements)
{
#ifdef _DEBUG
  if (elements == null) throw InvalidArgumentException::NotNull(ZSTRING("Predicate.In"), ZSTRING("elements"));
#endif
  
  return new Predicate_In<T>(elements);
}

} } } 

#endif
