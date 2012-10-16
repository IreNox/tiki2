#pragma once

#include "Core/Scene.h"
#include "Core/LightObject.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::Objects;

		class SceneAdrian : public Scene
		{
		public:

			SceneAdrian(Engine* engine);
			~SceneAdrian();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:

			LightObject* light;

			ITexture* tex;
		};
	}
}