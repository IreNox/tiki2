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

#include "Core/Material.h"

#include "Graphics/TerrainIndexBuffer.h"
#include "Graphics/TerrainVertexBuffer.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Resources;

		class TerrainTriangulationCallback : public codex_Disposable, public cloddy_ITriangulationCallback
		{
		public:

			TerrainTriangulationCallback(TerrainIndexBuffer* indexBuffer, TerrainVertexBuffer* vertexBuffer);
			~TerrainTriangulationCallback();

			/*!
				* @brief A triangulation cycle has begun.
				* 
				* @param userData Optional user data object.
				*/
			void BeginTriangulation(void* userData);

			/*! @brief The current triangulation cycle has ended. */
			void EndTriangulation();    

			/*!
				* @brief This method is called for each triangle strip generated during triangulation.
				* 
				* @param indices Holds the indices of the generated triangle strip.
				* @param count Number of indices in \e indices .
				* @param min Minimum index value.
				* @param max Maximum index value.
				*/
			void TriangleStripChunk(codex_Array<codex_int32> indices, codex_int32 count, codex_int32 min, codex_int32 max);   
    
			void SetMaterial(Material* mat);

			static const codex_int32 TypeId = 0xB3C81825;

		protected:

			void DisposeUnmanaged();
			void DisposeManaged();

			void* TryCast(int id)
			{
				void* ptr;

				ptr = codex_Disposable::TryCast(id);
				if (ptr != 0) return ptr;

				ptr = cloddy_ITriangulationCallback::TryCast(id);
				if (ptr != 0) return ptr;

				return Object::TryCast(id);
			}

		private:

			Material* material;

			TerrainIndexBuffer* indexBufferCloddy;
			TerrainVertexBuffer* vertexBuffer;

			DynamicBuffer<Int32, TIKI_INDEX_BUFFER>* indexBuffer;

			TDX_InputLayout* layout;

		};
	}
}