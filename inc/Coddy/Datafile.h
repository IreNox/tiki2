////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_DATAFILE_H
#define CLODDY_API_DATAFILES_DATAFILE_H

#include "CodeX/System.h"

// Include referenced enumerations.

#include "Cloddy/FileHint.h"

// Include referenced classes.

#include "Cloddy/DatafileBase.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Datafiles { class IDatafile; } } }

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datafiles { class Cache; } } }
namespace Cloddy { namespace API { namespace Datafiles { class Datafile_Cached; } } }
namespace Cloddy { namespace API { namespace Datafiles { class DatafileFactory_Cached; } } }
namespace Cloddy { namespace API { namespace Datafiles { class IoStats; } } }
namespace Cloddy { namespace Core { namespace IO { namespace Files { class Path; } } } }

// Declare class ::Cloddy::API::Datafiles::Datafile.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace Cloddy::Core::IO::Files;
  using namespace CodeX;
  
  /*!
   * @brief  Default implementation of the IDatafile interface that accesses files in the local 
   *         filesystem via the IFile class.
   * 
   * Access to datafiles is performed through a memory cache.The size of the memory cache can be 
   * specified via the static #GetCacheMemory property.All datafiles that are opened resp. created 
   * share the same memory cache object.
   * The memory cache is automatically deleted when all IDatafiles that use it have been disposed.
   * The memory cache is organized into equally sized pages.Data is read from resp. written to disk 
   * for full pages.The used cache page size can be configured via the #GetCachePageSize property 
   * for performance tweaking.
   */
  class Datafile : public DatafileBase
  {
    // Declare friend classes.
    
    friend class Cache;
    friend class Datafile_Cached;
    friend class DatafileFactory_Cached;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The #GetAccessHint to use for opening and creating Datafiles.
     * 
     * The default value is FileHint::FileHint_BufferedSynchronous.
     * 
     * @return The current #GetAccessHint setting.
     * 
     * @see #Create(Path*)
     * @see #Create(Path*,int64)
     * @see #Open
     */
    static FileHint GetAccessHint();
    
    /*!
     * @brief  The #GetAccessHint to use for opening and creating Datafiles.
     * 
     * The default value is FileHint::FileHint_BufferedSynchronous.
     * 
     * @param value The current #GetAccessHint setting.
     * 
     * @see #Create(Path*)
     * @see #Create(Path*,int64)
     * @see #Open
     */
    static void SetAccessHint(FileHint value);
    
    /*!
     * @brief  Amount of memory to use for caching datafile accesses.
     * 
     * Changes made to the #GetCacheMemory or #GetCachePageSize properties will not affect the 
     * caching behaviour of datafiles that have already been opened or created.Only those datafiles 
     * opened resp. created after a change has been made will use the new cache settings.
     * 
     * The default value is \c 32 .
     * 
     * @return <b>[>=1]</b>  The amount of cache memory to use,in megabytes.
     * 
     * @see #Create(Path*)
     * @see #Create(Path*,int64)
     * @see #Open
     */
    static int32 GetCacheMemory();
    
    /*!
     * @brief  Amount of memory to use for caching datafile accesses.
     * 
     * Changes made to the #GetCacheMemory or #GetCachePageSize properties will not affect the 
     * caching behaviour of datafiles that have already been opened or created.Only those datafiles 
     * opened resp. created after a change has been made will use the new cache settings.
     * 
     * The default value is \c 32 .
     * 
     * @param value <b>[>=1]</b>  The amount of cache memory to use,in megabytes.
     * 
     * @see #Create(Path*)
     * @see #Create(Path*,int64)
     * @see #Open
     */
    static void SetCacheMemory(int32 value);
    
    /*!
     * @brief  The size of a single cache page.
     * 
     * Changes made to the #GetCacheMemory or #GetCachePageSize properties will not affect the 
     * caching behaviour of datafiles that have already been opened or created.Only those datafiles 
     * opened resp. created after a change has been made will use the new cache settings.
     * 
     * The default value is \c 16384 .
     * 
     * @return <b>[pow2]</b>  The size of a cache page,in bytes.
     * 
     * @see #Create(Path*)
     * @see #Create(Path*,int64)
     * @see #Open
     */
    static int32 GetCachePageSize();
    
    /*!
     * @brief  The size of a single cache page.
     * 
     * Changes made to the #GetCacheMemory or #GetCachePageSize properties will not affect the 
     * caching behaviour of datafiles that have already been opened or created.Only those datafiles 
     * opened resp. created after a change has been made will use the new cache settings.
     * 
     * The default value is \c 16384 .
     * 
     * @param value <b>[pow2]</b>  The size of a cache page,in bytes.
     * 
     * @see #Create(Path*)
     * @see #Create(Path*,int64)
     * @see #Open
     */
    static void SetCachePageSize(int32 value);
    
    /*!
     * @brief  Global datafile statistics.
     */
    static const StaticPtr<IoStats> CacheStats;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new datafile,overwriting any existing datafile.
     * 
     * The size of the new datafile will be set to \c 0 .
     * 
     * This method uses the DatafileFactory::GetCached datafile factory.
     * 
     * @param filePath <b>[not-null]</b>  File path of the datafile to create.
     * 
     * @return <b>[not-null]</b>  The created IDatafile object.
     */
    static Ptr<IDatafile> Create(Path* filePath);
    
    /*!
     * @brief  Creates a new datafile,overwriting any existing datafile.
     * 
     * This method uses the DatafileFactory::GetCached datafile factory.
     * 
     * @param filePath <b>[not-null]</b>  File path of the datafile to create.
     * @param size <b>[>=0]</b>  The initial size of the datafile,in bytes.
     * 
     * @return <b>[not-null]</b>  The created IDatafile object.
     */
    static Ptr<IDatafile> Create(Path* filePath, int64 size);
    
    /*!
     * @brief  Opens an existing datafile.
     * 
     * This method uses the DatafileFactory::GetCached datafile factory.
     * 
     * @param filePath <b>[not-null]</b>  File path of the datafile to open.
     * @param readOnly Open the datafile as read only?
     * 
     * @return <b>[not-null]</b>  The opened IDatafile object.
     */
    static Ptr<IDatafile> Open(Path* filePath, bool readOnly);

    /*!
     * @brief  Opens an existing datafile through streaming.
     * 
     * This method uses the DatafileFactory::GetCached datafile factory.
     * 
     * @param fileName File name of the datafile to stream.
     * @param host Streaming host or ip.
     * @param port Streaming port.
     * 
     * @return <b>[not-null]</b>  The opened IDatafile object.
     */
    static Ptr<IDatafile> Open(String fileName, String host, int port);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The #GetAccessHint to use for opening and creating Datafiles.
     */
    static FileHint accessHint;
    
    /*!
     * @brief  Amount of memory to use to caching datafile accesses.
     */
    static int32 cacheMemory;
    
    /*!
     * @brief  The size of a single cache page.
     */
    static int32 cachePageSize;
    
    /*!
     * @brief  The current Cache object.
     */
    static Ptr<Cache> currentCache;
    
    // ---------------------------------------------------------------------------------------------
    // Private / Constructors
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Creates a new instance of Datafile.
     */
    Datafile();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Returns the Cache object to use for opening resp. creating datafiles.
     * 
     * @return <b>[not-null]</b>  The Cache object.
     */
    static Ptr<Cache> GetCache();
    
    // ---------------------------------------------------------------------------------------------
    // Static Initializer Functions
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Static initializer function for field CacheStats.
     */
    static Object* StaticInitializer_CacheStats();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Datafile> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x1C68C497;
    
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
      if ((ptr = DatafileBase::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
