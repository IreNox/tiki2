////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_KERNEL_ITRIANGULATIONCALLBACK_H
#define CLODDY_KERNEL_ITRIANGULATIONCALLBACK_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "CodeX/IDisposable.h"

// Declare interface ::Cloddy::Kernel::ITriangulationCallback.

namespace Cloddy { namespace Kernel
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  A ITriangulationCallback object consumes the triangle strip that is generated when 
   *         triangulating a CLOD mesh.
   */
  class NO_VTABLE ITriangulationCallback : public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  A triangulation cycle has begun.
     * 
     * @param userData Optional user data object.
     */
    virtual void BeginTriangulation(void* userData) = 0;
    
    /*!
     * @brief  The current triangulation cycle has ended.
     */
    virtual void EndTriangulation() = 0;
    
    /*!
     * @brief  This method is called for each triangle strip generated during triangulation.
     * 
     * @param indices Holds the indices of the generated triangle strip.
     * @param count Number of indices in \e indices .
     * @param min Minimum index value.
     * @param max Maximum index value.
     */
    virtual void TriangleStripChunk(Array<int32> indices, int32 count, int32 min, int32 max) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<ITriangulationCallback> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0x520CEC72;
    
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
} } 

#endif
