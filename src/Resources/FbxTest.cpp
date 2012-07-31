#include "Resources/FbxTest.h"

namespace TikiEngine
{
	namespace Resources
	{
		void InitializeSdkObjects(FbxManager*& pSdkManager, FbxScene*& pScene)
		{
			// The first thing to do is to create the FBX SDK manager which is the 
			// object allocator for almost all the classes in the SDK.
			pSdkManager = FbxManager::Create();
			if( !pSdkManager )
			{
				FBXSDK_printf("Unable to create the FBX SDK manager\n");
				exit(0);
			}
			else
			{
				FBXSDK_printf("FBX SDK version %s\n\n", pSdkManager->GetVersion());
			}

			// create an IOSettings object
			FbxIOSettings * ios = FbxIOSettings::Create(pSdkManager, IOSROOT );
			pSdkManager->SetIOSettings(ios);

			// Load plugins from the executable directory
			FbxString lPath = FbxGetApplicationDirectory();
			pSdkManager->LoadPluginsDirectory(lPath.Buffer());

			// Create the entity that will hold the scene.
			pScene = FbxScene::Create(pSdkManager,"");
		}

		FbxTest::FbxTest()
		{
			FbxManager* lSdkManager = NULL;
			FbxScene* lScene = NULL;
			bool lResult;

			// Prepare the FBX SDK.
			InitializeSdkObjects(lSdkManager, lScene);
		}

		FbxTest::~FbxTest()
		{

		}

		void FbxTest::DoWhatIWant()
		{

		}
	}

}
