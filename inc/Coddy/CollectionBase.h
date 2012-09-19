////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_COLLECTIONBASE_H
#define CLODDY_CORE_COLLECTIONS_COLLECTIONBASE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICollection.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerable; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IPredicate; } } }

// Declare class ::Cloddy::Core::Collections::CollectionBase.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Abstrace base class for ICollection implementations.
   */
  template<class T>
  class CollectionBase : public CollectionConstBase<T>, public virtual ICollection<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool Add(typename T::In element) = 0;
    
    virtual bool AddAll(IEnumerable<T>* elements);
    
    virtual void Clear() = 0;
    
    virtual bool Remove(typename T::In element) = 0;
    
    virtual bool RemoveAll(IPredicate<T>* predicate);
    
    virtual bool RemoveAll(IEnumerable<T>* elements);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<CollectionBase<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEABAFE9;
    
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
      if ((ptr = CollectionConstBase<T>::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ICollection<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
