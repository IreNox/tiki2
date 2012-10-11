
#include "Core/Engine.h"
#include "Core/HelperLog.h"

#include "Core/TypeGlobals.h"

#include "Graphics/Buffer.h"
#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		Buffer::Buffer(Engine* engine, UInt32 size)
			: EngineObject(engine), elementSize(size), buffer(0), bufferData(0), bufferUsage(0)
		{
		}

		Buffer::~Buffer()
		{
			SafeDelete(&bufferData);

			SafeRelease(&buffer);
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

			this->resizeBuffer(data, size);
		}
		#pragma endregion

		#pragma region Member - ResizeBuffer
		void Buffer::writeBuffer(void* addData, UINT dataSize, UINT index)
		{
			if (bufferData == 0)
			{
				HelperLog::WriteError("Buffer not init.", 0);
			}

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
				HelperLog::WriteError("Can't map Buffer", 0);
			}

			memcpy(bufferData + index, addData, dataSize);
			memcpy(mapped.pData, bufferData, bufferUsage);

			DllMain::Context->Unmap(buffer, 0);
		}

		void Buffer::resizeBuffer(void* addData, UINT dataSize)
		{
			UInt32 neededSize = this->bufferUsage + dataSize;

			char* newData = new char[neededSize];

			if (bufferData != 0)
			{
				memcpy(newData, bufferData, this->bufferUsage);
				SafeDelete(&bufferData);
			}
			memcpy(newData + this->bufferUsage, addData, dataSize);
			bufferData = newData;

			//if (buffer != NULL)
			//{
			//	D3D11_MAPPED_SUBRESOURCE mapped;
			//	mapped.pData = 0;
			//	mapped.RowPitch = 0;
			//	mapped.DepthPitch = 0;

			//	DllMain::Context->Map(
			//		buffer,
			//		0,
			//		D3D11_MAP_READ,
			//		0,
			//		&mapped
			//	);

			//	index = this->bufferUsage;
			//	memcpy(newData, mapped.pData, this->bufferUsage);

			//	DllMain::Context->Unmap(buffer, 0);

			//	buffer->Release();
			//	buffer = 0;
			//}

			
			this->bufferUsage = neededSize;
			buffer = this->createBuffer(neededSize, newData);

			if (buffer == 0)
			{
				HelperLog::WriteError("Can't create Buffer", 0);
			}
		}
		#pragma endregion
	}
}