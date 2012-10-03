#pragma once

#include "Core/Scene.h"
#include "Game/sqlite3.h"

#include "Game/Level.h"
#include "Game/LevelEnemy.h"
#include "Game/LevelObject.h"

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

			bool LoadLevel(Int64 id);
			void DisposeLevel();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			Level* GetLevel();

		private:

			Level* level;
			List<LevelEnemy*> enemies;
			List<LevelObject*> objects;

			sqlite3* db;

		};	
	}
}