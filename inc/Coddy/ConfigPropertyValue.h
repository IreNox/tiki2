////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_CONFIGPROPERTYVALUE_H
#define CLODDY_CORE_CONFIG_CONFIGPROPERTYVALUE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IConfigPropertyValue.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Config { class ICompositeValue; } } }
namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyType; } } }
namespace Cloddy { namespace Core { namespace Config { class IListValue; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Config { class ConfigPropertyValue_Boolean; } } }
namespace Cloddy { namespace Core { namespace Config { class ConfigPropertyValue_Class; } } }
namespace Cloddy { namespace Core { namespace Config { class ConfigPropertyValue_List; } } }
namespace Cloddy { namespace Core { namespace Config { class ConfigPropertyValue_Number; } } }
namespace Cloddy { namespace Core { namespace Config { class ConfigPropertyValue_String; } } }
namespace Cloddy { namespace Core { namespace Config { class ConfigPropertyValue_Struct; } } }
namespace CodeX { namespace System { class FailedAssertionException; } }

// Declare class ::Cloddy::Core::Config::ConfigPropertyValue.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using CodeX::System::FailedAssertionException;
  
  /*!
   * @brief  Abstract base class for IConfigPropertyValue implementations.
   */
  class ConfigPropertyValue : public virtual IConfigPropertyValue
  {
    // Declare friend classes.
    
    friend class ConfigPropertyValue_Boolean;
    friend class ConfigPropertyValue_Class;
    friend class ConfigPropertyValue_List;
    friend class ConfigPropertyValue_Number;
    friend class ConfigPropertyValue_String;
    friend class ConfigPropertyValue_Struct;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual bool GetBoolean() = 0;
    
    virtual void SetBoolean(bool value) = 0;
    
    virtual Ptr<ICompositeValue> GetComposite() = 0;
    
    virtual bool IsBoolean();
    
    virtual bool IsComposite();
    
    virtual bool IsList();
    
    virtual bool IsNumber();
    
    virtual bool IsString();
    
    virtual Ptr<IListValue> GetList() = 0;
    
    virtual float64 GetNumber() = 0;
    
    virtual void SetNumber(float64 value) = 0;
    
    virtual String GetString() = 0;
    
    virtual void SetString(String value) = 0;
    
    virtual Ptr<IConfigPropertyType> GetType() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
  private:
    
    static FailedAssertionException IncompatibleType(String source, IConfigPropertyType* type);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ConfigPropertyValue> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xAD358897;
    
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
      if ((ptr = IConfigPropertyValue::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
