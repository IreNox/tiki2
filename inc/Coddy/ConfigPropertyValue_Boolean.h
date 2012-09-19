////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_CONFIGPROPERTYVALUE_BOOLEAN_H
#define CLODDY_CORE_CONFIG_CONFIGPROPERTYVALUE_BOOLEAN_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ConfigPropertyValue.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Config { class ICompositeValue; } } }
namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyType; } } }
namespace Cloddy { namespace Core { namespace Config { class IListValue; } } }

// Declare class ::Cloddy::Core::Config::ConfigPropertyValue_Boolean.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Implementation of the IConfigPropertyValue for BooleanType.
   */
  class ConfigPropertyValue_Boolean : public ConfigPropertyValue
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool GetBoolean();
    
    virtual void SetBoolean(bool value);
    
    virtual Ptr<ICompositeValue> GetComposite();
    
    virtual Ptr<IListValue> GetList();
    
    virtual float64 GetNumber();
    
    virtual void SetNumber(float64 value);
    
    virtual String GetString();
    
    virtual void SetString(String value);
    
    virtual Ptr<IConfigPropertyType> GetType();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The current property value.
     */
    bool value;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    ConfigPropertyValue_Boolean();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ConfigPropertyValue_Boolean> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xEFC39242;
    
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
      return (void*) 0;
    }
  };
  
} } } 

#endif
