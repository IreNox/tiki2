#pragma once

#include "Core/GameObject.h"
#include "Core/IMeshRenderer.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/PostProcessVertex.h"

namespace TikiEngine
{
	namespace Objects
	{
		using namespace TikiEngine::Effects;
		using namespace TikiEngine::Vertices;

		class Quad : public GameObject
		{
		public:

			Quad(Engine* engine);
			~Quad();

			bool Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			IMesh* mesh;
			IMaterial* material;

			IMeshRenderer* renderer;

		};
	}
}