////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_DATAFILEFACTORY_H
#define CLODDY_API_DATAFILES_DATAFILEFACTORY_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IDatafileFactory.h"

// Include referenced classes.

#include "Cloddy/SerializableBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Serialization { class ISerialTypeInfo; } } } }

// Forward declare referenced classes.

namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Datafiles::DatafileFactory.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerialTypeInfo;
  
  // Use referenced classes.
  
  using Cloddy::Core::IO::Files::Path;
  using Cloddy::Core::IO::Serialization::SerializableBase;
  
  class DatafileFactory : public SerializableBase, public virtual IDatafileFactory
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns an IDatafileFactory that produces datafiles that use the internal datafile 
     *         cache.
     * 
     * @return <b>[not-null]</b>  The datafile factory.
     * 
     * @see Datafile::GetAccessHint
     * @see Datafile::GetCacheMemory
     * @see Datafile::GetCachePageSize
     */
    static Ptr<IDatafileFactory> GetCached();
    
    /*!
     * @brief  Returns an IDatafileFactory that produces memory mapped datafiles.
     * 
     * @return <b>[not-null]</b>  The datafile factory.
     */
    static Ptr<IDatafileFactory> GetMapped();
    
    /*!
     * @brief  Returns an IDatafileFactory that produces datafiles that are fully loaded into 
     *         memory.
     * 
     * @return <b>[not-null]</b>  The datafile factory.
     */
    static Ptr<IDatafileFactory> GetMemory();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    virtual Ptr<IDatafileFactory> Chunked(int64 chunkSize);
    
    virtual Ptr<IDatafile> Create(Path* filePath);
    
    virtual Ptr<IDatafile> Create(Path* filePath, int64 initialLength) = 0;
    
    virtual Ptr<IDatafile> Open(Path* filePath, bool readOnly) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Protected / Constructors
    // ---------------------------------------------------------------------------------------------
  protected:
    
    /*!
     * @brief  Creates a new instance of DatafileFactory.
     * 
     * @param serialType <b>[not-null]</b>  The serial type ID.
     */
    DatafileFactory(ISerialTypeInfo* serialType);
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<DatafileFactory> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF70988A7;
    
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
      if ((ptr = SerializableBase::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDatafileFactory::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
