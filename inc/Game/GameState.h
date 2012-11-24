#pragma once

#include "Core/GUIButton.h"
#include "Core/TypeGlobals.h"

#include "Game/GameHud.h"
#include "Game/UnitFunctions.h"

#include "Game/NavigationMesh.h"

#include "Game/EventUnitSelectionChanged.h"

namespace TikiEngine
{
	typedef void (*FuncExecuteUnitFunction)(GameObject* gameObject);

	namespace Game
	{
		using namespace TikiEngine::AI;
		using namespace TikiEngine::UserInterface;

		class Level;
		class SceneLevel;
		class UnitSelection;

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

			bool LoadLevel(Level* level);
			void DisposeLevel();

			Engine* GetEngine();
			SceneLevel* GetScene();

			void GetSelectedAvailableFunctions(List<UnitFunctions>* list);

			UInt64 GetResource1();
			UInt64 GetResource2();

			void AddProjectile(GameObject* go);

			void ExecuteUnitFunction(UnitFunctions func);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:
			
			UInt64 resource1;
			UInt64 resource2;

			GameHud* hud;
			SceneLevel* scene;

			NavigationMesh* navMesh;
			
			UnitSelection* unitSelection;

			List<GameObject*> projectiles;

			//List<Unit*> levelUnits;
			//List<Building*> levelBuildings;

			Dictionary<UnitFunctions, FuncExecuteUnitFunction> funcButton;

		};
	}
}
