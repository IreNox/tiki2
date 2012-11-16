
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
			LevelChild::Update(args);
		}
		#endif
		
		void LevelObject::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "Type")
			{
				type = sqlite3_column_int(state, fieldId);

				Material* material = engine->content->LoadMaterial(L"os_skinning");
				material->TexDiffuse = engine->content->LoadTexture(L"Soldier_S/Soldier_S_diff");
				material->TexNormalMap = engine->content->LoadTexture(L"Soldier_S/Soldier_S_normal");
				material->TexSpecular = engine->content->LoadTexture(L"Soldier_S/Soldier_S_spec");
				
				switch (type)
				{
				case 0:
					this->SModel(engine->content->LoadModel(L"replaceme_cube"));
					this->GModel()->SetMaterial(material);

					break;
				case 1:
					this->SModel(engine->content->LoadModel(L"mark"));
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
