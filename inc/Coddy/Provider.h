////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_PROVIDER_H
#define CLODDY_KERNEL_PROVIDER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IProvider.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Collections { template<class, class> class IDictionary; } } }

// Declare class ::Cloddy::Kernel::Provider.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IDictionary;
  
  /*!
   * @brief  Default implementation of the IProvider interface.
   * 
   * Multiple Provider objects can be organized in a tree structure.This way,common component can 
   * be provided by Provider objects near the tree root,where specialized components are provided 
   * by leaf nodes.
   */
  class Provider : public virtual IProvider
  {
    // ---------------------------------------------------------------------------------------------
    // Public / Constructors
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Creates a new instance of Provider.
     * 
     * The created Provider instance may contain up to \c 64  components.
     */
    Provider();
    
    /*!
     * @brief  Creates a new instance of Provider.
     * 
     * The created Provider instance may contain up to \c 64  components.
     * 
     * If a component is requested which is not contained in this provider,its parent provider will 
     * be checked.
     * 
     * @param parent <b>[not-null]</b>  The parent provider.
     */
    Provider(IProvider* parent);
    
    // ---------------------------------------------------------------------------------------------
    // Public / Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Adds a component.
     * 
     * @param componentId The component ID.
     * @param component <b>[not-null]</b>  The component.
     * 
     * @return <b>[not-null]</b>  this
     * 
     * @exception CoreException  
     *   - If a parameter is invalid.
     */
    Ptr<Provider> AddComponent(int64 componentId, Object* component);
    
    virtual Ptr<Object> GetComponent(int64 componentId);
    
    virtual Ptr<Object> GetOptionalComponent(int64 componentId);
    
    virtual bool HasComponent(int64 componentId);
    
    /*!
     * @brief  Removes a component.
     * 
     * @param componentId The component ID.
     */
    void RemoveComponent(int64 componentId);
    
    // ---------------------------------------------------------------------------------------------
    // Private / Attributes
    // ---------------------------------------------------------------------------------------------
  private:
    
    /*!
     * @brief  Mapping from component IDs to components.
     */
    Ptr<IDictionary<Prm<int64>, Ref<Object> > > dictionary;
    
    /*!
     * @brief  Optional parent provider.
     */
    Ptr<IProvider> parent;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<Provider> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x5512EB6E;
    
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
      if ((ptr = IProvider::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
  
} } 

#endif
