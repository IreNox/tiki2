////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_CONFIGPROPERTYVALUE_CLASS_H
#define CLODDY_CORE_CONFIG_CONFIGPROPERTYVALUE_CLASS_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICompositeValue.h"

// Include referenced classes.

#include "Cloddy/ConfigPropertyValue.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class> class ICollectionConst; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class, class> class IDictionary; } } }
namespace Cloddy { namespace Core { namespace Collections { template<class> class ISetConst; } } }
namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyType; } } }
namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyValue; } } }
namespace Cloddy { namespace Core { namespace Config { class IListValue; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Config { class ClassType; } } }

// Declare class ::Cloddy::Core::Config::ConfigPropertyValue_Class.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::ICollectionConst;
  using Cloddy::Core::Collections::IDictionary;
  using Cloddy::Core::Collections::ISetConst;
  
  /*!
   * @brief  Implementation of the IConfigPropertyValue for ClassType.
   */
  class ConfigPropertyValue_Class : public ConfigPropertyValue, public virtual ICompositeValue
  {
    // Declare friend classes.
    
    friend class ClassType;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool GetBoolean();
    
    virtual void SetBoolean(bool value);
    
    virtual Ptr<ICompositeValue> GetComposite();
    
    virtual int32 GetCount();
    
    virtual Ptr<ISetConst<Prm<String> > > GetFieldNames();
    
    virtual Ptr<ICollectionConst<Ref<IConfigPropertyValue> > > GetFieldValues();
    
    virtual Ptr<IListValue> GetList();
    
    virtual float64 GetNumber();
    
    virtual void SetNumber(float64 value);
    
    virtual String GetString();
    
    virtual void SetString(String value);
    
    virtual Ptr<IConfigPropertyType> GetType();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    bool Contains(String key);
    
    Ptr<IConfigPropertyValue> Get(String key, IConfigPropertyValue* defaultValue);
    
    virtual Ptr<IConfigPropertyValue> GetField(String name);
    
    virtual bool HasField(String name);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The field values.
     */
    Ptr<IDictionary<Prm<String>, Ref<IConfigPropertyValue> > > fieldValues;
    
    /*!
     * @brief  The class type.
     */
    Ptr<ClassType> type;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ConfigPropertyValue_Class.
     * 
     * @param type The class type.
     */
    ConfigPropertyValue_Class(ClassType* type);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    static void AssertNotNull(String name, IConfigPropertyValue* value);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ConfigPropertyValue_Class> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE61B1342;
    
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
      if ((ptr = ConfigPropertyValue::TryCast(typeId)) != 0) return ptr;
      if ((ptr = ICompositeValue::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
