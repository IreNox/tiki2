////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_CONFIGPROPERTYVALUE_LIST_H
#define CLODDY_CORE_CONFIG_CONFIGPROPERTYVALUE_LIST_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IConfigPropertyValue.h"
#include "Cloddy/IListValue.h"

// Include referenced classes.

#include "Cloddy/ListConstBase.hpp"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class IEnumerator; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class IList; } } }
namespace Cloddy { namespace Core { namespace Config { class ICompositeValue; } } }
namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyType; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Config { class ListType; } } }

// Declare class ::Cloddy::Core::Config::ConfigPropertyValue_List.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IEnumerator;
  using Cloddy::Core::Collections::IList;
  
  // Use referenced classes.
  
  using Cloddy::Core::Collections::ListConstBase;
  
  /*!
   * @brief  Implementation of the IConfigPropertyValue for ListType.
   */
  class ConfigPropertyValue_List : public ListConstBase<Ref<IConfigPropertyValue> >, public virtual IConfigPropertyValue, public virtual IListValue
  {
    // Declare friend classes.
    
    friend class ListType;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool GetBoolean();
    
    virtual void SetBoolean(bool value);
    
    virtual Ptr<ICompositeValue> GetComposite();
    
    virtual int32 GetCount();
    
    virtual Ptr<IEnumerator<Ref<IConfigPropertyValue> > > GetEnumerator();
    
    virtual bool IsBoolean();
    
    virtual bool IsComposite();
    
    virtual bool IsList();
    
    virtual bool IsNumber();
    
    virtual bool IsString();
    
    virtual Ptr<IListValue> GetList();
    
    virtual float64 GetNumber();
    
    virtual void SetNumber(float64 value);
    
    virtual String GetString();
    
    virtual void SetString(String value);
    
    virtual Ptr<IConfigPropertyType> GetType();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IConfigPropertyValue> Add();
    
    virtual Ptr<IConfigPropertyValue> GetAt(int32 index);
    
    virtual int32 IndexOf(IConfigPropertyValue* element);
    
    virtual Ptr<IConfigPropertyValue> InsertAt(int32 index);
    
    virtual void RemoveAt(int32 index);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The list values.
     */
    Ptr<IList<Ref<IConfigPropertyValue> > > listValues;
    
    /*!
     * @brief  The list type.
     */
    Ptr<ListType> type;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ConfigPropertyValue_List.
     * 
     * @param type The list type.
     */
    ConfigPropertyValue_List(ListType* type);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ConfigPropertyValue_List> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2285E7B6;
    
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
      if ((ptr = ListConstBase<Ref<IConfigPropertyValue> >::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IConfigPropertyValue::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IListValue::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
