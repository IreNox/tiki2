////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_ICONFIGPROPERTYVALUE_H
#define CLODDY_CORE_CONFIG_ICONFIGPROPERTYVALUE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Config { class ICompositeValue; } } }
namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyType; } } }
namespace Cloddy { namespace Core { namespace Config { class IListValue; } } }

// Declare interface ::Cloddy::Core::Config::IConfigPropertyValue.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent actual property values.
   */
  class NO_VTABLE IConfigPropertyValue : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Accesses this property value,assuming it is convertible to a boolean value.
     * 
     * @return The property value,interpreted as a boolean value.
     */
    virtual bool GetBoolean() = 0;
    
    /*!
     * @brief  Accesses this property value,assuming it is convertible to a boolean value.
     * 
     * @param value The property value,interpreted as a boolean value.
     */
    virtual void SetBoolean(bool value) = 0;
    
    /*!
     * @brief  Accesses this property v alue,assuming it is a composite value (i.e.struct or class).
     * 
     * @return The property value,interpreted as a composite value.
     */
    virtual Ptr<ICompositeValue> GetComposite() = 0;
    
    /*!
     * @brief  Can this property value be interpreted as a boolean value?
     * 
     * @return \c true  if this property value can be interpreted as a boolean value,\c false  if 
     * not.
     * 
     * @see #GetBoolean
     */
    virtual bool IsBoolean() = 0;
    
    /*!
     * @brief  Can this property value be interpreted as a composite value?
     * 
     * @return \c true  if this property value can be interpreted as a composite value,\c false  if 
     * not.
     * 
     * @see #GetComposite
     */
    virtual bool IsComposite() = 0;
    
    /*!
     * @brief  Can this property value be interpreted as a list of values?
     * 
     * @return \c true  if this property value can be interpreted as a list of values,\c false  if 
     * not.
     * 
     * @see #GetList
     */
    virtual bool IsList() = 0;
    
    /*!
     * @brief  Can this property value be interpreted as a number value?
     * 
     * @return \c true  if this property value can be interpreted as a number value,\c false  if 
     * not.
     * 
     * @see #GetNumber
     */
    virtual bool IsNumber() = 0;
    
    /*!
     * @brief  Can this property value be interpreted as a string value?
     * 
     * @return \c true  if this property value can be interpreted as a string value,\c false  if 
     * not.
     * 
     * @see #GetString
     */
    virtual bool IsString() = 0;
    
    /*!
     * @brief  Accesses this property value,assuming it is a list of values.
     * 
     * @return The property value,interpreted as a list of values.
     */
    virtual Ptr<IListValue> GetList() = 0;
    
    /*!
     * @brief  Accesses this property value,assuming it is convertible to a number value.
     * 
     * @return The property value,interpreted as a number.
     */
    virtual float64 GetNumber() = 0;
    
    /*!
     * @brief  Accesses this property value,assuming it is convertible to a number value.
     * 
     * @param value The property value,interpreted as a number.
     */
    virtual void SetNumber(float64 value) = 0;
    
    /*!
     * @brief  Accesses this property value,assuming it is convertible to a string value.
     * 
     * @return The property value,interpreted as a string.
     */
    virtual String GetString() = 0;
    
    /*!
     * @brief  Accesses this property value,assuming it is convertible to a string value.
     * 
     * @param value The property value,interpreted as a string.
     */
    virtual void SetString(String value) = 0;
    
    /*!
     * @brief  Returns the type of this config property value.
     * 
     * @return <b>[not-null]</b>  The type of this property value.
     */
    virtual Ptr<IConfigPropertyType> GetType() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IConfigPropertyValue> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF99FB02A;
    
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
