////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_COLLECTIONS_ISORTEDSETCONST_H
#define CLODDY_CORE_COLLECTIONS_ISORTEDSETCONST_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISetConst.h"

// Declare interface ::Cloddy::Core::Collections::ISortedSetConst.

namespace Cloddy { namespace Core { namespace Collections
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for immutable sets that store their elements in order.
   */
  template<class T>
  class NO_VTABLE ISortedSetConst : public virtual ISetConst<T>
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the maximum element of this set.
     * 
     * @return The maximum element.
     */
    virtual typename T::Out GetMaximum() = 0;
    
    /*!
     * @brief  Returns the minimum element of this set.
     * 
     * @return The minimum element.
     */
    virtual typename T::Out GetMinimum() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ISortedSetConst<T> > ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x11333ACF;
    
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
      if ((ptr = ISetConst<T>::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
