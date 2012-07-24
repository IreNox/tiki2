
#include "Core/Engine.h"
#include "Graphics/SimpleVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
			SimpleVertexDeclaration::SimpleVertexDeclaration(TikiEngine::Engine* engine, Shader* shader)
				: VertexDeclaration(engine, shader, sizeof(SimpleVertex))
			{
				D3D11_INPUT_ELEMENT_DESC description[] =
				{
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
				};

				shader->CreateLayout(
					description,
					1,
					&this->inputLayout,
					&this->hash
				);
			}
	}
}

