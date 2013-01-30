#pragma once

#include "Core/TypeGlobals.h"
#include "Core/EngineObject.h"

#include "Core/PostProcessVertex.h"

#include "Graphics/Shader.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/StaticBuffer.h"
#include "Graphics/VertexDeclaration.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Resources;

		class Quad : public EngineObject
		{
		public:

			Quad(Engine* Engine, IShader* shader);
			~Quad();

			IShader* GetShader();

			void SetInput(const Dictionary<string, IRenderTarget*>& input);
			void SetOutput(const Dictionary<UInt32, IRenderTarget*>& output);

			void Draw();

		private:

			IShader* shader;
			VertexDeclaration* decl;
			StaticBuffer<TIKI_VERTEX_BUFFER>* vertexBuffer;

			static PostProcessVertex quadVertices[4];

		};
	}
}