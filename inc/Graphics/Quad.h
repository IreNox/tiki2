#pragma once

#include "Core/TypeGlobals.h"
#include "Core/EngineObject.h"

#include "Core/PostProcessVertex.h"

#include "Graphics/Shader.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/VertexBuffer.h"

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

			IRenderTarget* GetRenderTerget();
			void SetRenderTarget(IRenderTarget* renderTarget);

			void Draw();

		private:

			Shader* shader;
			RenderTarget* renderTarget;

			VertexBuffer* vertexBuffer;

			ID3D11InputLayout* inputLayout;

			static PostProcessVertex quadVertices[6];
			static D3D11_INPUT_ELEMENT_DESC Quad::quadVertexElements[2];

		};
	}
}