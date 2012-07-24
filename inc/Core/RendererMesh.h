#pragma once;

#include <D3D11.h>

#include "Graphics/Shader.h"
#include "Core/Element.h"
#include "Graphics/VertexData.h"

namespace TikiEngine
{
	namespace Elements
	{
		using namespace TikiEngine::Vertices;

		class Mesh : public Element
		{
		public:
			Mesh(Engine* engine);
			virtual ~Mesh();

			virtual void Init(VertexDeclaration* decl);

			virtual void Draw(const FrameArgs& args);
			virtual void Update(const FrameArgs& args);

			void Dispose();

		protected:
			Shader* shader;
			VertexData* data;
		};
	}
}