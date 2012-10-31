
#include "Graphics/TerrainVertexBuffer.h"
#include "Graphics/DllMain.h"

#include <iostream>
using namespace std;

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		TerrainVertexBuffer::TerrainVertexBuffer(int32 size)
			: size(size), buffer(0)
		{
			dataVector = new Vector3[size];
			dataVertices = new CloddyVertex[size];
			vertexBuffer = new DynamicBuffer<CloddyVertex, D3D11_BIND_VERTEX_BUFFER>(DllMain::Engine);
		}

		TerrainVertexBuffer::~TerrainVertexBuffer()
		{
			delete[](dataVector);
			delete[](dataVertices);
			SafeRelease(&vertexBuffer);
		}
		#pragma endregion

		#pragma region Member - Get
		const Vector3* TerrainVertexBuffer::GetData() const
		{
			return dataVector;
		}

		int32 TerrainVertexBuffer::GetCapacity()
		{
			return size;
		}

		int32 TerrainVertexBuffer::GetVertexSize()
		{
			return sizeof(Vector3);
		}
		#pragma endregion

		#pragma region Member - VertexBuffer
		void TerrainVertexBuffer::LockBuffer(int32 min, int32 max, int32 count, void* userData, BufferLock* bufferLock)
		{	
			buffer = ByteBuffer::Allocate(
				sizeof(CloddyVertex) * count
			);

			lockMin = min;
			lockMax = max;
			bufferLock->Locked(buffer);
		}

		void TerrainVertexBuffer::Unlock()
		{
			CloddyVertex* ptr = (CloddyVertex*)buffer->GetRawPointer();
			int64 size = buffer->GetCapacity();

			int32 i = lockMin;
			while (i < lockMax)
			{
				memcpy(&dataVector[i], ptr[i - lockMin].Position, sizeof(Vector3));
				i++;
			}

			memcpy(dataVertices + lockMin, ptr, (PInt)size);

			CloddyVertex* bdata = vertexBuffer->Map(this->size);
			memcpy(bdata, dataVertices, this->size * sizeof(CloddyVertex));
			vertexBuffer->Unmap();

			buffer = 0;
		}
		#pragma endregion



		void TerrainVertexBuffer::DisposeManaged()
		{
		}

		void TerrainVertexBuffer::DisposeUnmanaged()
		{

			// hire code
		}
	}
}