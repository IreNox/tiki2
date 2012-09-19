////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_CORE_PROFILING_IPERFORMANCEVALUE_H
#define CLODDY_CORE_PROFILING_IPERFORMANCEVALUE_H

#include "CodeX/System.h"

// Forward declare referenced interfaces.

namespace Cloddy { namespace Core { namespace Profiling { class IPerformanceValueListener; } } }

// Declare interface ::Cloddy::Core::Profiling::IPerformanceValue.

namespace Cloddy { namespace Core { namespace Profiling
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  class NO_VTABLE IPerformanceValue : public virtual Object
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Returns the most recent performance value.
     * 
     * @return The most recent performance value.
     */
    virtual float64 GetCurrent() = 0;
    
    /*!
     * @brief  Returns the timestamp when the most recent performance value has been reported.
     * 
     * @return The timestamp,in milliseconds.
     * 
     * @see LowLevel::GetTickCount
     */
    virtual int32 GetTimestamp() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief  Registers the given performance value listener.
     * 
     * @param listener <b>[not-null]</b>  The listener to register.
     */
    virtual void AddListener(IPerformanceValueListener* listener) = 0;
    
    /*!
     * @brief  Unregisters the given performance value listener.
     * 
     * @param listener <b>[not-null]</b>  The listener to unregister.
     */
    virtual void RemoveListener(IPerformanceValueListener* listener) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IPerformanceValue> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xDBD85D57;
    
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
