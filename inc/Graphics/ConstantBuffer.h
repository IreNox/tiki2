#pragma once

#include "Core/Engine.h"
#include "Core/HelperLog.h"

namespace TikiEngine
{
	namespace Graphics
	{
		template <class T>
		class ConstantBuffer
		{
		public:

			#pragma region Class
			ConstantBuffer(Engine* engine)
				: engine(engine), buffer(0)
			{
				this->createBuffer();
			}

			~ConstantBuffer()
			{
				SafeRelease(&buffer);
			}
			#pragma endregion

			#pragma region Member
			T* Map()
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

			#pragma region Vars
			Engine* engine;
			ID3D11Buffer* buffer;
			#pragma endregion

			#pragma region Member - CreateBuffer
			void createBuffer()
			{
				D3D11_BUFFER_DESC desc;
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				desc.ByteWidth = sizeof(T);
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