////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_HEIGHTMAPS_IDIRTYREGIONCALLBACK_H
#define CLODDY_API_HEIGHTMAPS_IDIRTYREGIONCALLBACK_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::API::Heightmaps::IDirtyRegionCallback.

namespace Cloddy { namespace API { namespace Heightmaps
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  This interface defines callback methods that can be used to keep track of dirty 
   *         regions when modifying heightmap regions.
   * 
   * For each call of the IHeightmap::MarkAsDirty method,the #MarkAsDirty method of the callback is 
   * invoked on the specified callback object.
   */
  class NO_VTABLE IDirtyRegionCallback : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  A region of a cubemap heightmap has been modified.
     * 
     * @param faceX Cubemap face X-coordinate of top-left corner of modified region.
     * @param faceY Cubemap face Y-coordinate of top-left corner of modified region.
     * @param face Cubemap face of modified region (see constants of Cubemap class).
     * @param width Width of modified region,in heightmap samples.
     * @param height Height of modified region,in heightmap samples.
     */
    virtual void MarkAsDirty(int32 faceX, int32 faceY, int32 face, int32 width, int32 height) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IDirtyRegionCallback> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xF2CA5EC;
    
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
