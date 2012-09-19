////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_ENTRIES_H
#define CLODDY_CORE_COLLECTIONS_TREEDICTIONARY_ENTRIES_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.h"

// Include referenced interfaces.

#include "Cloddy/ISetConst.h"

// Include referenced classes.

#include "Cloddy/CollectionConstBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class TreeDictionary; } } }

// Declare class ::Cloddy::Core::Collections::TreeDictionary_Entries.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  template<class TKey, class TValue>
  class TreeDictionary_Entries : public CollectionConstBase<Val<DictionaryEntry<TKey, TValue> > >, public virtual ISetConst<Val<DictionaryEntry<TKey, TValue> > >
  {
    // Declare friend classes.
    
    template<class, class> friend class TreeDictionary;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual int32 GetCount();
    
    virtual Ptr<IEnumerator<Val<DictionaryEntry<TKey, TValue> > > > GetEnumerator();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual bool Contains(const DictionaryEntry<TKey, TValue>& element);
    
    virtual Array<DictionaryEntry<TKey, TValue> > ToArrayCopy(Array<DictionaryEntry<TKey, TValue> > array, int32 offset);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    Ptr<TreeDictionary<TKey, TValue> > dictionary;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    TreeDictionary_Entries(TreeDictionary<TKey, TValue>* dictionary);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<TreeDictionary_Entries<TKey, TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x620D7B75;
    
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
      if ((ptr = CollectionConstBase<Val<DictionaryEntry<TKey, TValue> > >::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ISetConst<Val<DictionaryEntry<TKey, TValue> > >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
