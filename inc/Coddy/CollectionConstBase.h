////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_COLLECTIONCONSTBASE_H
#define CLODDY_CORE_COLLECTIONS_COLLECTIONCONSTBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICollectionConst.h"

// Include referenced classes.

#include "Cloddy/EnumerableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerable; } } }

// Declare class ::Cloddy::Core::Collections::CollectionConstBase.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Abstrace base class for ICollectionConst implementations.
   */
  template<class T>
  class CollectionConstBase : public EnumerableBase<T>, public virtual ICollectionConst<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual bool Contains(typename T::In element) = 0;
    
    virtual bool ContainsAll(IEnumerable<T>* elements);
    
    virtual bool ContainsNone(IEnumerable<T>* elements);
    
    virtual bool ContainsSome(IEnumerable<T>* elements);
    
    virtual Array<typename T::Out> ToArray();
    
    virtual Array<typename T::Out> ToArrayCopy(Array<typename T::Out> array, int32 offset) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CollectionConstBase<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xFFF59B92;
    
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
      if ((ptr = ICollectionConst<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
