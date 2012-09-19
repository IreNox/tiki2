////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_ENTRIES_ENUMERATOR_H
#define CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_ENTRIES_ENUMERATOR_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.h"

// Include referenced classes.

#include "Cloddy/EnumeratorBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IDeque; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class TreeDictionary_Entries; } } }

// Declare class ::Cloddy::Core::Collections::TreeDictionary_Entries_Enumerator.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class TKey, class TValue>
  class TreeDictionary_Entries_Enumerator : public EnumeratorBase<Val<DictionaryEntry<TKey, TValue> > >
  {
    // Declare friend classes.
    
    template<class, class> friend class TreeDictionary_Entries;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual DictionaryEntry<TKey, TValue> GetCurrent();
    
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
     * @brief  Index of current tree node.
     */
    int32 current;
    
    /*!
     * @brief  The node keys.
     */
    Array<typename TKey::Out> keys;
    
    /*!
     * @brief  Left child nodes.
     */
    Array<int32> left;
    
    /*!
     * @brief  Index of next tree node.
     */
    int32 next;
    
    /*!
     * @brief  Right child nodes.
     */
    Array<int32> right;
    
    /*!
     * @brief  The traversal stack.
     */
    Ptr<IDeque<Prm<int32> > > stack;
    
    /*!
     * @brief  The node values.
     */
    Array<typename TValue::Out> values;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Tree_Enumerator.
     * 
     * @param root The root node.
     * @param left Left child nodes.
     * @param right Right child nodes.
     * @param keys The node keys.
     * @param values The node values.
     */
    TreeDictionary_Entries_Enumerator(int32 root, Array<int32> left, Array<int32> right, Array<typename TKey::Out> keys, Array<typename TValue::Out> values);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<TreeDictionary_Entries_Enumerator<TKey, TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE224DC8A;
    
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
      if ((ptr = EnumeratorBase<Val<DictionaryEntry<TKey, TValue> > >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
