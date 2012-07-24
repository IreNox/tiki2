#pragma once

#include "Core/Engine.h"
#include "Core/Console.h"

namespace TikiEngine
{
	namespace Buffer
	{
		template <class T>
		class ConstantBuffer
		{
		public:

			#pragma region Class
			ConstantBuffer(Engine* engine)
				: engine(engine), buffer(0), context(engine->graphics->GetDeviceContext())
			{
				this->createBuffer();
			}

			~ConstantBuffer()
			{
				if (buffer != 0)
				{
					buffer->Release();
					buffer = 0;
				}
			}
			#pragma endregion

			#pragma region Member
			T* Map()
			{
				D3D11_MAPPED_SUBRESOURCE mapped;

				HRESULT r = context->Map(
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
				context->Unmap(buffer, 0);
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
			ID3D11DeviceContext* context;
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

				HRESULT r = engine->graphics->GetDevice()->CreateBuffer(
					&desc,
					0,
					&buffer
					);

				if (FAILED(r)) 
				{
					Console::WriteError("Can't create ConstantBuffer", r);
				}
			}
			#pragma endregion

		};
	}
}