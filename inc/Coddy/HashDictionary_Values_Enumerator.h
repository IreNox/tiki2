////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_VALUES_ENUMERATOR_H
#define CLODDY_CORE_COLLECTIONS_HASHDICTIONARY_VALUES_ENUMERATOR_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class HashDictionary_Values; } } }

// Declare class ::Cloddy::Core::Collections::HashDictionary_Values_Enumerator.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class TValue>
  class HashDictionary_Values_Enumerator : public EnumeratorBase<TValue>
  {
    // Declare friend classes.
    
    template<class, class> friend class HashDictionary_Values;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual typename TValue::Out GetCurrent();
    
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
     * @brief  Next pointer of linked node lsit.
     */
    Array<int32> next;
    
    /*!
     * @brief  Index of current node.
     */
    int32 node;
    
    /*!
     * @brief  Mapped values per node.
     */
    Array<typename TValue::Out> values;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    HashDictionary_Values_Enumerator(Array<int32> hashtable, Array<typename TValue::Out> values, Array<int32> next);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<HashDictionary_Values_Enumerator<TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC867F906;
    
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
      if ((ptr = EnumeratorBase<TValue>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
