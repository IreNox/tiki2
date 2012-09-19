////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_API_RENDERING_IINDEXBUFFER_H
#define CLODDY_API_RENDERING_IINDEXBUFFER_H

#include "CodeX/System.h"

// Include referenced interfaces.

#include "Cloddy/ICapacity.h"
#include "CodeX/IDisposable.h"

// Declare interface ::Cloddy::API::Rendering::IIndexBuffer.

namespace Cloddy { namespace API { namespace Rendering
{
  // Use referenced namespaces.
  
  using namespace CodeX;
  
  // Use referenced interfaces.
  
  using Cloddy::Kernel::ICapacity;
  using CodeX::System::IDisposable;
  
  /*!
   * @brief  Base interface for classes that represent index buffers for rendering geometry.
   * 
   * An IIndexBuffer object always stores 32-bit indices.
   */
  class NO_VTABLE IIndexBuffer : public virtual ICapacity, public virtual IDisposable
  {
    // ---------------------------------------------------------------------------------------------
    // Methods
    // ---------------------------------------------------------------------------------------------
  public:
    
    /*!
     * @brief  Updates a range of indices in the buffer.TODO:Add userData Parameter!
     * 
     * @param bufferIndex <b>[>=0]</b>  Index of the first index buffer element to update.
     * @param indices <b>[not-null]</b>  An array holding the updated indices.
     * @param indicesOffset <b>[>=0]</b>  Offset into \e indices  to first index to read.
     * @param indicesCount <b>[>=0]</b>  Total number of indices to read from \e indices .
     */
    virtual void SetIndices(int32 bufferIndex, Array<int32> indices, int32 indicesOffset, int32 indicesCount) = 0;
    
    // ---------------------------------------------------------------------------------------------
    // Metadata
    // ---------------------------------------------------------------------------------------------
    
    /*!
     * @brief Type definition for a smart pointer to this type.
     *
     * The \c ptr typedef can be used when the \c Ptr symbol cannot be used because another symbol
     * of that name has already been defined.
     */
    public: typedef Ptr<IIndexBuffer> ptr;
    
    /*!
     * @brief The unique ID of this type.
     */
    public: static const int32 TypeId = 0xC035D215;
    
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
      if ((ptr = ICapacity::TryCast(typeId)) != 0) return ptr;
      if ((ptr = IDisposable::TryCast(typeId)) != 0) return ptr;
      return (void*) 0;
    }
  };
} } } 

#endif
