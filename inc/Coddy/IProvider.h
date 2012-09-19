////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IPROVIDER_H
#define CLODDY_KERNEL_IPROVIDER_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::Kernel::IProvider.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Marker interface for Mesh_Terrain user objects that act as providers for CLOD mesh 
   *         specific information that is needed during refinement.
   * 
   * @see ComponentIdsKernel
   * @see CloddyKernel::CreateMesh
   * @see Mesh::GetProvider
   * @see IMeshCallback::BeginMeshAction
   */
  class NO_VTABLE IProvider : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Requests a reference to a component.
     * 
     * @param componentId The ID of the component.
     * 
     * @return <b>[not-null]</b>  The component reference.
     * 
     * @exception CloddyKernelException If the provider does not contain the component.
     */
    virtual Ptr<Object> GetComponent(int64 componentId) = 0;
    
    /*!
     * @brief  Requests a reference to a component.
     * 
     * @param componentId The ID of the component.
     * 
     * @return The component reference or \c null  if this provider does not contain the requested 
     * component..
     */
    virtual Ptr<Object> GetOptionalComponent(int64 componentId) = 0;
    
    /*!
     * @brief  Checks if this provider contains a component.
     * 
     * @param componentId The ID of the component.
     * 
     * @return \c true  if the provider contains the component,\c false  if not.
     */
    virtual bool HasComponent(int64 componentId) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IProvider> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xCC4C2001;
    
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
