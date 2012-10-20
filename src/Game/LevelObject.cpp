
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
				this->Model->GetMaterial()->TexNormalMap = 0;
			}

			LevelObject::Update(args);
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
					this->Model = engine->content->LoadModel(L"replaceme_cube");
					this->Model->SetMaterial(material);
					material->Release();

					break;
				case 1:
					this->Model = engine->content->LoadModel(L"Soldier_S");
					this->Model->SetMaterial(material);
					
					material->FlipTexcorrdV = false;
					material->Release();

					TikiBot* bot = new TikiBot(gameState, this);
					bot->SetScale(0.06f);
					bot->Release();
					break;
				}
			}

			LevelChild::databaseToField(fieldName, state, fieldId);
		}
	}
}