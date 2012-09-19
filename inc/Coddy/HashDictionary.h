////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_H
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.h"

// Include referenced interfaces.

#include "Cloddy/IDictionary.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ICollectionConst; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class HashDictionary_Entries; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class, class> class HashDictionary_Keys; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class, class> class HashDictionary_Values; } } }

// Declare class ::Cloddy::Core::Collections::HashDictionary.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the IDictionary interface that uses a hashtable for storing the 
   *         key/value pairs.
   */
  template<class TKey, class TValue>
  class HashDictionary : public virtual IDictionary<TKey, TValue>
  {
    // Declare friend classes.
    
    template<class, class> friend class HashDictionary_Entries;
    template<class, class> friend class HashDictionary_Keys;
    template<class, class> friend class HashDictionary_Values;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount();
    
    virtual Ptr<ISetConst<Val<DictionaryEntry<TKey, TValue> > > > GetEntries();
    
    virtual Ptr<ISetConst<TKey> > GetKeys();
    
    virtual Ptr<ICollectionConst<TValue> > GetValues();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of HashDictionary.
     */
    HashDictionary();
    
    /*!
     * @brief  Creates a new instance of HashDictionary.
     * 
     * @param initialCapacity <b>[>=0]</b>  The inhitial capacity of the dictionary,in key/value 
     * pairs.
     */
    HashDictionary(int32 initialCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual void Clear();
    
    virtual bool Contains(typename TKey::In key);
    
    virtual typename TValue::Out Get(typename TKey::In key, typename TValue::In defaultValue);
    
    virtual typename TValue::Out Put(typename TKey::In key, typename TValue::In value);
    
    virtual typename TValue::Out Remove(typename TKey::In key);
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Methods
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Fetches an unused storage node.
     * 
     * @return Index of storage node.
     */
    virtual int32 PopFree();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Number of used hashtable buckets.
     */
    int32 countUsedBuckets;
    
    /*!
     * @brief  Number of used value nodes.
     */
    int32 countUsedNodes;
    
    /*!
     * @brief  Mapping from hash bucket index to index of first value node.
     */
    Array<int32> hashtable;
    
    /*!
     * @brief  Bitmask for computing modulo by bucket count.
     */
    int32 mask;
    
    /*!
     * @brief  Index of first value node in the list of free nodes.
     */
    int32 nodeFree;
    
    /*!
     * @brief  The key of each value node.
     */
    Array<typename TKey::Out> nodeKeys;
    
    /*!
     * @brief  Mapping from value node index to index of next value node in hash bucket.
     */
    Array<int32> nodeNext;
    
    /*!
     * @brief  The value of each value node.
     */
    Array<typename TValue::Out> nodeValues;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Computes a hash value for the given key.
     * 
     * @param key The key value.
     * 
     * @return The hash value.
     */
    static int32 HashCode(typename TKey::In key);
    
    void GrowHashtable();
    
    void GrowNodeStorage();
    
    void PushFree(int32 idx);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HashDictionary<TKey, TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x386F1B10;
    
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
      if ((ptr = IDictionary<TKey, TValue>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
