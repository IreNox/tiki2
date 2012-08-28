
#include "Core/Engine.h"
#include "Core/Console.h"

#include "Graphics/Buffer.h"
#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		Buffer::Buffer(Engine* engine, UInt32 size)
			: EngineObject(engine), elementSize(size), buffer(0), bufferSize(0), bufferUsage(0)
		{
		}

		Buffer::~Buffer()
		{
			if (buffer != NULL)
			{
				buffer->Release();
				buffer = NULL;
			}
		}
		#pragma endregion

		#pragma region Member
		void Buffer::Apply(UINT offset) const
		{
			DllMain::Context->IASetVertexBuffers(0, 1, &buffer, &elementSize, &offset);
		}

		ID3D11Buffer* Buffer::GetBuffer() const
		{
			return this->buffer;
		}

		UINT Buffer::GetElementSize() const
		{
			return elementSize;
		}
		#pragma endregion

		#pragma region Member - Copy
		void Buffer::Copy(void* data, UINT count, UINT index)
		{
			UINT size = this->elementSize * count;

			this->writeBuffer(
				data,
				size,
				this->elementSize * index
			);
		}
		#pragma endregion

		#pragma region Member - Allocate
		void Buffer::Allocate(void* data, UINT count, UINT* index)
		{
			UINT size = this->elementSize * count;
			*index = this->bufferUsage / this->elementSize;

			if (this->bufferSize < this->bufferUsage + size)
			{
				this->resizeBuffer(data, size);
			}
			else
			{
				this->writeBuffer(data, size, this->bufferUsage);
				this->bufferUsage += size;
			}
		}
		#pragma endregion

		#pragma region Member - ResizeBuffer
		void Buffer::writeBuffer(void* addData, UINT dataSize, UINT index)
		{
			D3D11_MAPPED_SUBRESOURCE mapped;

			HRESULT r = DllMain::Context->Map(
				buffer,
				0,
				D3D11_MAP_WRITE_DISCARD,
				0,
				&mapped
			);

			if (FAILED(r))
			{
				Console::WriteError("Can't map Buffer", r);
			}

			char* data = (char*)mapped.pData;
			data += index;

			memcpy(
				(void*)data,
				addData,
				dataSize
			);			

			DllMain::Context->Unmap(buffer, 0);
		}

		void Buffer::resizeBuffer(void* addData, UINT dataSize)
		{
			UINT neededSize = this->bufferUsage + dataSize;
			UINT size = neededSize;

			UINT index = 0;
			char* newData = new char[size];
			ZeroMemory(newData, size);

			if (buffer != NULL)
			{
				D3D11_MAPPED_SUBRESOURCE mapped;
				mapped.pData = 0;
				mapped.RowPitch = 0;
				mapped.DepthPitch = 0;

				DllMain::Context->Map(
					buffer,
					0,
					D3D11_MAP_READ,
					0,
					&mapped
				);

				index = this->bufferUsage;
				memcpy(newData, mapped.pData, this->bufferUsage);

				DllMain::Context->Unmap(buffer, 0);

				buffer->Release();
				buffer = 0;
			}

			memcpy(newData + index, addData, dataSize);
			
			this->bufferSize = size;
			this->bufferUsage += dataSize;

			buffer = this->createBuffer(size, newData);

			if (buffer == 0)
			{
				Console::WriteError("Can't create Buffer", 0);
			}

			delete(newData);
		}
		#pragma endregion
	}
}