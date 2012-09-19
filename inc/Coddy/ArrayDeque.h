////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ARRAYDEQUE_H
#define CLODDY_CORE_COLLECTIONS_ARRAYDEQUE_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/DequeBase.h"

// Declare class ::Cloddy::Core::Collections::ArrayDeque.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the IDeque interface that uses a dynamic array for storing the 
   *         queue elements.
   * 
   * A ArrayDeque container has the following performance characteristics:
   * <pre>
   *     PeekFirst:  O(1)
   *     PeekLast:   O(1)
   *     PopFirst:   O(1)
   *     PopLast:    O(1)
   *     PushFirst:  O(1)
   *     PushLast:   O(1)
   *     n := number of elements in the container.
   * </pre>
   */
  template<class T>
  class ArrayDeque : public DequeBase<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ArrayDeque.
     */
    ArrayDeque();
    
    /*!
     * @brief  Creates a new instance of ArrayDeque.
     * 
     * @param initialCapacity <b>[>=0]</b>  The initial capacity of the deque,in elements.
     */
    ArrayDeque(int32 initialCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual typename T::Out PeekFirst();
    
    virtual typename T::Out PeekLast();
    
    virtual typename T::Out PopFirst();
    
    virtual typename T::Out PopLast();
    
    virtual void PushFirst(typename T::In element);
    
    virtual void PushLast(typename T::In element);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The current capacity of the deque.
     */
    int32 capacity;
    
    /*!
     * @brief  The current number of elements in the deque.
     */
    int32 count;
    
    /*!
     * @brief  Internal storage array for the elements of the deque.
     */
    Array<typename T::Out> elements;
    
    /*!
     * @brief  Index of the head element.
     */
    int32 headIdx;
    
    /*!
     * @brief  Index of the tail elements successor.
     */
    int32 tailIdx;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Grows the internal array.
     */
    void Grow();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ArrayDeque<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD19324C3;
    
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
      if ((ptr = DequeBase<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
