////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SERIALIZATION_ISERIALIZABLE_H
#define CLODDY_CORE_IO_SERIALIZATION_ISERIALIZABLE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class Serializer; } } } }

// Declare interface ::Cloddy::Core::IO::Serialization::ISerializable.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  A class that supports serialization must implement this interface.
   * 
   * Every solid (ie. non-abstract)class that implements the ISerializable interface \b must  
   * provide a public default constructor.
   */
  class NO_VTABLE ISerializable : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the serial type of this object.
     * 
     * @return <b>[not-null]</b>  The serial type.
     */
    virtual Ptr<ISerialTypeInfo> GetSerialType() = 0;
    
    /*!
     * @brief  Returns the serial data version.
     * 
     * An ISerializable implementation is required to support all versions up to the one returned 
     * by #GetSerialVersion.
     * 
     * @return <b>[>=1]</b>  The serial data version tag.
     * 
     * @see #Serialize
     * @see #Deserialize
     */
    virtual int32 GetSerialVersion() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Initializes the state of this object from the given data stream.
     * 
     * The #Deserialize method will be called immediately after the object has been instantiated 
     * via its default constructor.
     * 
     * The provided \e serialVersion  number is guaranteed to be equal to or less than 
     * the #GetSerialVersion returned by this object (ie. ISerializable object must provide 
     * backwards compatibility).
     * 
     * @param serialVersion <b>[>=1]</b>  The serial data version.
     * @param data <b>[not-null]</b>  The serial data stream.
     * 
     * @return <b>[not-null]</b>  The deserialized object.This will typically be \c this ,but in 
     * some circumstances,another instance may be returned (eg. singletons).
     * 
     * @see #Serialize
     * @see #GetSerialVersion
     */
    virtual Ptr<ISerializable> Deserialize(int32 serialVersion, Serializer* data) = 0;
    
    /*!
     * @brief  Serializes the current state of this object to the given data stream.
     * 
     * @param data <b>[not-null]</b>  The serial data stream.
     * 
     * @see #Deserialize
     * @see #GetSerialVersion
     */
    virtual void Serialize(Serializer* data) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISerializable> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xD1EBF9FD;
    
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
