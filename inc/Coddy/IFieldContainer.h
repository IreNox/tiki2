////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_IFIELDCONTAINER_H
#define CLODDY_CORE_CONFIG_IFIELDCONTAINER_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace Config { class ConfigProperty; } } }

// Declare interface ::Cloddy::Core::Config::IFieldContainer.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that aggregate zero or more fields (i.e.ConfigProperty 
   *         objects).
   */
  class NO_VTABLE IFieldContainer : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the number of contained fields.
     * 
     * @return <b>[>0]</b>  The number of contained fields.
     */
    virtual int32 GetFieldCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns a field of this struct type.
     * 
     * @param idx <b>[0..#GetFieldCount-1]</b>  The field index.
     * 
     * @return <b>[not-null]</b>  The struct field.
     */
    virtual Ptr<ConfigProperty> GetField(int32 idx) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IFieldContainer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6A7CFF09;
    
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
