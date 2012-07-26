#pragma once

#include "D3D11.h"

#include "Core/Vector3.h"
#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	namespace Vertices
	{
		struct SimpleVertex
		{
			float Position[3];
		};

		class SimpleVertexDeclaration : public VertexDeclaration
		{
		public:
			SimpleVertexDeclaration(TikiEngine::Engine* engine, Shader* shader);
			~SimpleVertexDeclaration();

		protected:
			void createLayout(ID3D11InputLayout** layout, ULONG* hash);
			
		};
	}
}