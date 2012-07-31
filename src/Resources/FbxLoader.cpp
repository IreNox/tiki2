#include "Resources/FbxLoader.h"
#include "Resources/FbxTest.h"

namespace TikiEngine
{
	namespace Resources
	{
		FbxLoader::FbxLoader()
		{

		}
		FbxLoader::~FbxLoader()
		{


		}
		Mesh* FbxLoader::LoadMesh(const wstring& name)
		{
			//FbxTest* test = new FbxTest();
			//FbxManager* fbxManager = NULL;


			FbxManager* fbxManager = NULL;
			FbxScene* scene = NULL;

			fbxManager = FbxManager::Create();

			if( !fbxManager )
			{
				FBXSDK_printf("Unable to create the FBX SDK manager\n");
				exit(0);
			}
			else
			{
				FBXSDK_printf("FBX SDK version %s\n\n", fbxManager->GetVersion());
			}


			return NULL;
		}
	}
}
