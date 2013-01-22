#pragma once

#include "Core/TypeGlobals.h"
#include "Core/EngineObject.h"

#include "Core/PostProcessVertex.h"

#include "Graphics/Shader.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/StaticBuffer.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Resources;

		class Quad : public EngineObject
		{
		public:

			Quad(Engine* Engine);
			~Quad();

			IShader* GetShader();
			void SetShader(IShader* shader);

			void SetInput(const Dictionary<string, IRenderTarget*>& input);
			void SetOutput(const Dictionary<UInt32, IRenderTarget*>& output);

			void Draw();

		private:

			Shader* shader;

			//VertexBuffer* vertexBuffer;
			StaticBuffer<TIKI_VERTEX_BUFFER>* vertexBuffer;

			TDX_InputLayout* inputLayout;

			static PostProcessVertex quadVertices[4];
			static TDX_Input_Element_desc Quad::quadVertexElements[2];

		};
	}
}