////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_LISTUTILGENERIC_H
#define CLODDY_CORE_COLLECTIONS_LISTUTILGENERIC_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerable; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IListConst; } } }

// Declare class ::Cloddy::Core::Collections::ListUtilGeneric.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Helper class for dealing with arrays and generic lists.
   */
  template<class T>
  class ListUtilGeneric
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns an IListConst object that wraps the given array.
     * 
     * The list will use the given array,no elements will be copied.
     * 
     * @param array The array to wrap.
     * 
     * @return The list object or \c null  if \e array  is \c null .
     */
    static Ptr<IListConst<T> > AsList(Array<typename T::Out> array);
    
    /*!
     * @brief  Consumes all elements in the given enumeration and returns them as an array.
     * 
     * @param enumerable The enumeration.
     * 
     * @return The array or \c null  if \e enumerable  is \c null .
     */
    static Array<typename T::Out> ToArray(IEnumerable<T>* enumerable);
    
    /*!
     * @brief  Copies the given array elements into a new list.
     * 
     * @param array The array.
     * 
     * @return The list or \c null  if \e array  is \c null .
     */
    static Ptr<IList<T> > ToList(Array<typename T::Out> array);
    
    /*!
     * @brief  Copies the given array elements into a new list.
     * 
     * @param array The array.
     * @param offset <b>[>=0]</b>  Index of first element in \e array  to copy.
     * 
     * @return The list or \c null  if \e array  is \c null .
     */
    static Ptr<IList<T> > ToList(Array<typename T::Out> array, int32 offset);
    
    /*!
     * @brief  Copies the given array elements into a new list.
     * 
     * @param array The array.
     * @param offset <b>[>=0]</b>  Index of first element in \e array  to copy.
     * @param count <b>[>=0]</b>  Number of elements to copy.
     * 
     * @return The list or \c null  if \e array  is \c null .
     */
    static Ptr<IList<T> > ToList(Array<typename T::Out> array, int32 offset, int32 count);
    
    /*!
     * @brief  Consumes all elements in the given enumeration and returns them as a list.
     * 
     * @param enumerable The enumeration.
     * 
     * @return The list or \c null  if \e enumerable  is \c null .
     */
    static Ptr<IList<T> > ToList(IEnumerable<T>* enumerable);
  };
  
} } } 

#endif
