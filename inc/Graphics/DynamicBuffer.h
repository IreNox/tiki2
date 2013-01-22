#pragma once

#include "Core/TypeGlobals.h"
#include "Core/EngineObject.h"
#include "Core/HelperLog.h"

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

#if TIKI_DX10
				void* mapped;
				HRESULT r = buffer->Map(D3D10_MAP_WRITE_DISCARD, 0, &mapped);
#else
				D3D11_MAPPED_SUBRESOURCE mapped;

				HRESULT r = DllMain::Context->Map(
					buffer,
					0,
					D3D11_MAP_WRITE_DISCARD,
					0,
					&mapped
				);
#endif

				if (FAILED(r))
				{
					engine->HLog.WriteError("Can't map ConstantBuffer", 0);
				}

#if TIKI_DX10
				return (T*)mapped;
#else
				return (T*)mapped.pData;
#endif
			}

			void Unmap()
			{
#if TIKI_DX10
				if (buffer) buffer->Unmap();
#else
				if (buffer) DllMain::Context->Unmap(buffer, 0);
#endif
			}

			TDX_Buffer* GetBuffer()
			{
				return buffer;
			}
			#pragma endregion

			#pragma region Member - Apply
			inline void Apply()
			{
				if (TBinding == TIKI_VERTEX_BUFFER)
				{
					UInt32 offset = 0;
					UInt32 stride = sizeof(T);
					TDX_Buffer* d3dbuffer = buffer;

					DllMain::Context->IASetVertexBuffers(0, 1, &d3dbuffer, &stride, &offset);
				}
				else if (TBinding == TIKI_INDEX_BUFFER)
				{
					DllMain::Context->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
				}
			}
			#pragma endregion

		private:

			UInt32 elementCount;
			TDX_Buffer* buffer;

			#pragma region Private Member - CreateBuffer
			void createBuffer()
			{
				if (buffer != 0)
				{
					SafeRelease(&buffer);
				}

#if TIKI_DX10
				D3D10_BUFFER_DESC desc;
				desc.Usage = D3D10_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
#else
				D3D11_BUFFER_DESC desc;
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
				desc.StructureByteStride = 0;
#endif
				desc.BindFlags = TBinding;
				desc.ByteWidth = sizeof(T) * elementCount;
				desc.MiscFlags = 0;
				
				HRESULT r = DllMain::Device->CreateBuffer(
					&desc,
					0,
					&buffer
				);

				if (FAILED(r)) 
				{
					engine->HLog.WriteError("Can't create FullSizeBuffer", 0);
				}
			}
			#pragma endregion

		};
	}
}