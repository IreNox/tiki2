
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Game
	{
		GameState::GameState(Engine* engine)
			: EngineObject(engine)
		{
		}

		GameState::~GameState()
		{
		}

		Engine* GameState::GetEngine()
		{
			return engine;
		}

		/*void StartLevel(UInt32 id);

		void GetSelectedAvailableFunctions(List<UnitFunctions>* list);

		UInt64 GetResource1();
		UInt64 GetResource2();

		void ExecuteUnitFunction(UnitFunctions func);

		void Draw(const DrawArgs& args);
		void Update(const UpdateArgs& args);*/
	}
}
