#pragma once

#include <D3D11.h>

#include "Core/Vector2.h"
#include "Core/Vector3.h"
#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	namespace Vertices
	{
		struct PostProcessVertex
		{
			float Position[3];
			float UV[2];
		};

		class PostProcessVertexDeclaration : public VertexDeclaration
		{
		public:
			PostProcessVertexDeclaration(TikiEngine::Engine* engine, Shader* shader);			
			~PostProcessVertexDeclaration();

		private:

			static D3D11_INPUT_ELEMENT_DESC elements[2];

		};
	}
}