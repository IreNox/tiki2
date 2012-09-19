////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PROFILING_IPERFORMANCEVARIABLE_H
#define CLODDY_CORE_PROFILING_IPERFORMANCEVARIABLE_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/IPerformanceValue.h"

// Declare interface ::Cloddy::Core::Profiling::IPerformanceVariable.

namespace Cloddy { namespace Core { namespace Profiling
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  class NO_VTABLE IPerformanceVariable : public virtual IPerformanceValue
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual void ReportValue(float64 value) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IPerformanceVariable> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x7A454B3E;
    
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
      if ((ptr = IPerformanceValue::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
