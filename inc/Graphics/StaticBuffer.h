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
				D3D11_BUFFER_DESC desc;
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.BindFlags = TBinding;
				desc.CPUAccessFlags = 0;
				desc.ByteWidth = elementSize * elementCount;
				desc.MiscFlags = 0;
				desc.StructureByteStride = 0;
				
				D3D11_SUBRESOURCE_DATA data;
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
					HelperLog::WriteError("Can't create StaticBuffer", 0);
				}
			}

			~StaticBuffer()
			{
				SafeRelease(&buffer);
			}
			#pragma endregion

			#pragma region Member
			ID3D11Buffer* GetBuffer()
			{
				return buffer;
			}

			UInt32 GetElementSize()
			{
				return elementSize;
			}

			UInt32 GetElementCount()
			{
				return elementCount;
			}

			UInt32 GetSize()
			{
				return elementSize * elementCount;
			}
			#pragma endregion
			
			#pragma region Member - Apply
			void Apply()
			{
				if (TBinding == D3D11_BIND_VERTEX_BUFFER)
				{
					UInt32 offset = 0;
					UInt32 stride = elementSize;
					ID3D11Buffer* d3dbuffer = buffer;

					DllMain::Context->IASetVertexBuffers(0, 1, &d3dbuffer, &stride, &offset);
				}
				else if (TBinding == D3D11_BIND_INDEX_BUFFER)
				{
					DllMain::Context->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
				}
			}
			#pragma endregion

		private:

			UInt32 elementSize;
			UInt32 elementCount;
			ID3D11Buffer* buffer;

		};
	}
}