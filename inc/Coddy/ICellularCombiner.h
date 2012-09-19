////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PROCEDURAL_ICELLULARCOMBINER_H
#define CLODDY_API_PROCEDURAL_ICELLULARCOMBINER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ISerializable.h"

// Declare interface ::Cloddy::API::Procedural::ICellularCombiner.

namespace Cloddy { namespace API { namespace Procedural
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Core::IO::Serialization::ISerializable;
  
  class NO_VTABLE ICellularCombiner : public virtual ISerializable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    virtual float64 Combine(float64 f1, float64 f2) = 0;
    
    virtual float64 Combine(float64 f1, float64 f2, float64 f3) = 0;
    
    virtual float64 Combine(float64 f1, float64 f2, float64 f3, float64 f4) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICellularCombiner> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xE80B67EF;
    
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
      if ((ptr = ISerializable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
