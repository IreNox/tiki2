////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_LISTUTILGENERIC_HPP
#define CLODDY_CORE_COLLECTIONS_LISTUTILGENERIC_HPP

#include "Cloddy/ListUtilGeneric.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"
#include "Cloddy/IEnumerator.h"
#include "Cloddy/IList.h"
#include "Cloddy/IListConst.h"
#include "Cloddy/ISet.h"

// Include referenced classes.

#include "Cloddy/ArrayList.hpp"
#include "Cloddy/ArrayList_Wrap.hpp"
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

/*!
 * @brief  Returns an IListConst object that wraps the given array.
 * 
 * The list will use the given array,no elements will be copied.
 * 
 * @param array The array to wrap.
 * 
 * @return The list object or \c null  if \e array  is \c null .
 */
template<class T>
Ptr<IListConst<T> > ListUtilGeneric<T>::AsList(Array<typename T::Out> array)
{
  if (array == null) return null;
  
  return new ArrayList_Wrap<T>(array);
}

/*!
 * @brief  Consumes all elements in the given enumeration and returns them as an array.
 * 
 * @param enumerable The enumeration.
 * 
 * @return The array or \c null  if \e enumerable  is \c null .
 */
template<class T>
Array<typename T::Out> ListUtilGeneric<T>::ToArray(IEnumerable<T>* enumerable)
{
  if (enumerable == null) return null;
  
  return ToList(enumerable)->ToArray();
}

/*!
 * @brief  Copies the given array elements into a new list.
 * 
 * @param array The array.
 * 
 * @return The list or \c null  if \e array  is \c null .
 */
template<class T>
Ptr<IList<T> > ListUtilGeneric<T>::ToList(Array<typename T::Out> array)
{
  if (array == null) return null;
  
  return ToList(array, 0, array.Length());
}

/*!
 * @brief  Copies the given array elements into a new list.
 * 
 * @param array The array.
 * @param offset <b>[>=0]</b>  Index of first element in \e array  to copy.
 * 
 * @return The list or \c null  if \e array  is \c null .
 */
template<class T>
Ptr<IList<T> > ListUtilGeneric<T>::ToList(Array<typename T::Out> array, int32 offset)
{
#ifdef _DEBUG
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ListUtilGeneric.ToList"), ZSTRING("offset"), 0);
#endif
  
  if (array == null) return null;
  
  return ToList(array, offset, array.Length() - offset);
}

/*!
 * @brief  Copies the given array elements into a new list.
 * 
 * @param array The array.
 * @param offset <b>[>=0]</b>  Index of first element in \e array  to copy.
 * @param count <b>[>=0]</b>  Number of elements to copy.
 * 
 * @return The list or \c null  if \e array  is \c null .
 */
template<class T>
Ptr<IList<T> > ListUtilGeneric<T>::ToList(Array<typename T::Out> array, int32 offset, int32 count)
{
#ifdef _DEBUG
  if (offset < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ListUtilGeneric.ToList"), ZSTRING("offset"), 0);
  if (count < 0) throw InvalidArgumentException::GreaterEqual(ZSTRING("ListUtilGeneric.ToList"), ZSTRING("count"), 0);
#endif
  
  Ptr<IList<T> > list;
  
  if (array == null) return null;
  
  list = new ArrayList<T>(count);
  
  while (count-- > 0)
  {
    list->Add(array[offset++]);
  }
  
  return list;
}

/*!
 * @brief  Consumes all elements in the given enumeration and returns them as a list.
 * 
 * @param enumerable The enumeration.
 * 
 * @return The list or \c null  if \e enumerable  is \c null .
 */
template<class T>
Ptr<IList<T> > ListUtilGeneric<T>::ToList(IEnumerable<T>* enumerable)
{
  Ptr<IList<T> > list;
  
  if (enumerable == null) return null;
  
  list = new ArrayList<T>();
  
  for (Ptr<IEnumerator<T> > it = enumerable->GetEnumerator(); it->Next(); )
    list->Add(it->GetCurrent());
  
  return list;
}

} } } 

#endif
