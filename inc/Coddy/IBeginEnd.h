////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_UTIL_IBEGINEND_H
#define CLODDY_API_UTIL_IBEGINEND_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::API::Util::IBeginEnd.

namespace Cloddy { namespace API { namespace Util
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that exhibit a begin/end semantic.
   * 
   * Various components of the CloddySDK perform fine grained operations like reading individual 
   * dataset samples from datafiles or computing vertex data from heightmap samples.
   * Since the CloddySDK has a multithreaded design (render thread,refinement thread and/or compute 
   * thread),synchronization is necessary.
   * In order to reduce the synchronization overhead,these components use a begin/end semantic:A 
   * sequence of fine grained operations is grouped into a single bulk access and the #Begin 
   * and #End method are used to mark the scope of the access.
   * Synchronization is then performed on bulk accesses only and not on individual fine grained 
   * operations,which reduces the overhead for synchronization.
   */
  class NO_VTABLE IBeginEnd : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Begins an access to this object.
     * 
     * See the documentation of the class which implements this interface for details on the 
     * operations that must be wrapped in #Begin /#End calls.
     */
    virtual void Begin() = 0;
    
    /*!
     * @brief  Ends the current access to this object.
     * 
     * See the documentation of the class which implements this interface for details on the 
     * operations that must be wrapped in #Begin /#End calls.
     */
    virtual void End() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IBeginEnd> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x2ADC9735;
    
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
