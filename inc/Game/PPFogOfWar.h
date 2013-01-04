#pragma once

#include "Core/PostProcess.h"
#include "Game/GameState.h"
#include "Game/EventUnitSelectionChanged.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Game;

		class PPFogOfWar : public PostProcess, public UnitSelectionChangedEventHandler
		{
		public:

			PPFogOfWar(GameState* state);
			~PPFogOfWar();

			void UpdatePass(UInt32 index, const DrawArgs& args);

			void Handle(GameState* sender, const UnitSelectionChangedArgs& args);

		private:

			GameState* state;

			IShader* shader;
			IConstantBuffer* buffer;

			List<GameObject*> selected;

			struct CBUnit
			{
				Vector2 Position;				
				float Range;
				float Type;
			};

			struct CBFogOfWar
			{
				float UnitsCount;
				Vector3 MapSize;

				CBUnit Units[128];

			};

		};
	}
}