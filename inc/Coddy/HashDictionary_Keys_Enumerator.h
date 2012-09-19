////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_KEYS_ENUMERATOR_H
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_KEYS_ENUMERATOR_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class HashDictionary_Keys; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class HashSet; } } }

// Declare class ::Cloddy::Core::Collections::HashDictionary_Keys_Enumerator.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class TKey>
  class HashDictionary_Keys_Enumerator : public EnumeratorBase<TKey>
  {
    // Declare friend classes.
    
    template<class, class> friend class HashDictionary_Keys;
    template<class> friend class HashSet;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual typename TKey::Out GetCurrent();
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    virtual void DisposeManaged();
    
    virtual bool DoNext();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Index of next hashtable bucket to visit.
     */
    int32 bucket;
    
    /*!
     * @brief  The hashtable buckets.
     */
    Array<int32> hashtable;
    
    /*!
     * @brief  Key values per node.
     */
    Array<typename TKey::Out> keys;
    
    /*!
     * @brief  Next pointer of linked node lsit.
     */
    Array<int32> next;
    
    /*!
     * @brief  Index of current node.
     */
    int32 node;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    HashDictionary_Keys_Enumerator(Array<int32> hashtable, Array<typename TKey::Out> keys, Array<int32> next);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HashDictionary_Keys_Enumerator<TKey> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x237115F4;
    
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
      if ((ptr = EnumeratorBase<TKey>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
