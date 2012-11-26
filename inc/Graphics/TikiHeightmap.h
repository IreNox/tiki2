#pragma once

#define CODEX_PREFIX
#define CODEX_SYSTEM_PREFIX
#define CLODDY_CORE_PREFIX
#define CLODDY_KERNEL_PREFIX
#define CLODDY_API_PREFIX

#include <CodeX/Codex.h>
#include <CodeX/Codex_System.h>
#include <Cloddy/Cloddy_Core.h>
#include <Cloddy/Cloddy_Kernel.h>
#include <Cloddy/Cloddy_API.h>

#include "Core/TypeDef.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace Cloddy::API::Heightmaps;

		class TikiHeightmap : public Heightmap
		{
		public:

			TikiHeightmap(int size);
			~TikiHeightmap();

			void SetColor(IHeightmap* color);
			void SetDetail(IHeightmap* detail);
			void SetElevation(IHeightmap* elevation);

			virtual HeightmapLayer GetLayerMask();

			void Get(Int32 x, Int32 y, HeightmapSample* sample);
			void Get(Int32 x, Int32 y, Int32 z, HeightmapSample* sample);

			static const codex_int32 TypeId = 0xF2C4BDE6;

		protected:

			void DisposeUnmanaged();
			void DisposeManaged();

			void* TryCast(int id)
			{
				void* ptr;

				if (id == TypeId) return (void*) this;
				if ((ptr = cloddy_Heightmap::TryCast(id)) != 0) return ptr;
				if ((ptr = TikiHeightmap::TryCast(TypeId)) != 0) return ptr;

				return Object::TryCast(id);
			}

		private:

			int size;

			codex_Ptr<IHeightmap> color;
			codex_Ptr<IHeightmap> detail;
			codex_Ptr<IHeightmap> elevation;

		};
	}
}