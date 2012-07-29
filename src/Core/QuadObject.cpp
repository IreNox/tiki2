
#include "Core/QuadObject.h"

#include "Core/IMesh.h"
#include "Core/IMeshRenderer.h"

#include "Core/LibraryManager.h"

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

			mesh = engine->librarys->CreateComponent<IMesh>(this);
			mesh->SetVertexData(&vertices, sizeof(vertices));
			mesh->SetVertexDeclaration(PostProcessVertex::Declaration, sizeof(PostProcessVertex::Declaration));

			renderer = engine->librarys->CreateComponent<IMeshRenderer>(this);
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