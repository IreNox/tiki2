#pragma once

#include "Core/GUIButton.h"
#include "Core/TypeGlobals.h"

#include "Game/GameHud.h"
#include "Game/SceneLevel.h"
#include "Game/UnitFunctions.h"

namespace TikiEngine
{
	typedef void (*FuncExecuteUnitFunction)(GameObject* gameObject);

	namespace Game
	{
		using namespace TikiEngine::UserInterface;

		class GameState : public EngineObject
		{
		public:

			GameState(Engine* engine);
			~GameState();

			void StartLevel(UInt32 id);

			Engine* GetEngine();

			void GetSelectedAvailableFunctions(List<UnitFunctions>* list);

			UInt64 GetResource1();
			UInt64 GetResource2();

			void ExecuteUnitFunction(UnitFunctions func);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

		private:
			
			UInt64 resource1;
			UInt64 resource2;

			GameHud* hud;
			SceneLevel* scene;


			//List<Unit*> selectedUnits;

			//List<Unit*> levelUnits;
			//List<Building*> levelBuildings;

			Dictionary<UnitFunctions, FuncExecuteUnitFunction> funcButton;

		};
	}
}