#pragma once

#include "Core/EngineObject.h"
#include "Core/Console.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		template <class T, UINT TBinding>
		class DynamicBuffer : public EngineObject
		{
		public:

			#pragma region Class
			DynamicBuffer(Engine* engine)
				: EngineObject(engine), buffer(0), elementCount(0)
			{
			}

			~DynamicBuffer()
			{
				SafeRelease(&buffer);
			}
			#pragma endregion

			#pragma region Member
			T* Map(UInt32 count)
			{
				if (count == 0) return 0;

				if (count > elementCount)
				{
					elementCount = count;
					this->createBuffer();
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
					Console::WriteError("Can't map ConstantBuffer", r);
				}

				return (T*)mapped.pData;
			}

			void Unmap()
			{
				DllMain::Context->Unmap(buffer, 0);
			}

			ID3D11Buffer* GetBuffer()
			{
				return buffer;
			}
			#pragma endregion

		private:

			UInt32 elementCount;
			ID3D11Buffer* buffer;

			#pragma region Private Member - CreateBuffer
			void createBuffer()
			{
				if (buffer != 0)
				{
					SafeRelease(&buffer);
				}

				D3D11_BUFFER_DESC desc;
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.BindFlags = TBinding;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				desc.ByteWidth = sizeof(T) * elementCount;
				desc.MiscFlags = 0;
				desc.StructureByteStride = 0;

				HRESULT r = DllMain::Device->CreateBuffer(
					&desc,
					0,
					&buffer
				);

				if (FAILED(r)) 
				{
					Console::WriteError("Can't create FullSizeBuffer", r);
				}
			}
			#pragma endregion

		};
	}
}