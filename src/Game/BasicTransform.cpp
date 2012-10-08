
#include "Game/BasicTransform.h"

#include "Game/SceneLevel.h"
#include "Core/ITerrainRenderer.h"

namespace TikiEngine
{
	namespace Game
	{
		BasicTransform::BasicTransform(Engine* engine)
			: BasicDatabase(engine)
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
				this->PRS.SetPosition(
					this->PRS.GetPosition() + Vector3(0, scene->GetLevel()->GetTerrain()->SampleHeight(this->PRS.GetPosition()), 0)
				);
			}			
		}

		void BasicTransform::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "PositionX")
			{
				this->PRS.SetPosition(
					this->PRS.GetPosition() + Vector3((float)sqlite3_column_double(state, fieldId), 0, 0)
				);
			}
			else if (fieldName == "PositionY")
			{
				this->PRS.SetPosition(
					this->PRS.GetPosition() + Vector3(0, 0, (float)sqlite3_column_double(state, fieldId))
				);
			}
			else if (fieldName == "Scale")
			{
				this->PRS.SetScale(Vector3(
					(float)sqlite3_column_double(state, fieldId)
				));
			}
			else if (fieldName == "Rotation")
			{
				this->PRS.SetRotation(Quaternion::CreateFromYawPitchRoll(
					(float)sqlite3_column_double(state, fieldId), 0, 0
				));
			}

			BasicDatabase::databaseToField(fieldName, state, fieldId);
		}
	}
}
