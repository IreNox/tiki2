#pragma once

#include "Core/Scene.h"

namespace TikiEngine
{
	namespace Game
	{
		class SceneTim : public Scene
		{
		public:

			SceneTim(Engine* engine);
			~SceneTim();
	
			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
		};
	}
}