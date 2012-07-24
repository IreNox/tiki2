
#include "Core/Engine.h"
#include "Graphics/DefaultVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
			DefaultVertexDeclaration::DefaultVertexDeclaration(TikiEngine::Engine* engine, Shader* shader)
				: VertexDeclaration(engine, shader, sizeof(DefaultVertex))
			{				
				D3D11_INPUT_ELEMENT_DESC description[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
				};

				shader->CreateLayout(
					description,
					3,
					&this->inputLayout,
					&this->hash
				);
			}

			DefaultVertexDeclaration::~DefaultVertexDeclaration()
			{
			}
	}
}
