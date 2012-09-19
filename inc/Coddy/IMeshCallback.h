////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IMESHCALLBACK_H
#define CLODDY_KERNEL_IMESHCALLBACK_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IProvider; } }

// Declare interface ::Cloddy::Kernel::IMeshCallback.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  During mesh refinement and traversal,an IMeshCallback is notified each time a mesh 
   *         action is about to be performed.
   */
  class NO_VTABLE IMeshCallback : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  A mesh action (refinement or traversal)is about to begin.
     * 
     * @param provider The IProvider object of the CLOD mesh.
     */
    virtual void BeginMeshAction(IProvider* provider) = 0;
    
    /*!
     * @brief  The mesh action has just finished.
     */
    virtual void EndMeshAction() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IMeshCallback> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x605F4E28;
    
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
} } 

#endif
