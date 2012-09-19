////////////////////////////////////////////////////////////////////////////////////////////////////
// Cloddy SDK v2.1 - (C) Copyright 2008-2012, BiteTheBytes UG (haftungsbeschraenkt)
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLODDY_GRAPHICS_TRIANGULATIONCALLBACK_H
#define CLODDY_GRAPHICS_TRIANGULATIONCALLBACK_H

// Definitions

#define CODEX_PREFIX
#define CODEX_SYSTEM_PREFIX
#define CLODDY_API_PREFIX
#define CLODDY_KERNEL_PREFIX

// Include referenced classes.

#include <d3d11.h>
#include <CodeX/CodeX.h>
#include <CodeX/CodeX_System.h>
#include <Cloddy/Cloddy_API.h>
#include <Cloddy/Cloddy_Kernel.h>

#include <Cloddy/VertexBuffer.h>
#include <Cloddy/IndexBuffer.h>

// Declare class ::Cloddy::Graphics::TriangulationCallback

namespace Cloddy{ namespace Graphics { 

  class TriangulationCallback : public codex_Disposable, public cloddy_ITriangulationCallback
  {
    // ---------------------------------------------------------------------------------------------
    // Public
    // ---------------------------------------------------------------------------------------------

  public:

    /*!
     * @brief  Creates a Cloddy TriangulationCallback object.
     * 
     * @param device The Direct3D 11 device.
     * @param vertexbuffer The Cloddy vertex buffer.
     * @param indexBuffer The Cloddy index buffer.
     */
    TriangulationCallback(void* device, VertexBuffer* vertexbuffer, IndexBuffer* indexBuffer);

    /*!
     * @brief  A triangulation cycle has begun.
     * 
     * @param userData Optional user data object.
     */
    void BeginTriangulation(void* userData);

    /*!
     * @brief  The current triangulation cycle has ended.
     */
    void EndTriangulation();    

    /*!
     * @brief  This method is called for each triangle strip generated during triangulation.
     * 
     * @param indices Holds the indices of the generated triangle strip.
     * @param count Number of indices in \e indices .
     * @param min Minimum index value.
     * @param max Maximum index value.
     */
    void TriangleStripChunk(codex_Array<codex_int32> indices, codex_int32 count, codex_int32 min, codex_int32 max);   
    
    /*!
     * @brief The unique ID of this type.
     */
    static const codex_int32 TypeId = 0xB3C81825;

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

      ptr = cloddy_ITriangulationCallback::TryCast(id);
      if (ptr != 0) return ptr;

      return Object::TryCast(id);
    }

    // ---------------------------------------------------------------------------------------------
    // Private
    // ---------------------------------------------------------------------------------------------

  private:

    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    codex_Ptr<IndexBuffer> indexBuffer;
    codex_Ptr<VertexBuffer> vertexBuffer;
  };

} }

#endif