////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_THREADING_ITHREADCONTEXT_H
#define CLODDY_CORE_THREADING_ITHREADCONTEXT_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::Core::Threading::IThreadContext.

namespace Cloddy { namespace Core { namespace Threading
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that provide context information for a main method of a 
   *         background thread.
   */
  class NO_VTABLE IThreadContext : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the parameter object that has been specified when the thread has been 
     *         started.
     * 
     * @return The parameter object or \c null .
     */
    virtual Ptr<Object> GetParameter() = 0;
    
    /*!
     * @brief  Shall the thread terminate gracefully?
     * 
     * @return \c true  if the thread shall terminate as soon as possible,\c false  if not.
     */
    virtual bool ShallQuit() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IThreadContext> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x3B026BF9;
    
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
