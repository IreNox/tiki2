
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

				Material* material = engine->content->LoadMaterial(L"os_default");
				material->TexDiffuse = engine->content->LoadTexture(L"Soldier_S/Soldier_S_diff");
				material->TexNormalMap = engine->content->LoadTexture(L"Soldier_S/Soldier_S_normal");
				material->TexSpecular = engine->content->LoadTexture(L"Soldier_S/Soldier_S_spec");
				
                TikiBotDescription botDesc;

				switch (type)
				{
				case 0:
					this->SModel(engine->content->LoadModel(L"replaceme_cube"));
					this->GModel()->SetMaterial(material);

					break;
				case 1: // player
					this->SModel(engine->content->LoadModel(L"mark"));
					this->GModel()->SetMaterial(material);
					
					material->FlipTexcorrdV = false;

                    botDesc.Faction = 0;
					(new TikiBot(gameState, this, botDesc))->SetScale(0.06f);
					break;
                case 2: // enemy
                    this->SModel(engine->content->LoadModel(L"soldier"));
                    this->GModel()->SetMaterial(material);

                    material->FlipTexcorrdV = false;

                    botDesc.Faction = 1;
                    (new TikiBot(gameState, this, botDesc))->SetScale(0.06f);
                    break;

				case 3: // Trigger
					(new Trigger(gameState, this))->Init(Vector3(50, 10, 50)); // Vector3(150, 30, -150)
					break;
				default:
					material->Release();
					break;
				}
			}

			LevelChild::databaseToField(fieldName, state, fieldId);
		}
	}
}
