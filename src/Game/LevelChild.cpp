
#include "Game/LevelChild.h"

#include "Core/LibraryManager.h"

namespace TikiEngine
{
	namespace Game
	{
		LevelChild::LevelChild(Engine* engine)
			: BasicTransform(engine)
		{
		}

		LevelChild::~LevelChild()
		{
			SafeRelease(&renderer);
		}

		void LevelChild::LoadFromDatabase(sqlite3_stmt* state)
		{
			renderer = engine->librarys->CreateComponent<IMeshRenderer>(this);

			BasicTransform::LoadFromDatabase(state);

			if (!renderer->GetReady())
			{
				this->RemoveComponent(renderer);
				SafeRelease(&renderer);
			}
		}

		Int64 LevelChild::GetLevelID()
		{
			return levelId;
		}

		void LevelChild::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "LevelID")
			{
				levelId = sqlite3_column_int64(state, fieldId);
			}

			BasicTransform::databaseToField(fieldName, state, fieldId);
		}
	}
}