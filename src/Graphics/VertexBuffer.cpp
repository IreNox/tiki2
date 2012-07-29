
#include "Core/Engine.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexDeclaration.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Buffer
	{
		#pragma region Class
		VertexBuffer::VertexBuffer(Engine* engine, VertexDeclaration* decl)
			: Buffer(engine, decl->GetElementSize())
		{
		}

		VertexBuffer::~VertexBuffer()
		{
		}
		#pragma endregion

		#pragma region Member
		void VertexBuffer::fillBufferDesc(D3D11_BUFFER_DESC* desc)
		{
			desc->BindFlags = D3D11_BIND_VERTEX_BUFFER;
		}
		#pragma endregion

		#pragma region Member - CreateBuffer
		ID3D11Buffer* VertexBuffer::createBuffer(UINT size, void* data)
		{
			D3D11_BUFFER_DESC desc;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.ByteWidth = size;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.CPUAccessFlags = 0; //D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
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