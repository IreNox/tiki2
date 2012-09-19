////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_IENUMERABLE_H
#define CLODDY_CORE_COLLECTIONS_IENUMERABLE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IPredicate; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISet; } } }

// Declare interface ::Cloddy::Core::Collections::IEnumerable.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for collection classes that allow their elements to be enumerated.
   */
  template<class T>
  class NO_VTABLE IEnumerable : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns an enumerator object that returns the elements in this collection.
     * 
     * @return <b>[not-null]</b>  The enumerator object.
     */
    virtual Ptr<IEnumerator<T> > GetEnumerator() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns an IEnumerable object that returns all elements of this enumerable object,
     *         followed by all elements of the given enumerable object.
     * 
     * @param elements <b>[not-null]</b>  The other enumerable object.
     * 
     * @return <b>[not-null]</b>  The resulting enumerable object.
     */
    virtual Ptr<IEnumerable<T> > Concatenate(IEnumerable<T>* elements) = 0;
    
    /*!
     * @brief  Returns an IEnumerable object that returns all elements of this enumerable object 
     *         for which the given predicate evaluates to \c true .
     * 
     * @param predicate <b>[not-null]</b>  The predicate to evaluate for each element.
     * 
     * @return <b>[not-null]</b>  The resulting enumerable object.
     */
    virtual Ptr<IEnumerable<T> > Select(IPredicate<T>* predicate) = 0;
    
    /*!
     * @brief  Returns the elements of this enumerable object as an array.
     * 
     * @return <b>[not-null]</b>  The array of elements.
     */
    virtual Array<typename T::Out> ToArray() = 0;
    
    /*!
     * @brief  Returns the elements of this enumerable object as a list.
     * 
     * @return <b>[not-null]</b>  The list of elements.
     */
    virtual Ptr<IList<T> > ToList() = 0;
    
    /*!
     * @brief  Returns the elements of this enumerable object as a set.
     * 
     * @return <b>[not-null]</b>  The set of elements.
     */
    virtual Ptr<ISet<T> > ToSet() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IEnumerable<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x277DBCDD;
    
    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    protected: virtual void* TryCast(int typeId)
    {
      if (typeId == TypeId) return (void*) this;
      return (void*) 0;
    }
  };
} } } 

#endif
