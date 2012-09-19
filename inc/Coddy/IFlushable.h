////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_IO_IFLUSHABLE_H
#define CLODDY_CORE_IO_IFLUSHABLE_H

#include "CodeX/System.h"

// Declare interface ::Cloddy::Core::IO::IFlushable.

namespace Cloddy { namespace Core { namespace IO
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  /*!
   * @brief  Base interface for classes that perform caching and provide a flush method.
   * 
   * Usually,implementing classes cache I/O work.However,this interface does not restrict 
   * implementors to cache only read and write accesses.For example,a class may choose to buffer 
   * commands;in this case,flushing will force all buffered commands to be executed.
   */
  class NO_VTABLE IFlushable : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Flushes all cached data.
     * 
     * Performing a flush may result in I/O work.Depending on the semantics of the implementing 
     * class,this work may need to be wrapped in special Begin /End method calls.See the 
     * documentation of the implementing classes for details.
     */
    virtual void Flush() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IFlushable> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDCFA60A6;
    
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
