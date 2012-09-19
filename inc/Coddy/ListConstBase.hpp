////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_LISTCONSTBASE_HPP
#define CLODDY_CORE_COLLECTIONS_LISTCONSTBASE_HPP

#include "Cloddy/ListConstBase.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.hpp"
#include "CodeX/ErrorInfo.h"
#include "CodeX/InvalidArgumentException.h"

namespace Cloddy { namespace Core { namespace Collections {

// Use referenced namespaces.

using namespace CodeX;

// Use referenced classes.

using CodeX::System::ErrorInfo;
using CodeX::System::InvalidArgumentException;

// -------------------------------------------------------------------------------------------------
// Public / Methods
// -------------------------------------------------------------------------------------------------

template<class T>
bool ListConstBase<T>::Contains(typename T::In element)
{
  return IndexOf(element) >= 0;
}

template<class T>
Array<typename T::Out> ListConstBase<T>::ToArrayCopy(Array<typename T::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (array == null) throw InvalidArgumentException::NotNull(ZSTRING("ListConstBase.ToArrayCopy"), ZSTRING("array"));
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ListConstBase.ToArrayCopy"), ZSTRING("offset"), 0);
#endif
  
  for (int32 n = this->GetCount(); n > 0; n--)
    array[offset++] = GetAt(n);
  
  return array;
}

} } } 

#endif
