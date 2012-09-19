////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ARRAYLIST_H
#define CLODDY_CORE_COLLECTIONS_ARRAYLIST_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ListBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }

// Declare class ::Cloddy::Core::Collections::ArrayList.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the IList interface that uses a dynamic array for storing the 
   *         list elements.
   * 
   * A ArrayList container has the following performance characteristics:
   * <pre>
   *     Add:         O( 1 )
   *     Clear:       O( 1 )
   *     Contains:    O( n )
   *     GetAt:       O( 1 )
   *     InsertAt:    O( n )
   *     Remove:      O( n )
   *     RemoveAt:    O( n )
   *     RemoveRange: O( n )
   *     SetAt:       O( 1 )
   *     n := number of elements in the container.
   * </pre>
   */
  template<class T>
  class ArrayList : public ListBase<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount();
    
    virtual Ptr<IEnumerator<T> > GetEnumerator();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ArrayList.
     */
    ArrayList();
    
    /*!
     * @brief  Creates a new instance of ArrayList.
     * 
     * @param capacity <b>[>=0]</b>  The initial capacity.
     */
    ArrayList(int32 capacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual bool Add(typename T::In element);
    
    virtual void Clear();
    
    virtual typename T::Out GetAt(int32 index);
    
    virtual int32 IndexOf(typename T::In element);
    
    virtual void InsertAt(int32 index, typename T::In element);
    
    virtual bool Remove(typename T::In element);
    
    virtual typename T::Out RemoveAt(int32 index);
    
    virtual void RemoveRange(int32 index, int32 count);
    
    virtual typename T::Out SetAt(int32 index, typename T::In element);
    
    virtual Array<typename T::Out> ToArrayCopy(Array<typename T::Out> array, int32 offset);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Current capacity of #elements.
     */
    int32 capacity;
    
    /*!
     * @brief  The number of elements in the vector.
     */
    int32 count;
    
    /*!
     * @brief  The internal array for storing elements.
     */
    Array<typename T::Out> elements;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ArrayList<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC7C83299;
    
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
      void* ptr;
      if ((ptr = ListBase<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
