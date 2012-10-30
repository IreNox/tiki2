
#include "Game/LevelObject.h"

#include "Core/IContentManager.h"

#include "Game/TikiBot.h"

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
			if (args.Input.GetKeyPressed(KEY_F3))
			{
				this->GModel()->GetMaterial()->TexNormalMap = 0;
			}

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
				TikiObject::WatchPointer.Add(material->GetShader());
				
				switch (type)
				{
				case 0:
					this->SModel(engine->content->LoadModel(L"Soldier_S"));
					this->GModel()->SetMaterial(material);

					break;
				case 1:
					this->SModel(engine->content->LoadModel(L"Soldier_S"));
					this->GModel()->SetMaterial(material);
					
					material->FlipTexcorrdV = false;

					(new TikiBot(gameState, this))->SetScale(0.06f);
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
