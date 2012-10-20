
#include "Game/BasicTransform.h"

#include "Game/SceneLevel.h"
#include "Core/ITerrainRenderer.h"

namespace TikiEngine
{
	namespace Game
	{
		BasicTransform::BasicTransform(GameState* state)
			: BasicDatabase(state)
		{
		}

		BasicTransform::~BasicTransform()
		{
		}

		void BasicTransform::LoadFromDatabase(sqlite3_stmt* state)
		{
			BasicDatabase::LoadFromDatabase(state);

			SceneLevel* scene = (SceneLevel*)engine->scene;
			if (scene && scene->GetLevel()->GetTerrain())
			{
				this->PRS.SPosition().Y = scene->GetLevel()->GetTerrain()->SampleHeight(this->PRS.GPosition());
			}			
		}

		void BasicTransform::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "PositionX")
			{
				this->PRS.SPosition().X = (float)sqlite3_column_double(state, fieldId);
			}
			else if (fieldName == "PositionY")
			{
				this->PRS.SPosition().Z = (float)sqlite3_column_double(state, fieldId);
			}
			else if (fieldName == "Scale" && this->PRS.GScale() == Vector3::One)
			{
				this->PRS.SScale() = Vector3(
					(float)sqlite3_column_double(state, fieldId)
				);
			}
			else if (fieldName == "Rotation")
			{
				this->PRS.SRotation() = Quaternion::CreateFromYawPitchRoll(
					(float)sqlite3_column_double(state, fieldId), 0, 0
				);
			}

			BasicDatabase::databaseToField(fieldName, state, fieldId);
		}
	}
}
