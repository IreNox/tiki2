#pragma once

#include "Core/TypeGlobals.h"
#include "Core/EngineObject.h"
#include "Core/HelperLog.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		template <UINT TBinding>
		class StaticBuffer : public EngineObject
		{
		public:

			#pragma region Class
			StaticBuffer(Engine* engine, UInt32 elementSize, UInt32 elementCount, void* initData)
				: EngineObject(engine), buffer(0), elementCount(elementCount), elementSize(elementSize)
			{
#if TIKI_DX10
				D3D10_BUFFER_DESC desc;
				D3D10_SUBRESOURCE_DATA data;
				desc.Usage = D3D10_USAGE_DEFAULT;
#else
				D3D11_BUFFER_DESC desc;
				D3D11_SUBRESOURCE_DATA data;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.StructureByteStride = 0;
#endif

				desc.BindFlags = TBinding;
				desc.CPUAccessFlags = 0;
				desc.ByteWidth = elementSize * elementCount;
				desc.MiscFlags = 0;

				data.pSysMem = initData;
				data.SysMemPitch = 0;
				data.SysMemSlicePitch = 0;

				HRESULT r = DllMain::Device->CreateBuffer(
					&desc,
					&data,
					&buffer
				);

				if (FAILED(r)) 
				{
					_CrtDbgBreak();
					engine->HLog.WriteError("Can't create StaticBuffer", 0);
				}
			}

			~StaticBuffer()
			{
				SafeRelease(&buffer);
			}
			#pragma endregion

			#pragma region Member
			inline TDX_Buffer* GetBuffer()
			{
				return buffer;
			}

			inline UInt32 GetElementSize()
			{
				return elementSize;
			}

			inline UInt32 GetElementCount()
			{
				return elementCount;
			}

			inline UInt32 GetSize()
			{
				return elementSize * elementCount;
			}
			#pragma endregion
			
			#pragma region Member - Apply
			inline void Apply()
			{
				if (TBinding == TIKI_VERTEX_BUFFER)
				{
					UInt32 offset = 0;
					UInt32 stride = elementSize;
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

			UInt32 elementSize;
			UInt32 elementCount;
			TDX_Buffer* buffer;

		};
	}
}