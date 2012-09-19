////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_SERIALIZATION_SERIALTYPEINFOS_H
#define CLODDY_CORE_IO_SERIALIZATION_SERIALTYPEINFOS_H

#include "CodeX/System_Native.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class IDictionary; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization { template<class> class SerialTypeInfo; } } } }

// Declare class ::Cloddy::Core::IO::Serialization::SerialTypeInfos.

namespace Cloddy { namespace Core { namespace IO { namespace Serialization
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IDictionary;
  
  class SerialTypeInfos : public virtual Object
  {
    // Declare friend classes.
    
    template<class> friend class SerialTypeInfo;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the ISerialTypeInfo object for the given serializable type.
     * 
     * @param fullName <b>[not-empty]</b>  Full name of the type.
     * 
     * @return <b>[not-null]</b>  The ISerialTypeInfo object.
     * 
     * @exception CoreException If the given type name cannot be resolved.
     */
    static Ptr<ISerialTypeInfo> Get(String fullName);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Mapping from type name resp. type GUIDs to ISerialTypeInfo objects.
     */
    static Ptr<IDictionary<Prm<String>, Ref<ISerialTypeInfo> > > typeInfos;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds the given serial type info to the registry.
     * 
     * @param name The type name.
     * @param guid The type GUID.
     * @param info The serial type info object.
     */
    static void AddSerialTypeInfo(String name, String guid, ISerialTypeInfo* info);
    
    /*!
     * @brief  Returns the ISerialTypeInfo object for the given name.
     * 
     * @param name The type name or GUID.
     * 
     * @return The ISerialTypeInfo object or \c null .
     */
    static Ptr<ISerialTypeInfo> GetSerialTypeInfo(String name);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<SerialTypeInfos> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xB4CD6178;
    
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
