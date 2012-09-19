////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IVISIBILITYCRITERION_H
#define CLODDY_KERNEL_IVISIBILITYCRITERION_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IMeshCallback.h"

// Declare interface ::Cloddy::Kernel::IVisibilityCriterion.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  An IVisibilityCriterion object decides which vertices of a CLOD mesh shall be visible.
   *         Only visible vertices are included in triangulation.
   * 
   * Each time a CLOD mesh is created via CloddyKernel::CreateMesh,the passed IProvider object must 
   * contain an IVisibilityCriterion object (see ComponentIdsKernel::Req_VisibilityCriterion).
   */
  class NO_VTABLE IVisibilityCriterion : public virtual IMeshCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Computes the visibility for the given vertex.
     * 
     * @param v The vertex.
     * @param g The grand parent vertex.
     * @param a The ancestor vertex.
     * 
     * @return \c true  if the vertex shall be visible,\c false  if not.
     */
    virtual bool ComputeVisibility(int32 v, int32 g, int32 a) = 0;

    /*!
     * @brief  The tolerance value.
     * 
     * @return <b>[>0]</b>  The tolerance.
     */
    virtual float32 GetTolerance() = 0;
    
    /*!
     * @brief  The tolerance value.
     * 
     * @param value <b>[>0]</b>  The tolerance.
     */
    virtual void SetTolerance(float32 value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IVisibilityCriterion> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2AC70D3D;
    
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
      if ((ptr = IMeshCallback::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } 

#endif
