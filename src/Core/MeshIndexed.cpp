
#include "Core/MeshIndexed.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		MeshIndexed::MeshIndexed(Engine* engine)
			: Mesh(engine), indexData(0), indexCount(0)
		{
		}

		MeshIndexed::~MeshIndexed()
		{
		}
		#pragma endregion

		#pragma region Member
		bool MeshIndexed::GetReady()
		{
			return Mesh::GetReady() && (indexData != 0) && (indexCount != 0);
		}
		#pragma endregion

		#pragma region Member - Get/Set
		void MeshIndexed::SetIndexData(UInt32* data, UInt32 count)
		{
			if (indexData != 0)
			{
				delete(indexData);
				indexData = 0;
			}

			indexData = new UInt32[count];
			indexCount = count;

			memcpy(
				indexData,
				data,
				count * sizeof(UInt32)
			);
		}

		void MeshIndexed::GetIndexData(UInt32** data, UInt32* count)
		{
			*data = indexData;
			*count = indexCount;
		}
		#pragma endregion
	}
}