////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_ICONFIGPROPERTYTYPE_H
#define CLODDY_CORE_CONFIG_ICONFIGPROPERTYTYPE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyValue; } } }

// Declare interface ::Cloddy::Core::Config::IConfigPropertyType.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that represent config property types.
   */
  class NO_VTABLE IConfigPropertyType : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The human-readable name of this property type.
     * 
     * @return <b>[not-null]</b>  The type name.
     */
    virtual String GetName() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new value object for this config property type.
     * 
     * @return <b>[not-null]</b>  The created value object.
     */
    virtual Ptr<IConfigPropertyValue> CreateValue() = 0;
    
    /*!
     * @brief  Checks if this config property type is convertible to the given type,without loss of 
     *         data or precision.
     * 
     * @param other <b>[not-null]</b>  The other config property type.
     * 
     * @return \c true  if this type is assignable to the given one,\c false  if not.
     */
    virtual bool IsConvertibleTo(IConfigPropertyType* other) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IConfigPropertyType> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x88A489D;
    
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
