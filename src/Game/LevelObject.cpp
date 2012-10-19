
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
		
		void LevelObject::databaseToField(string fieldName, sqlite3_stmt* state, int fieldId)
		{
			if (fieldName == "Type")
			{
				type = sqlite3_column_int(state, fieldId);

				Material* material = engine->content->LoadMaterial(L"os_default");
				ITexture* tex = engine->content->LoadTexture(L"checker");
				material->GetShader()->SetTexture("tex", tex);
				
				switch (type)
				{
				case 0:
					this->Model = engine->content->LoadModel(L"replaceme_cube");
					this->Model->SetMaterial(material);
					material->Release();

					break;
				case 1:
					this->Model = engine->content->LoadModel(L"normals");
					this->Model->SetMaterial(material);
					material->Release();

					(new TikiBot(gameState, this))->Release();
					break;
				}
			}

			LevelChild::databaseToField(fieldName, state, fieldId);
		}
	}
}