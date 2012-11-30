
#include "Game/LevelObject.h"

#include "Core/IContentManager.h"

#include "Game/TikiBot.h"
#include "Game/Trigger.h"
#include "Game/AnimationHandlerDefaultUnit.h"

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
					this->GModel()->animationEvent->SetHandlerOnly(new AnimationHandlerDefaultUnit(this->GModel()));

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
				case 4:
					{
						IMeshRenderer* render = engine->librarys->CreateComponent<IMeshRenderer>(this);

						Material* mat = engine->content->LoadMaterial(L"os_default");
						mat->TexDiffuse   = engine->content->LoadTexture(L"building03_05/building03_05_Diff");
						mat->TexNormalMap = engine->content->LoadTexture(L"building03_05/building03_05_Normal");
						//mat->TexSpecular = engine->content->LoadTexture(L"building_03/building_03_Spec");
						render->SetMaterial(mat);
						render->SetMesh(engine->content->LoadMesh(L"building03_05"));
					}
					break;
				case 5:
					this->SModel(engine->content->LoadModel(L"env_pipe_01"));
					break;
				}
			}

			LevelChild::databaseToField(fieldName, state, fieldId);
		}
	}
}
