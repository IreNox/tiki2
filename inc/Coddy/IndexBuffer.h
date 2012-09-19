////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_GRAPHICS_INDEXBUFFER_H
#define CLODDY_GRAPHICS_INDEXBUFFER_H

// Definitions

#define CODEX_PREFIX
#define CODEX_SYSTEM_PREFIX
#define CLODDY_API_PREFIX

// Include referenced classes.

#include <d3d11.h>
#include <CodeX/CodeX.h>
#include <CodeX/CodeX_System.h>
#include <Cloddy/Cloddy_API.h>

// Declare class ::Cloddy::Graphics::IndexBuffer

namespace Cloddy{ namespace Graphics { 

  class IndexBuffer : public codex_Disposable, public cloddy_IIndexBuffer
  {
    // ---------------------------------------------------------------------------------------------
    // Public
    // ---------------------------------------------------------------------------------------------

  public:

    /*!
     * @brief  Creates a Cloddy IndexBuffer object.
     * 
     * @param device The Direct3D 11 device.
     * @param device The capacity.
     */
    IndexBuffer(void* device, int capacity);

    /*!
     * @brief  Returns the capacity of this object.
     * 
     * @return <b>[>=0]</b>  The capacity,in elements.
     */
    codex_int32 GetCapacity();

    /*!
     * @brief  Updates a range of indices in the buffer.TODO:Add userData Parameter!
     * 
     * @param bufferIndex <b>[>=0]</b>  Index of the first index buffer element to update.
     * @param indices <b>[not-null]</b>  An array holding the updated indices.
     * @param indicesOffset <b>[>=0]</b>  Offset into \e indices  to first index to read.
     * @param indicesCount <b>[>=0]</b>  Total number of indices to read from \e indices .
     */
    void SetIndices(codex_int32 bufferIndex, codex_Array<codex_int32> indices, codex_int32 indicesOffset, codex_int32 indicesCount);

    /*!
     * @brief Sets the internal encapsulated index buffer.
     */
    void SetBuffer();
    
    /*!
     * @brief The unique ID of this type.
     */
    static const codex_int32 TypeId = 0xA1B43C1F;

    // ---------------------------------------------------------------------------------------------
    // Protected
    // ---------------------------------------------------------------------------------------------

  protected:

    /*!
     * @brief Disposes unmanaged allocated memory.
     */
    void DisposeUnmanaged();

    /*!
     * @brief Disposes managed allocated memory.
     */
    void DisposeManaged();

    /*!
     * @brief Tries to cast this object to the given type.
     *
     * @param typeId The ID of the type to cast to.
     *
     * @return The result of the type cast. Can be \c 0 if the requested cast is an invalid 
     *         downcast.
     */
    void* TryCast(int id)
    {
      void* ptr;

      ptr = codex_Disposable::TryCast(id);
      if (ptr != 0) return ptr;

      ptr = cloddy_IIndexBuffer::TryCast(id);
      if (ptr != 0) return ptr;

      return Object::TryCast(id);
    }

    // ---------------------------------------------------------------------------------------------
    // Private
    // ---------------------------------------------------------------------------------------------

  private:

    int capacity;
    ID3D11Device* device;
    ID3D11Buffer* indexBuffer; 
    ID3D11DeviceContext* deviceContext;
  };

} }

#endif