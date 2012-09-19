////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IMESHVOLUME_H
#define CLODDY_KERNEL_IMESHVOLUME_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMesh.h"

// Declare interface ::Cloddy::Kernel::IMeshVolume.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for CLOD meshes that represent 3D volumetric data.
   */
  class NO_VTABLE IMeshVolume : public virtual IMesh
  {
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IMeshVolume> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x129398B3;
    
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
      if ((ptr = IMesh::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } 

#endif
