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

#include "Core/TypeDef.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace CodeX;
		using namespace Cloddy;

		class TerrainIndexBuffer : public codex_Disposable, public cloddy_IIndexBuffer
		{
		public:

			TerrainIndexBuffer(int32 size);
			~TerrainIndexBuffer();
			
			const UInt32* GetData() const;

			int32 GetCapacity();

			void SetIndices(int32 bufferIndex, Array<int32> indices, int32 indicesOffset, int32 indicesCount);

			static const codex_int32 TypeId = 0xA1B43C20;

		  protected:

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

		private:

			int32 size;
			UInt32* data;

		};
	}
}