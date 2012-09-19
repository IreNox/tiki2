////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_CONFIG_ILISTVALUE_H
#define CLODDY_CORE_CONFIG_ILISTVALUE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IConfigPropertyValue.h"
#include "Cloddy/IListConst.h"

// Declare interface ::Cloddy::Core::Config::IListValue.

namespace Cloddy { namespace Core { namespace Config
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::Collections::IListConst;
  
  class NO_VTABLE IListValue : public virtual IListConst<Ref<IConfigPropertyValue> >
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Adds the given element to this collection..
     * 
     * @return <b>[not-null]</b>  The added value.
     */
    virtual Ptr<IConfigPropertyValue> Add() = 0;
    
    /*!
     * @brief  Inserts the given element into the list.
     * 
     * @param index <b>[0..ICollectionConst::GetCount]</b>  List index where to insert the element.
     * 
     * @return <b>[not-null]</b>  The inserted value.
     */
    virtual Ptr<IConfigPropertyValue> InsertAt(int32 index) = 0;
    
    /*!
     * @brief  Removes the element at the given list index.
     * 
     * @param index <b>[0..ICollectionConst::GetCount-1]</b>  The list index.
     * 
     * @return The removed element.
     */
    virtual void RemoveAt(int32 index) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IListValue> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x98490925;
    
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
      if ((ptr = IListConst<Ref<IConfigPropertyValue> >::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
