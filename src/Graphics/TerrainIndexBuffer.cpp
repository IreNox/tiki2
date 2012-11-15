
#include "Graphics/TerrainIndexBuffer.h"
#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		TerrainIndexBuffer::TerrainIndexBuffer(int32 size)
			: size(size), indexCount(0)
		{
			data = new UInt32[size];
			indexBuffer = new DynamicBuffer<UInt32, D3D11_BIND_INDEX_BUFFER>(DllMain::Engine);
		}

		TerrainIndexBuffer::~TerrainIndexBuffer()
		{
			delete[](data);
			SafeRelease(&indexBuffer);
		}

		UInt32 TerrainIndexBuffer::GetSizeList() const
		{
			return size;
		}

		const UInt32* TerrainIndexBuffer::GetDataList() const
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
						
			UInt32* bdata = indexBuffer->Map(size);
			memcpy(
				bdata,
				data,
				sizeof(int32) * size
			);	
			indexBuffer->Unmap();
		}

		void TerrainIndexBuffer::DisposeManaged()
		{
		}

		void TerrainIndexBuffer::DisposeUnmanaged()
		{
		}
	}
}