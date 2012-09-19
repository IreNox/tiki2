////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_FIELDBUILDER_H
#define CLODDY_CORE_CONFIG_FIELDBUILDER_H

#include "CodeX/System.h"

// Include referenced classes.

#include "Cloddy/ArrayBuilder.hpp"
#include "Cloddy/ConfigProperty.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Config { class IConfigPropertyType; } } }

// Declare class ::Cloddy::Core::Config::FieldBuilder.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced classes.
  
  using Cloddy::Core::Collections::ArrayBuilder;
  
  class FieldBuilder : public ArrayBuilder<Ref<ConfigProperty> >
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of FieldBuilder.
     * 
     * @return <b>[not-null]</b>  The creates FieldBuilder object.
     */
    static Ptr<FieldBuilder> New();
    
    /*!
     * @brief  Adds a new field.
     * 
     * @param name <b>[not-empty]</b>  The field name.
     * @param type <b>[not-null]</b>  The field type.
     * 
     * @return <b>[not-null]</b>  this
     */
    Ptr<FieldBuilder> AddField(String name, IConfigPropertyType* type);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Creates a new instance of FieldBuilder.
     * 
     * @param initialCapacity The initial capacity.
     */
    FieldBuilder(int32 initialCapacity);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<FieldBuilder> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5370E144;
    
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
      if ((ptr = ArrayBuilder<Ref<ConfigProperty> >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
