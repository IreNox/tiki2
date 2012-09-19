////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_CONFIGPROPERTY_H
#define CLODDY_CORE_CONFIG_CONFIGPROPERTY_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyType; } } }

// Declare class ::Cloddy::Core::Config::ConfigProperty.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Represents a single configuration property.
   */
  class ConfigProperty : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the name of this config property.
     * 
     * @return <b>[not-null]</b>  The property name.
     */
    String GetName();
    
    /*!
     * @brief  Returns the type of this confic property.
     * 
     * @return <b>[not-null]</b>  The config property type.
     */
    Ptr<IConfigPropertyType> GetType();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of ConfigProperty.
     * 
     * @param name <b>[not-empty]</b>  The property name.
     * @param type <b>[not-null]</b>  The property type.
     */
    ConfigProperty(String name, IConfigPropertyType* type);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The property name.
     */
    String name;
    
    /*!
     * @brief  The property type.
     */
    Ptr<IConfigPropertyType> type;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ConfigProperty> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD427F1EC;
    
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
