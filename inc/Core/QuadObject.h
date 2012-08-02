#pragma once

#include "Core/GameObject.h"
#include "Core/IMeshRenderer.h"
#include "Core/PostProcessVertex.h"

namespace TikiEngine
{
	namespace Objects
	{
		using namespace TikiEngine::Vertices;
		using namespace TikiEngine::Resources;

		class Quad : public GameObject
		{
		public:

			Quad(Engine* engine);
			~Quad();

			bool Initialize(const InitializationArgs& args);

		private:

			Mesh* mesh;
			Material* material;

			IMeshRenderer* renderer;

		};
	}
}