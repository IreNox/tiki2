
#include "Core/Engine.h"
#include "Graphics/IndexBuffer.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		IndexBuffer::IndexBuffer(Engine* engine)
			: Buffer(engine, 4)
		{
		}

		IndexBuffer::~IndexBuffer()
		{
		}
		#pragma endregion

		#pragma region Member - CreateBuffer
		ID3D11Buffer* IndexBuffer::createBuffer(UINT size, void* data)
		{
			D3D11_BUFFER_DESC desc;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = size;
			desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA initData;
			initData.pSysMem = data;
    
			ID3D11Buffer* buffer;

			HRESULT r = DllMain::Device->CreateBuffer(
				&desc,
				&initData,
				&buffer
			);
    
			if (FAILED(r)) 
			{
				return NULL;
			}

			return buffer;
		}
		#pragma endregion		
	}
}