
#include "Game/LevelObject.h"

#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Game
	{
		LevelObject::LevelObject(Engine* engine)
			: LevelChild(engine)
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
					Mesh* mesh = engine->content->LoadMesh(L"replaceme_cube");
					renderer->SetMesh(mesh);
					mesh->Release();

					break;
				}

				renderer->SetMaterial(material);
				SafeRelease(&material);
			}

			LevelChild::databaseToField(fieldName, state, fieldId);
		}
	}
}