////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SERIALIZATION_ISTRUCTSERIALIZER_H
#define CLODDY_CORE_IO_SERIALIZATION_ISTRUCTSERIALIZER_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare interface ::Cloddy::Core::IO::Serialization::IStructSerializer.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that perform serialization of struct types.
   */
  template<class T>
  class NO_VTABLE IStructSerializer : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Deserializes a struct value form the given serialization stream.
     * 
     * @param data <b>[not-null]</b>  The serialization stream.
     * 
     * @return The deserialized value.
     */
    virtual typename T::Out Deserialize(Serializer* data) = 0;
    
    /*!
     * @brief  Serializes the given struct value to the serialization stream.
     * 
     * @param value The struct value to serialize.
     * @param data <b>[not-null]</b>  The serialization stream.
     */
    virtual void Serialize(typename T::In value, Serializer* data) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IStructSerializer<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x53C53853;
    
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
} } } } 

#endif
