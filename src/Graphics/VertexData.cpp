
#include "Core/Engine.h"
#include "Graphics/VertexData.h"

namespace TikiEngine
{
	namespace Vertices
	{
		using namespace TikiEngine::Buffer;

		#pragma region Class
		VertexData::VertexData(Engine* engine, Shader* shader, VertexDeclaration* decl)
			: engine(engine), shader(shader), decl(decl), allocatedIndex(false), allocatedVertex(false)
		{
			this->indexBuffer = engine->graphics->GetIndexBuffer();
			this->vertexBuffer = engine->graphics->GetVertexBuffer(decl);
		}
		
		VertexData::~VertexData()
		{
			delete(shader);
			delete(decl);
		}
		#pragma endregion

		#pragma region Member - Apply
		void VertexData::Apply()
		{
			UINT offset = 0;
			UINT stride = decl->GetElementSize();
			auto context = engine->graphics->GetDeviceContext();

			ID3D11Buffer* buffer = this->vertexBuffer->GetBuffer();
			context->IASetVertexBuffers(
				0,
				1,
				&buffer,
				&stride,
				&offset
			);

			context->IASetIndexBuffer(
				this->indexBuffer->GetBuffer(),
				DXGI_FORMAT_R32_UINT,
				0
			);

			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			decl->Apply();
			shader->Apply();
		}
		#pragma endregion

		#pragma region Member - SetData
		void VertexData::SetIndexData(void* data, UINT size)
		{
			this->setData(
				this->indexBuffer,
				data,
				size,
				&this->allocatedIndex,
				&this->indexIndex,
				&this->countIndex
			);
		}

		void VertexData::SetVertexData(void* data, UINT size)
		{
			this->setData(
				this->vertexBuffer,
				data,
				size,
				&this->allocatedVertex,
				&this->indexVertex,
				&this->countVertex
			);
		}

		void VertexData::setData(TikiEngine::Buffer::Buffer* buffer, void* data, UINT size, bool* allocated, UINT* index, UINT* count)
		{
			UINT newCount = size / buffer->GetElementSize();

			if (*allocated)
			{
				if (newCount != *count)
				{
					throw "SetData -> new size not equals";
				}

				buffer->Copy(
					data,
					newCount,
					*index
				);
			}
			else
			{
				buffer->Allocate(
					data,
					newCount,
					index
				);

				*allocated = true;
			}	

			*count = newCount;
		}
		#pragma endregion
	}
}