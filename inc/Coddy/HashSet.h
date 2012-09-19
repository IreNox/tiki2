////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHSET_H
#define CLODDY_CORE_COLLECTIONS_HASHSET_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISet.h"

// Include referenced classes.

#include "Cloddy/CollectionBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }

// Declare class ::Cloddy::Core::Collections::HashSet.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An implementation of the ISet interface that uses a hashtable for storing the set 
   *         elements.
   */
  template<class T>
  class HashSet : public CollectionBase<T>, public virtual ISet<T>
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
     * @brief  Creates a new instance of HashDictionary.
     * 
     * @param initialCapacity <b>[>=0]</b>  The inhitial capacity of the dictionary,in key/value 
     * pairs.
     */
    HashSet(int32 initialCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual bool Add(typename T::In element);
    
    virtual void Clear();
    
    virtual bool Contains(typename T::In element);
    
    virtual bool Remove(typename T::In element);
    
    virtual Array<typename T::Out> ToArrayCopy(Array<typename T::Out> array, int32 offset);
    
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
    Array<typename T::Out> nodeKeys;
    
    /*!
     * @brief  Mapping from value node index to index of next value node in hash bucket.
     */
    Array<int32> nodeNext;
    
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
    static int32 HashCode(typename T::In key);
    
    void GrowHashtable();
    
    void GrowNodeStorage();
    
    /*!
     * @brief  Fetches an unused storage node.
     * 
     * @return Index of storage node.
     */
    int32 PopFree();
    
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
    public: typedef Ptr<HashSet<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEA4A3EE0;
    
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
      if ((ptr = CollectionBase<T>::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ISet<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
