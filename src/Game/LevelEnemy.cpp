
#include "Game/LevelEnemy.h"

namespace TikiEngine
{
	namespace Game
	{
		LevelEnemy::LevelEnemy(Engine* engine)
			: LevelChild(engine)
		{
		}

		LevelEnemy::~LevelEnemy()
		{
		}

		void LevelEnemy::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			LevelChild::databaseToField(fieldName, state, fieldId);
		}
	}
}