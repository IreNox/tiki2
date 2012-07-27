
#include "Graphics/PostProcessVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		D3D11_INPUT_ELEMENT_DESC PostProcessVertexDeclaration::elements[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		PostProcessVertexDeclaration::PostProcessVertexDeclaration(TikiEngine::Engine* engine, Shader* shader)
			: VertexDeclaration(engine, shader, sizeof(PostProcessVertex), elements, 2)
		{

		}

		PostProcessVertexDeclaration::~PostProcessVertexDeclaration()
		{

		}
	}
}