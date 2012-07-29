#pragma once

#include "Core/GameObject.h"
#include "Core/IMeshRenderer.h"
#include "Core/PostProcessVertex.h"

namespace TikiEngine
{
	namespace Objects
	{
		using namespace TikiEngine::Graphics;
		using namespace TikiEngine::Vertices;

		class Quad : public GameObject
		{
		public:

			Quad(Engine* engine);
			~Quad();

			bool Initialize(const InitializationArgs& args);

		private:

			IMesh* mesh;
			Material* material;

			IMeshRenderer* renderer;

		};
	}
}