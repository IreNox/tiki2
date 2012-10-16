
#include "Graphics/TerrainVertexBuffer.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		TerrainVertexBuffer::TerrainVertexBuffer(int32 size)
			: size(size)
		{
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
			//ByteBuffer* buffer = new ByteBuffer(sizeof(Vector3) * size, true, );

			//bufferLock->Locked()
			//float bla = bufferLock->
		}

		void TerrainVertexBuffer::Unlock()
		{

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