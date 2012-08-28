
#include "Core/Engine.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexDeclaration.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Graphics
	{
		#pragma region Class
		VertexBuffer::VertexBuffer(Engine* engine, UInt32 vertexSize, bool dynamic)
			: Buffer(engine, vertexSize), dynamic(dynamic)
		{		
		}

		VertexBuffer::VertexBuffer(Engine* engine, VertexDeclaration* decl, bool dynamic)
			: Buffer(engine, decl->GetElementSize()), dynamic(dynamic)
		{
		}

		VertexBuffer::~VertexBuffer()
		{
		}
		#pragma endregion

		#pragma region Member - CreateBuffer
		ID3D11Buffer* VertexBuffer::createBuffer(UINT size, void* data)
		{
			D3D11_BUFFER_DESC desc;
			desc.ByteWidth = size;
			desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			desc.MiscFlags = 0;
			desc.StructureByteStride = 0;

			if (dynamic)
			{
				desc.Usage = D3D11_USAGE_DYNAMIC;
				desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			}
			else
			{
				desc.Usage = D3D11_USAGE_DEFAULT;
				desc.CPUAccessFlags = 0;
			}

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