
#include "Game/BasicTransform.h"

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

			this->PRS.Position.Y = 0.0f; // read from cloddy
		}

		void BasicTransform::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "PositionX")
			{
				this->PRS.Position.X = (float)sqlite3_column_double(state, fieldId);
			}
			else if (fieldName == "PositionY")
			{
				this->PRS.Position.Y = (float)sqlite3_column_double(state, fieldId);
			}
			else if (fieldName == "Scale")
			{
				this->PRS.Scale = Vector3(
					(float)sqlite3_column_double(state, fieldId)
				);
			}
			else if (fieldName == "Rotation")
			{
				this->PRS.Rotation = Quaternion::CreateFromYawPitchRoll(
					(float)sqlite3_column_double(state, fieldId), 0, 0
				);
			}

			BasicDatabase::databaseToField(fieldName, state, fieldId);
		}
	}
}
