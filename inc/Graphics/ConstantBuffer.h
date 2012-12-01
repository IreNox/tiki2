#pragma once

#include "Core/Engine.h"
#include "Core/HelperLog.h"

#include "Core/IConstantBuffer.h"

namespace TikiEngine
{
	namespace Graphics
	{
		template <typename T>
		class ConstantBuffer : public IConstantBuffer
		{
		public:

			#pragma region Class
			ConstantBuffer(Engine* engine, UInt32 size = 0)
				: IConstantBuffer(engine), buffer(0), size(size)
			{
				if (!this->size) this->size = sizeof(T);

				this->createBuffer();
			}

			~ConstantBuffer()
			{
				SafeRelease(&buffer);
			}
			#pragma endregion

			#pragma region Member
			inline void* Map()
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
					engine->HLog.WriteError("Can't map ConstantBuffer", 0);
				}

				return mapped.pData;
			}

			inline T* MapTI()
			{
				return (T*)this->Map();
			}

			inline void Unmap()
			{
				DllMain::Context->Unmap(buffer, 0);
			}

			inline void* GBuffer() { return buffer; }
			inline UInt32 GSize() { return size; }
			#pragma endregion

		private:

			#pragma region Vars
			ID3D11Buffer* buffer;

			UInt32 size;
			#pragma endregion

			#pragma region Member - CreateBuffer
			void createBuffer()
			{
				D3D11_BUFFER_DESC desc;
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				desc.ByteWidth = size;
				desc.MiscFlags = 0;
				desc.StructureByteStride = 0;

				HRESULT r = DllMain::Device->CreateBuffer(
					&desc,
					0,
					&buffer
				);

				if (FAILED(r)) 
				{
					engine->HLog.WriteError("Can't create ConstantBuffer", 0);
				}
			}
			#pragma endregion

		};
	}
}