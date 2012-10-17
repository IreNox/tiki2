
#include "Graphics/TerrainIndexBuffer.h"

namespace TikiEngine
{
	namespace Graphics
	{
		TerrainIndexBuffer::TerrainIndexBuffer(int32 size)
			: size(size)
		{
			data = new UInt32[size];
		}

		TerrainIndexBuffer::~TerrainIndexBuffer()
		{
			delete[](data);
		}

		const UInt32* TerrainIndexBuffer::GetData() const
		{
			return data;
		}

		int32 TerrainIndexBuffer::GetCapacity()
		{
			return size;
		}

		void TerrainIndexBuffer::SetIndices(int32 bufferIndex, Array<int32> indices, int32 indicesOffset, int32 indicesCount)
		{
			memcpy(
				data + bufferIndex,
				((int32*)indices) + indicesOffset,
				sizeof(int32) * indicesCount
			);
		}

		void TerrainIndexBuffer::DisposeManaged()
		{
		}

		void TerrainIndexBuffer::DisposeUnmanaged()
		{
		}
	}
}