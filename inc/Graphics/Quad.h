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

			void SetInput(const Dictionary<IRenderTarget*, cstring>* input);
			void SetOutput(const Dictionary<IRenderTarget*, UInt32>* output);

			void Draw();

		private:

			Shader* shader;

			//VertexBuffer* vertexBuffer;
			StaticBuffer<D3D11_BIND_VERTEX_BUFFER>* vertexBuffer;

			ID3D11InputLayout* inputLayout;

			static PostProcessVertex quadVertices[4];
			static D3D11_INPUT_ELEMENT_DESC Quad::quadVertexElements[2];

		};
	}
}