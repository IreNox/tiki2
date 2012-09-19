////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_GRAPHICS_VERTEXBUFFER_H
#define CLODDY_GRAPHICS_VERTEXBUFFER_H

// Definitions

#define CODEX_PREFIX
#define CODEX_SYSTEM_PREFIX
#define CLODDY_KERNEL_PREFIX

// Include referenced classes.

#include <d3d11.h>
#include <CodeX/CodeX.h>
#include <CodeX/CodeX_System.h>
#include <Cloddy/Cloddy_Kernel.h>

// Declare class ::Cloddy::Graphics::VertexBuffer

namespace Cloddy{ namespace Graphics { 

  class VertexBuffer : public codex_Disposable, public cloddy_IVertexBuffer
  {
    // ---------------------------------------------------------------------------------------------
    // Public
    // ---------------------------------------------------------------------------------------------

  public:

    /*!
     * @brief  Creates a Cloddy VertexBuffer object.
     * 
     * @param device The Direct3D 11 device.
     * @param device The capacity.
     * @param device The size in bytes of a single vertex.
     */
    VertexBuffer(void* device, int capacity, int vertexSize);

    /*!
     * @brief  Locks a region of the buffer for writing.
     * 
     * @param min <b>[>=0]</b>  Minimum vertex buffer element index.
     * @param max <b>[>=0]</b>  Maximum vertex buffer element index.
     * @param count <b>[>=0]</b>  The number of vertices that will be updated in the locked region.
     * @param userData Optional user data object.
     * @param bufferLock <b>[not-null]</b>  The BufferLock object to use for reporting the result 
     * of the region lock.
     */
    void LockBuffer(codex_int32 min, codex_int32 max, codex_int32 count, void* userData, cloddy_BufferLock* bufferLock);     

    /*!
     * @brief Sets the internal encapsulated vertex buffer.
     */
    void SetBuffer();

    /*!
     * @brief  Unlocks a previously locked buffer region.
     * 
     * The #Unlock method must only be called if a locked buffer has been specified 
     * via BufferLock::Locked.
     */
    void Unlock();

    /*!
     * @brief  Returns the capacity of this object.
     * 
     * @return <b>[>=0]</b>  The capacity,in elements.
     */
    codex_int32 GetCapacity();

    /*!
     * @brief  Returns the size of a single vertex in the GPUs vertex buffer.
     * 
     * @return <b>[>0]</b>  Size of a single vertex,in bytes.
     */
    codex_int32 GetVertexSize();

    /*!
     * @brief The unique ID of this type.
     */
    static const codex_int32 TypeId = 0x2A4BA12E;

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

      ptr = cloddy_IVertexBuffer::TryCast(id);
      if (ptr != 0) return ptr;

      return Object::TryCast(id);
    }

    // ---------------------------------------------------------------------------------------------
    // Private
    // ---------------------------------------------------------------------------------------------

  private:

    int offset;  
    int capacity;
    int vertexSize;      
    ID3D11Buffer* vertexBuffer;     
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    codex_Ptr<codex_ByteBuffer> byteBuffer;
  };

} }

#endif