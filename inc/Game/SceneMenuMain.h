#pragma once

#include "Core/Scene.h"

namespace TikiEngine
{
	namespace Game
	{
		class SceneMenuMain : public Scene
		{
		public:

			SceneMenuMain(Engine* engine);
			~SceneMenuMain();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:



		};
	}
}