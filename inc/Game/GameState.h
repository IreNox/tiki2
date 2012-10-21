#pragma once

#include "Core/GUIButton.h"
#include "Core/TypeGlobals.h"

#include "Game/GameHud.h"
#include "Game/UnitFunctions.h"

#include "Game/NavigationMesh.h"

namespace TikiEngine
{
	typedef void (*FuncExecuteUnitFunction)(GameObject* gameObject);

	namespace Game
	{
		using namespace TikiEngine::AI;
		using namespace TikiEngine::UserInterface;

		class Level;
		class SceneLevel;

		class GameState : public EngineObject
		{
		public:

			GameState(Engine* engine, SceneLevel* scene);
			~GameState();

			bool LoadLevel(Level* level);
			void DisposeLevel();

			Engine* GetEngine();

			void GetSelectedAvailableFunctions(List<UnitFunctions>* list);

			UInt64 GetResource1();
			UInt64 GetResource2();

			void ExecuteUnitFunction(UnitFunctions func);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:
			
#if _DEBUG
			bool drawNavMesh;
			bool drawRenderTarget;
#endif

			UInt64 resource1;
			UInt64 resource2;

			GameHud* hud;
			SceneLevel* scene;

			NavigationMesh* navMesh;
			
			//List<Unit*> selectedUnits;

			//List<Unit*> levelUnits;
			//List<Building*> levelBuildings;

			Dictionary<UnitFunctions, FuncExecuteUnitFunction> funcButton;

		};
	}
}