
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{
		#pragma region Class
		GameState::GameState(Engine* engine, SceneLevel* scene)
			: EngineObject(engine), scene(scene)
		{
			hud = new GameHud(this);
		}

		GameState::~GameState()
		{
			SafeRelease(&hud);
		}
		#pragma endregion

		#pragma region Member - Get
		Engine* GameState::GetEngine()
		{
			return engine;
		}

		UInt64 GameState::GetResource1()
		{
			return resource1;
		}

		UInt64 GameState::GetResource2()
		{
			return resource1;
		}
		#pragma endregion

		#pragma region Member - Load/Dispose
		bool GameState::LoadLevel(UInt32 id)
		{
			return true;
		}

		void GameState::DisposeLevel()
		{
		}
		#pragma endregion

		#pragma region Member - Draw/Update
		void GameState::Draw(const DrawArgs& args)
		{
			hud->Draw(args);
		}

		void GameState::Update(const UpdateArgs& args)
		{
			hud->Update(args);
		}
		#pragma endregion


		/*void GetSelectedAvailableFunctions(List<UnitFunctions>* list);
		void ExecuteUnitFunction(UnitFunctions func);*/

	}
}
