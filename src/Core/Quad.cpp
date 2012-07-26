
#include "Core/Quad.h"
//#include "Core/Engine.h"
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

			mesh = 0;
			mesh->SetVertexData(&vertices, sizeof(vertices));
			mesh->SetVertexDeclaration(0, sizeof(bool));

			renderer = 0;
			renderer->SetMesh(mesh);
			renderer->SetMaterial(0);
			
			this->components.Add(renderer);			
		}

		Quad::~Quad()
		{
		}
		#pragma endregion
	}
}