////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IREFINEMENTCALLBACK_H
#define CLODDY_KERNEL_IREFINEMENTCALLBACK_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Kernel { class IRefinementProgress; } }

// Declare interface ::Cloddy::Kernel::IRefinementCallback.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that receive callbacks for CLOD mesh refinement events.
   */
  class NO_VTABLE IRefinementCallback : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The refinement has finished.
     * 
     * This method is called when the background refinement has reached an optimal mesh structure,
     * as depicted by the configured IVisibilityCriterion.
     * 
     * @param source <b>[not-null]</b>  The source object.
     */
    virtual void RefinementFinished(IRefinementProgress* source) = 0;
    
    /*!
     * @brief  The refinement has started.
     * 
     * This method is called when the background refinement has started by the current mesh 
     * structure is no longer optimal according to the configured IVisibilityCriterion.
     * 
     * @param source <b>[not-null]</b>  The source object.
     */
    virtual void RefinementStarted(IRefinementProgress* source) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IRefinementCallback> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7FC88070;
    
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
