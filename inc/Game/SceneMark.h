#pragma once

#include "Core/Scene.h"

namespace TikiEngine
{
	namespace Game
	{
		class SceneMark : public Scene
		{
		public:

			SceneMark(Engine* engine);
			~SceneMark();

			void Initialize(const InitializationArgs& args);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
		};
	}
}