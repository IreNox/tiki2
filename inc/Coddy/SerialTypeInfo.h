////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SERIALIZATION_SERIALTYPEINFO_H
#define CLODDY_CORE_IO_SERIALIZATION_SERIALTYPEINFO_H

#include "CodeX/System_Native.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"
#include "Cloddy/ISerialTypeInfo.h"

// Declare class ::Cloddy::Core::IO::Serialization::SerialTypeInfo.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Provides runtime information about a serializable type.
   */
  template<class T>
  class SerialTypeInfo : public virtual ISerialTypeInfo
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual String GetName();
    
    virtual String GetGuid();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of SerialTypeInfo.
     * 
     * @param name <b>[not-empty]</b>  Name of the type.
     */
    SerialTypeInfo(String name);
    
    /*!
     * @brief  Creates a new instance of SerialTypeInfo.
     * 
     * @param name <b>[not-empty]</b>  Name of the type.
     * @param guid <b>[not-empty]</b>  The type GUID.
     */
    SerialTypeInfo(String name, String guid);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<ISerializable> CreateInstance();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Name of the type.
     */
    String name;
    
    /*!
     * @brief  The type GUID.
     */
    String guid;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SerialTypeInfo<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC175E963;
    
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
      if ((ptr = ISerialTypeInfo::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } } 

#endif
