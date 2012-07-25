
#include "Core/Quad.h"
#include "Core/Engine.h"
#include "Core/IMeshRenderer.h"

namespace TikiEngine
{
	namespace Objects
	{
		using namespace TikiEngine::Vertices;

		#pragma region Class
		Quad::Quad(Engine* engine)
			: GameObject(engine)
		{
			PostProcessVertex vertices[] =
			{
				1.0f,  1.0f, 0.0f, 1.0f, 0.0f, // TR
				-1.0f,  1.0f, 0.0f, 0.0f, 0.0f, // TL
				-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // BL
				1.0f, -1.0f, 0.0f, 1.0f, 1.0f, // BR
				-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, // BL
				1.0f,  1.0f, 0.0f, 1.0f, 0.0f, // TR
			};

			IMeshRenderer renderer = engine->

			decl = new PostProcessVertexDeclaration(engine, shader);

			vertexBuffer = engine->graphics->GetVertexBuffer(decl);
			vertexBuffer->AddRef();
			vertexBuffer->Allocate(vertices, 6, &bufferIndex);
		}

		Quad::~Quad()
		{
			decl->Release();
			shader->Release();
			vertexBuffer->Release();
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void Quad::Draw(const DrawArgs& args)
		{
			decl->Apply();
			shader->Apply();
			vertexBuffer->Apply(bufferIndex);

			context->Draw(6, 0);
		}

		void Quad::Update(const UpdateArgs& args)
		{
		}
		#pragma endregion
	}
}