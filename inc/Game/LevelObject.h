#pragma once

#include "Game/LevelChild.h"

namespace TikiEngine
{
	namespace Game
	{
		class LevelObject : public LevelChild
		{
		public:

			LevelObject(GameState* state);
			~LevelObject();

			#if _DEBUG
			void Update(const UpdateArgs& args);
			#endif

		private:

			Int32 type;

		protected:

			void databaseToField(string fieldName, sqlite3_stmt* state, int fieldId);

		};
	}
}