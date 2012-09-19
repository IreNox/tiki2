////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_IMAPREGIONCALLBACK_H
#define CLODDY_API_UTIL_IMAPREGIONCALLBACK_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::API::Util::IMapRegionCallback.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that consume map regions.
   */
  class NO_VTABLE IMapRegionCallback : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Consumes the given map region.
     * 
     * @param face The cubemap face on which the map region is located.
     * @param faceX X-coordinate of top-left sample of map region.
     * @param faceY Y-coordinate of top-left sample of map region.
     * @param width Width of map region,in samples.
     * @param height Height of map region,in samples.
     */
    virtual void ConsumeMapRegion(int32 face, int32 faceX, int32 faceY, int32 width, int32 height) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IMapRegionCallback> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x6DE9DE8E;
    
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
