////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_VALUES_H
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_VALUES_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class HashDictionary; } } }

// Declare class ::Cloddy::Core::Collections::HashDictionary_Values.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class TKey, class TValue>
  class HashDictionary_Values : public CollectionConstBase<TValue>
  {
    // Declare friend classes.
    
    template<class, class> friend class HashDictionary;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount();
    
    virtual Ptr<IEnumerator<TValue> > GetEnumerator();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual bool Contains(typename TValue::In element);
    
    virtual Array<typename TValue::Out> ToArrayCopy(Array<typename TValue::Out> array, int32 offset);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The owning dictionary.
     */
    Ptr<HashDictionary<TKey, TValue> > dictionary;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of HashDictionary_Values.
     * 
     * @param dictionary The owning dictionary.
     */
    HashDictionary_Values(HashDictionary<TKey, TValue>* dictionary);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HashDictionary_Values<TKey, TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x61661523;
    
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
      if ((ptr = CollectionConstBase<TValue>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
