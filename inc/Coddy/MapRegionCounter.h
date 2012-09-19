////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_MAPREGIONCOUNTER_H
#define CLODDY_API_UTIL_MAPREGIONCOUNTER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMapRegionCallback.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace API { namespace Util { class IMapRegion; } } }

// Declare class ::Cloddy::API::Util::MapRegionCounter.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  class MapRegionCounter : public virtual IMapRegionCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    int32 GetRectangleCount();
    
    int64 GetSampleCount();
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Counts the number of rectangular subregions of the given map region.
     * 
     * @param region <b>[not-null]</b>  The map region.
     * 
     * @return <b>[>=0]</b>  The number of subregions.
     */
    static int32 CountRectangles(IMapRegion* region);
    
    /*!
     * @brief  Counts the number of cubemap samples that are covered by the given map region.
     * 
     * @param region <b>[not-null]</b>  The map region.
     * 
     * @return <b>[>=0]</b>  The number of cubemap samples.
     */
    static int64 CountSamples(IMapRegion* region);
    
    virtual void ConsumeMapRegion(int32 face, int32 faceX, int32 faceY, int32 width, int32 height);
    
    /*!
     * @brief  Counts the number of rectangular subregions and the number of covered cubemap 
     *         samples for the given map region.
     * 
     * @param region <b>[not-null]</b>  The map region.
     */
    void Count(IMapRegion* region);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    int32 rectangleCount;
    
    int64 sampleCount;
    
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    MapRegionCounter();
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<MapRegionCounter> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x30105270;
    
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
      if ((ptr = IMapRegionCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } } 

#endif
