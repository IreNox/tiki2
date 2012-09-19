////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_IUSERDATA_H
#define CLODDY_KERNEL_IUSERDATA_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::Kernel::IUserData.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Classes that allow the user to store application specific information implement this 
   *         interface.
   */
  class NO_VTABLE IUserData : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  The current user data object.
     * 
     * @return The user data object.
     */
    virtual void* GetUserData() = 0;
    
    /*!
     * @brief  The current user data object.
     * 
     * @param value The user data object.
     */
    virtual void SetUserData(void* value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IUserData> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x53F3D7F1;
    
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
