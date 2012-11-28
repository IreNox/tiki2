
#include "Game/LevelObject.h"

#include "Core/IContentManager.h"

#include "Game/TikiBot.h"
#include "Game/Trigger.h"

namespace TikiEngine
{
	namespace Game
	{
		LevelObject::LevelObject(GameState* state)
			: LevelChild(state)
		{
		}

		LevelObject::~LevelObject()
		{
		}

		#if _DEBUG
		void LevelObject::Update(const UpdateArgs& args)
		{
			LevelChild::Update(args);
		}
		#endif
		
		void LevelObject::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "Type")
			{
				type = sqlite3_column_int(state, fieldId);
						
                TikiBotDescription botDesc;

				switch (type)
				{
				case 0:
					this->SModel(engine->content->LoadModel(L"replaceme_cube"));
					break;
				case 1: // player
					this->SModel(engine->content->LoadModel(L"soldier"));

                    botDesc.Faction = 0;
					(new TikiBot(gameState, this, botDesc))->SetScale(0.06f);
					break;
                case 2: // enemy
                    this->SModel(engine->content->LoadModel(L"mark"));

                    botDesc.Faction = 1;
                    (new TikiBot(gameState, this, botDesc))->SetScale(0.06f);
                    break;

				case 3: // Trigger
					(new Trigger(gameState, this));
					break;
				}
			}

			LevelChild::databaseToField(fieldName, state, fieldId);
		}
	}
}
