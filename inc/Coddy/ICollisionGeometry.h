////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_PHYSICS_ICOLLISIONGEOMETRY_H
#define CLODDY_API_PHYSICS_ICOLLISIONGEOMETRY_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Declare interface ::Cloddy::API::Physics::ICollisionGeometry.

namespace Cloddy { namespace API { namespace Physics
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Represents a chunk of static collision geometry that is used by a physics module.
   * 
   * Disposing an ICollisionGeometry object will automatically remove it from the physics 
   * simulation.
   */
  class NO_VTABLE ICollisionGeometry : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Attributes
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Enables or disables this collision geometry chunk in the physics simulation.
     * 
     * @return \c true  to enable the collision geometry,\c false  to disable it.
     */
    virtual bool GetEnabled() = 0;
    
    /*!
     * @brief  Enables or disables this collision geometry chunk in the physics simulation.
     * 
     * @param value \c true  to enable the collision geometry,\c false  to disable it.
     */
    virtual void SetEnabled(bool value) = 0;
    
    /*!
     * @brief  The number of triangles this collision geometry has.
     * 
     * @return <b>[>=0]</b>  The number of triangles.
     */
    virtual int32 GetTriangleCount() = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ICollisionGeometry> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x16F2F2D0;
    
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
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
