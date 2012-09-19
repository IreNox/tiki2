////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_IDICTIONARYCONST_H
#define CLODDY_CORE_COLLECTIONS_IDICTIONARYCONST_H

#include "CodeX/System.h"

// Include referenced structures.

#include "Cloddy/DictionaryEntry.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ICollectionConst; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }

// Declare interface ::Cloddy::Core::Collections::IDictionaryConst.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent a read-only set of key/value pairs.
   */
  template<class TKey, class TValue>
  class NO_VTABLE IDictionaryConst : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of key/value pairs in the map.
     * 
     * @return <b>[>=0]</b>  The number of map entries.
     */
    virtual int32 GetCount() = 0;
    
    /*!
     * @brief  Returns a read-only set of all key/value pairs in this dictionary.
     * 
     * @return <b>[not-null]</b>  The set of key/value pairs.
     */
    virtual Ptr<ISetConst<Val<DictionaryEntry<TKey, TValue> > > > GetEntries() = 0;
    
    /*!
     * @brief  Returns a read-only set of all keys in this dictionary.
     * 
     * @return <b>[not-null]</b>  The set of keys.
     */
    virtual Ptr<ISetConst<TKey> > GetKeys() = 0;
    
    /*!
     * @brief  Returns a read-only collection of all values in this dictionary.
     * 
     * @return <b>[not-null]</b>  The collection of values.
     */
    virtual Ptr<ICollectionConst<TValue> > GetValues() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns if this map contains an entry for the given key.
     * 
     * @param key The key.
     * 
     * @return \c true  if the map contains an entry for the key,\c false  if it does not.
     */
    virtual bool Contains(typename TKey::In key) = 0;
    
    /*!
     * @brief  Returns the value that is currently mapped to the given key.
     * 
     * @param key The key.
     * @param defaultValue The default value to return in case the map does not contain an entry 
     * for \e key .
     * 
     * @return The entry value.
     */
    virtual typename TValue::Out Get(typename TKey::In key, typename TValue::In defaultValue) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDictionaryConst<TKey, TValue> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1F4FB15E;
    
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
      return (void*) 0;
    }
  };
} } } 

#endif
