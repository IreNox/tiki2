////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_DATAFILES_IOSTATS_H
#define CLODDY_API_DATAFILES_IOSTATS_H

#include "CodeX/System.h"

// Forward declare referenced classes.

namespace Cloddy { namespace API { namespace Datafiles { class Cache; } } }
namespace Cloddy { namespace API { namespace Datafiles { class Datafile_Cached; } } }
namespace Cloddy { namespace API { namespace Datafiles { class Datafile_Mapped; } } }
namespace Cloddy { namespace API { namespace Datafiles { class Datafile_Memory; } } }

// Declare class ::Cloddy::API::Datafiles::IoStats.

namespace Cloddy { namespace API { namespace Datafiles
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Provides information about performed I/O.
   */
  class IoStats : public virtual Object
  {
    // Declare friend classes.
    
    friend class Cache;
    friend class Datafile_Cached;
    friend class Datafile_Mapped;
    friend class Datafile_Memory;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The number of bytes that have been read from the persistent store.
     * 
     * @return <b>[>=0]</b>  The number of read bytes.
     */
    int64 GetBytesRead();
    
    /*!
     * @brief  The number of bytes that have been transferred from/to the persistent store.
     * 
     * @return <b>[>=0]</b>  The number of transferred bytes.
     */
    int64 GetBytesTransferred();
    
    /*!
     * @brief  The number of bytes that have been written to the persistent store.
     * 
     * @return <b>[>=0]</b>  The number of written bytes.
     */
    int64 GetBytesWritten();
    
    /*!
     * @brief  Returns the fit ratio of this cache.
     * 
     * The fit ratio depicts the probability that a read/write access falls inside the boundaries 
     * of a single cache page.
     * 
     * The cache fit ratio should be 95%or higher.If not,the cache page size can be increased (
     * see Datafile::GetCachePageSize).
     * 
     * @return <b>[0..100]</b>  The fit ratio,in percent.
     */
    float32 GetFitRatio();
    
    /*!
     * @brief  Returns the hit ratio of this cache.
     * 
     * The hit ratio depicts the probability that a read/write access can be satisfied directly 
     * from the cache.
     * 
     * The cache hit ratio should be 95%or higher.If not,the cache memory can be increased (
     * see Datafile::GetCacheMemory).
     * 
     * @return <b>[0..100]</b>  The hit ratio,in percent.
     */
    float32 GetHitRatio();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Resets the byte counters.
     */
    void Reset();
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  The number of bytes that have been read from the persistent store.
     */
    int64 bytesRead;
    
    /*!
     * @brief  The number of bytes that have been written to the persistent store.
     */
    int64 bytesWritten;
    
    /*!
     * @brief  Counts datafile accesses that fall within cache page boundaries.
     */
    int64 pageFitCount;
    
    /*!
     * @brief  Counts datafile accesses that can be served from cache pages.
     */
    int64 pageHitCount;
    
    /*!
     * @brief  Counts datafile accesses that require cache page swapping from disk.
     */
    int64 pageMissCount;
    
    /*!
     * @brief  Counts datafile accesses that straddle cache page boundaries.
     */
    int64 pageNoFitCount;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    IoStats();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IoStats> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5A51BE1E;
    
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
