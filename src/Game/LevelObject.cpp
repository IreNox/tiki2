
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

				Material* material = engine->content->LoadMaterial(L"Data/Effects/os_default.fx");
				ITexture* tex = engine->content->LoadTexture(L"Data/Resources/Textures/box_diffuse.jpg");
				material->GetShader()->SetTexture("tex", tex);
				
				switch (type)
				{
				case 0:
					Mesh* mesh = engine->content->LoadMesh(L"Data/Resources/Models/box_ursprung.fbx");
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