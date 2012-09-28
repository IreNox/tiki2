#pragma once

#include "Core/Scene.h"
#include "Game/sqlite3.h"

namespace TikiEngine
{
	namespace Game
	{
		class SceneLevel : public Scene
		{
		public:

			SceneLevel(Engine* engine);
			~SceneLevel();

			void Initialize(const InitializationArgs& args);

		private:

			string name;
			string heightmapFile;

			sqlite3* db;

		};	
	}
}