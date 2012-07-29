#pragma once

#include "Core/Mesh.h"

namespace TikiEngine
{
	namespace Graphics
	{
		class MeshIndexed : Mesh
		{
		public:

			MeshIndexed(Engine* engine);
			~MeshIndexed();

			void SetIndexData(UInt32* data, UInt32 count);
			void GetIndexData(UInt32** data, UInt32* count);

			bool GetReady();

		private:

			UInt32* indexData;
			UInt32 indexCount;
		};
	}
}