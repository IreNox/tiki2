#pragma once

#define CODEX_PREFIX
#define CLODDY_CORE_PREFIX
#define CLODDY_KERNEL_PREFIX
#define CLODDY_API_PREFIX
#define CLODDY_GRAPHICS_PREFIX
#define CLODDY_EXTENSIONS_PREFIX

#include <CodeX/Codex.h>
#include "Cloddy/Cloddy_Core.h"
#include "Cloddy/Cloddy_Kernel.h"
#include "Cloddy/Cloddy_API.h"
#include "Cloddy/Cloddy_Graphics.h"
#include "Cloddy/Cloddy_Extensions.h"

#include "Core/Vector3.h"
#include "Graphics/DynamicBuffer.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace CodeX;
		using namespace Cloddy;
		using namespace Cloddy::Kernel;

		struct CloddyVertex
		{
			float Position[3];
			float UV[2];
			float Normal[3];
			int Color;
		};

		class TerrainVertexBuffer : public codex_Disposable, public cloddy_IVertexBuffer
		{
		public:
			
			DynamicBuffer<CloddyVertex, D3D11_BIND_VERTEX_BUFFER>* vertexBuffer;

			TerrainVertexBuffer(int32 size);
			~TerrainVertexBuffer();
			
			const Vector3* GetData() const;

			int32 GetCapacity();
			int32 GetVertexSize();

			void LockBuffer(int32 min, int32 max, int32 count, void* userData, BufferLock* bufferLock);    
		    void Unlock();

			static const codex_int32 TypeId = 0xA1B43C21;

		  protected:

			void DisposeUnmanaged();

			void DisposeManaged();

			void* TryCast(int id)
			{
			  void* ptr;

			  ptr = codex_Disposable::TryCast(id);
			  if (ptr != 0) return ptr;

			  ptr = cloddy_IVertexBuffer::TryCast(id);
			  if (ptr != 0) return ptr;

			  return Object::TryCast(id);
			}

		private:

			int32 size;

			Vector3* dataVector;
			CloddyVertex* dataVertices;

			int32 lockMin;
			int32 lockMax;
			codex_Ptr<ByteBuffer> buffer;

		};
	}
}