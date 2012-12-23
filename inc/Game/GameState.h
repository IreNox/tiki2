#pragma once

#include "Core/GUIButton.h"
#include "Core/TypeGlobals.h"

#include "Game/GameHud.h"
#include "Game/GamePart.h"
#include "Game/NavigationMesh.h"

#include "Game/EventUnitSelectionChanged.h"

namespace TikiEngine
{
	namespace Game
	{
		using namespace TikiEngine::AI;
		using namespace TikiEngine::UserInterface;

		class Level;
		class SceneLevel;
		class UnitSelection;
		class TikiBotFactory;
		class ProjectileManager;

		class GameState : public EngineObject
		{
		public:

			UnitSelectionChangedEvent UnitSelectionChanged;

			#if _DEBUG
			bool DrawNavMesh;
			bool DrawRenderTarget;
			bool DrawPhysX;
			#endif

			GameState(Engine* engine, SceneLevel* scene);
			~GameState();

			void LoadLevel(Level* level);
			void DisposeLevel();

			inline Engine* GetEngine() { return engine; }
			inline SceneLevel* GetScene() { return scene; }
			inline NavigationMesh* GetNavMesh() { return navMesh; }
			inline List<GamePart*>& GetGameParts() { return gameParts; }
			inline TikiBotFactory* GetBotFactory() { return botFactory; }
			inline ProjectileManager* GetProjectiles() { return projectiles; }

			inline double GetResource() { return resource; }
			inline void IncrementResource(double toIncrement) { resource += toIncrement; }
			inline void DecrementResource(double toDecrement) { resource -= toDecrement; }

			void AddTrigger(GameObject* go);

			//void ExecuteUnitFunction(UnitFunctions func);
			//void GetSelectedAvailableFunctions(List<UnitFunctions>* list);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:
			
			double resource;

			GameHud* hud;
			SceneLevel* scene;
			List<GamePart*> gameParts;

			NavigationMesh* navMesh;			
			TikiBotFactory* botFactory;
			UnitSelection* unitSelection;
			ProjectileManager* projectiles;

		};
	}
}
