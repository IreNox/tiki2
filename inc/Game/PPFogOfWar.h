#pragma once

#include "Core/PostProcess.h"
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace Graphics
	{
		using namespace TikiEngine::Game;

		class PPFogOfWar : public PostProcess
		{
		public:

			PPFogOfWar(GameState* state);
			~PPFogOfWar();

			void UpdatePass(UInt32 index, const DrawArgs& args);

		private:

			GameState* state;

			IShader* shader;
			IConstantBuffer* buffer;

			struct CBUnit
			{
				Vector3 Position;
				float Range;
			};

			struct CBFogOfWar
			{
				float UnitsCount;
				Vector3 MapSize;

				CBUnit Units[32];

			};

		};
	}
}