#pragma once

#include "Core/Scene.h"

#include "Game/Level.h"
#include "Game/LevelPoint.h"
#include "Game/LevelObject.h"

namespace TikiEngine
{
	namespace Game
	{
		class GameState;

		class SceneLevel : public Scene
		{
			friend class GameState;

		public:

			SceneLevel(Engine* engine);
			~SceneLevel();

			void Initialize(const InitializationArgs& args);

			bool LoadLevel(Int64 id);
			void DisposeLevel();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			inline Level* GLevel() { return level; }
			inline const List<LevelPoint*>& GPoints() { return points; }
			inline List<GameObject*> GetDrawContent() { return drawContent; }
			inline List<GameObject*> GetHudContent() { return hudContent; }

		private:

			Level* level;			
			
			GameState* gameState;

			List<LevelPoint*> points;

			void DoFoWCulling();
			List<GameObject*> drawContent;
			List<GameObject*> hudContent;
		};	
	}
}