
#include "Graphics/TerrainIndexBuffer.h"
#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		TerrainIndexBuffer::TerrainIndexBuffer(int32 size)
			: sizeStrip(size), sizeList(size * 3), indexCount(0)
		{
			dataList = new UInt32[sizeList];
			dataStrip = new UInt32[sizeStrip];
			indexBuffer = new DynamicBuffer<UInt32, D3D11_BIND_INDEX_BUFFER>(DllMain::Engine);
		}

		TerrainIndexBuffer::~TerrainIndexBuffer()
		{
			delete[](dataList);
			delete[](dataStrip);
			SafeRelease(&indexBuffer);
		}

		UInt32 TerrainIndexBuffer::GetSizeList() const
		{
			return sizeStrip;
		}

		const UInt32* TerrainIndexBuffer::GetDataList() const
		{
			return dataStrip;
		}

		int32 TerrainIndexBuffer::GetCapacity()
		{
			return sizeStrip;
		}

		void TerrainIndexBuffer::SetIndices(int32 bufferIndex, Array<int32> indices, int32 indicesOffset, int32 indicesCount)
		{
			memcpy(
				dataStrip + bufferIndex,
				((int32*)indices) + indicesOffset,
				sizeof(int32) * indicesCount
			);
						
			//UInt32 i = 2;
			//UInt32 iList = 0;
			//while (i < sizeStrip)
			//{
			//	dataList[iList++] = dataStrip[i - 2];  
			//	dataList[iList++] = dataStrip[i - 1];
			//	dataList[iList++] = dataStrip[i];

			//	i++;
			//}

			UInt32* bdata = indexBuffer->Map(sizeStrip);
			memcpy(
				bdata,
				dataStrip,
				sizeof(int32) * sizeStrip
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