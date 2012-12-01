#pragma once

#include "Core/GUIButton.h"
#include "Core/TypeGlobals.h"

#include "Game/GameHud.h"
#include "Game/UnitFunctions.h"

#include "Game/NavigationMesh.h"

#include "Game/EventUnitSelectionChanged.h"



namespace TikiEngine
{
	//typedef void (*FuncExecuteUnitFunction)(GameObject* gameObject);

	namespace Game
	{
		using namespace TikiEngine::AI;
		using namespace TikiEngine::UserInterface;

		class Level;
		class SceneLevel;
		class UnitSelection;
		class TikiBotFactory;

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
			inline TikiBotFactory* GetBotFactory() { return botFactory; }

			inline double GetResource() { return resource; }

			void AddProjectile(GameObject* go);
			void AddTrigger(GameObject* go);

			void ExecuteUnitFunction(UnitFunctions func);
			void GetSelectedAvailableFunctions(List<UnitFunctions>* list);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:
			
			double resource;

			GameHud* hud;
			SceneLevel* scene;

			NavigationMesh* navMesh;			
			TikiBotFactory* botFactory;
			UnitSelection* unitSelection;

			List<GameObject*> projectiles;

			//Dictionary<UnitFunctions, FuncExecuteUnitFunction> funcButton;

		};
	}
}
