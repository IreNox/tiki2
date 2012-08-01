#pragma once

#include "Core/Scene.h"

namespace TikiEngine
{
	namespace Game
	{
		class SceneAdrian : public Scene
		{
		public:

			SceneAdrian(Engine* engine);
			~SceneAdrian();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
		};
	}
}