
#include "Graphics/TerrainVertexBuffer.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		TerrainVertexBuffer::TerrainVertexBuffer(int32 size)
			: size(size), buffer(0)
		{
			bla = new float[size * 3];
			data = new Vector3[size];
		}

		TerrainVertexBuffer::~TerrainVertexBuffer()
		{
			delete[](data);
		}
		#pragma endregion

		#pragma region Member - Get
		const Vector3* TerrainVertexBuffer::GetData() const
		{
			return data;
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
			if (buffer == 0)
			{
				buffer = ByteBuffer::Allocate(
					sizeof(Vector3) * size
				);
			}

			bufferLock->Locked(buffer);
		}

		void TerrainVertexBuffer::Unlock()
		{
			void* ptr = buffer->GetRawPointer();
			int64 size = buffer->GetCapacity();

			memcpy(bla, ptr, size);
			memcpy(data, ptr, size);
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