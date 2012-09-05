
#include "Core/Engine.h"
#include "Graphics/VertexData.h"

#include "Graphics/DllMain.h"

namespace TikiEngine
{
	namespace Vertices
	{
		using namespace TikiEngine::Graphics;

		#pragma region Class
		VertexData::VertexData(Engine* engine)
			: EngineObject(engine), mesh(0), decl(0), shader(0), indexBuffer(0), vertexBuffer(0), allocatedIndex(false), allocatedVertex(false), dynamic(false)
		{
		}
		
		VertexData::~VertexData()
		{
			SafeRelease(&mesh);
			SafeRelease(&decl);
			SafeRelease(&shader);
			SafeRelease(&indexBuffer);
			SafeRelease(&vertexBuffer);
		}
		#pragma endregion

		#pragma region Member
		bool VertexData::GetDynamic()
		{
			return dynamic;
		}

		void VertexData::SetDynamic(bool dynamic)
		{
			this->dynamic = dynamic;

			if (vertexBuffer != 0)
			{
				vertexBuffer->Release();

				vertexBuffer = DllMain::Module->GetVertexBuffer(decl, dynamic);
				vertexBuffer->AddRef();
			}
		}
		#pragma endregion

		#pragma region Member - Apply/Draw
		void VertexData::Apply()
		{
			UINT offset = 0;
			UINT stride = decl->GetElementSize();

			ID3D11Buffer* buffer = this->vertexBuffer->GetBuffer();
			DllMain::Context->IASetVertexBuffers(
				0,
				1,
				&buffer,
				&stride,
				&offset
			);

			if (useIndex)
			{
				DllMain::Context->IASetIndexBuffer(
					this->indexBuffer->GetBuffer(),
					DXGI_FORMAT_R32_UINT,
					0
				);
			}

			D3D11_PRIMITIVE_TOPOLOGY pt = (D3D11_PRIMITIVE_TOPOLOGY)mesh->GetPrimitiveTopology();
			DllMain::Context->IASetPrimitiveTopology(pt);

			decl->Apply();
			shader->Apply();
		}

		void VertexData::Draw()
		{
			if (useIndex)
			{
				DllMain::Context->DrawIndexed(countIndex, indexIndex, indexVertex);
			}
			else
			{
				DllMain::Context->Draw(countVertex, 0);
			}
		}
		#pragma endregion

		#pragma region Member - Get/Set
		void VertexData::SetData(Mesh* inMesh, Shader* inShader)
		{
			if (inMesh == 0 || inShader == 0) 
			{
				throw "Arguments fail";
			}

			if (mesh != inMesh || shader != inShader)
			{
				SafeRelease(&mesh);
				SafeRelease(&decl);
				SafeRelease(&shader);
				SafeRelease(&indexBuffer);
				SafeRelease(&vertexBuffer);

				mesh = inMesh;
				mesh->AddRef();

				decl = new VertexDeclaration(
					engine,
					inShader,
					mesh->GetVertexDeclaration()
				);

				shader = inShader;
				shader->AddRef();

				indexBuffer = DllMain::Module->GetIndexBuffer();
				indexBuffer->AddRef();

				vertexBuffer = DllMain::Module->GetVertexBuffer(decl, dynamic);
				vertexBuffer->AddRef();
			}

			MeshIndexed* meshIndexed = dynamic_cast<MeshIndexed*>(mesh);

			if (meshIndexed != 0)
			{
				useIndex = true;

				UInt32* indices;
				UInt32 indiciesCount;
				meshIndexed->GetIndexData(&indices, &indiciesCount);

				this->setData(
					this->indexBuffer,
					indices,
					indiciesCount * sizeof(UInt32),
					&this->allocatedIndex,
					&this->indexIndex,
					&this->countIndex
				);
			}
			else
			{
				useIndex = false;
			}
			
			void* data;
			UInt32 size;
			mesh->GetVertexData(&data, &size);

			this->setData(
				this->vertexBuffer,
				data,
				size,
				&this->allocatedVertex,
				&this->indexVertex,
				&this->countVertex
			);
		}

		Mesh* VertexData::GetMesh()
		{
			return mesh;
		}
		#pragma endregion

		#pragma region Private Member
		void VertexData::setData(Buffer* buffer, void* data, UINT size, bool* allocated, UINT* index, UINT* count)
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