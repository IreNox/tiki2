#pragma once

#include "Core/Element.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/PostProcessVertex.h"

namespace TikiEngine
{
	namespace Elements
	{
		using namespace TikiEngine::Buffer;
		using namespace TikiEngine::Effects;
		using namespace TikiEngine::Vertices;

		class Quad : public Element
		{
		public:

			Quad(Engine* engine, Shader* shader);
			~Quad();

			void Draw(const FrameArgs& args);
			void Update(const FrameArgs& args);

		private:

			Shader* shader;

			VertexDeclaration* decl;

			UINT bufferIndex;
			VertexBuffer* vertexBuffer;

		};
	}
}