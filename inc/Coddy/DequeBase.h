////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_DEQUEBASE_H
#define CLODDY_CORE_COLLECTIONS_DEQUEBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IDeque.h"

// Include referenced classes.

#include "Cloddy/EnumerableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }

// Declare class ::Cloddy::Core::Collections::DequeBase.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class T>
  class DequeBase : public EnumerableBase<T>, public virtual IDeque<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount() = 0;
    
    virtual Ptr<IEnumerator<T> > GetEnumerator();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual typename T::Out PeekFirst() = 0;
    
    virtual typename T::Out PeekLast() = 0;
    
    virtual typename T::Out PopFirst() = 0;
    
    virtual typename T::Out PopLast() = 0;
    
    virtual void PushFirst(typename T::In element) = 0;
    
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
    public: typedef Ptr<DequeBase<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5C13E8C7;
    
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
      if ((ptr = EnumerableBase<T>::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDeque<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
