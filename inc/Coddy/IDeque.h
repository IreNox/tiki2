////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_IDEQUE_H
#define CLODDY_CORE_COLLECTIONS_IDEQUE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IEnumerable.h"

// Declare interface ::Cloddy::Core::Collections::IDeque.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent a double-ended queue of elements.
   */
  template<class T>
  class NO_VTABLE IDeque : public virtual IEnumerable<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of element in this queue.
     * 
     * @return <b>[>=0]</b>  The number of elements in the queue.
     */
    virtual int32 GetCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the first element in the queue without removing it.
     * 
     * @return The first element.
     */
    virtual typename T::Out PeekFirst() = 0;
    
    /*!
     * @brief  Returns the last element in the queue without removing it.
     * 
     * @return The last element.
     */
    virtual typename T::Out PeekLast() = 0;
    
    /*!
     * @brief  Returns the first element in the queue and removes it.
     * 
     * @return The first element.
     */
    virtual typename T::Out PopFirst() = 0;
    
    /*!
     * @brief  Returns the last element in the queue and removes it.
     * 
     * @return The last element.
     */
    virtual typename T::Out PopLast() = 0;
    
    /*!
     * @brief  Prepends the given element to the queue.
     * 
     * @param element The element.
     */
    virtual void PushFirst(typename T::In element) = 0;
    
    /*!
     * @brief  Appends the given element to the queue.
     * 
     * @param element The element.
     */
    virtual void PushLast(typename T::In element) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDeque<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1EE77FF;
    
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
      if ((ptr = IEnumerable<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
