#pragma once

#include "Core/Scene.h"

namespace TikiEngine
{
	namespace Game
	{
		class SceneLoading : public Scene
		{
		public:

			SceneLoading(Engine* engine);
			~SceneLoading();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);

		private:

			ITexture* circle;

		};
	}
}