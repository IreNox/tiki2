#include "Resources/FbxLoader.h"

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
			FbxManager* fbxManager = NULL;
			FbxScene* scene = NULL;

			InitializeSdkObjects(fbxManager, scene);
			bool result = LoadScene(fbxManager, scene, (char*)name.c_str());

			return NULL;
		}

		void FbxLoader::InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
		{
			//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
			pManager = FbxManager::Create();
			if( !pManager )
			{
				FBXSDK_printf("Error: Unable to create FBX Manager!\n");
				exit(1);
			}
			else FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());

			//Create an IOSettings object. This object holds all import/export settings.
			FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
			
			pManager->SetIOSettings(ios);

			//Create an FBX scene. This object holds most objects imported/exported from/to files.
			pScene = FbxScene::Create(pManager, "My Scene");
			if( !pScene )
			{
				FBXSDK_printf("Error: Unable to create FBX scene!\n");
				exit(1);
			}
		}

		bool FbxLoader::LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename)
		{
			int lFileMajor, lFileMinor, lFileRevision;
			int lSDKMajor,  lSDKMinor,  lSDKRevision;
			//int lFileFormat = -1;
			int i, lAnimStackCount;
			bool lStatus;
			char lPassword[1024];

			// Get the file version number generate by the FBX SDK.
			FbxManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

			// Create an importer.
			FbxImporter* lImporter = FbxImporter::Create(pManager,"");

			// Initialize the importer by providing a filename.
			const bool lImportStatus = lImporter->Initialize(pFilename, -1, pManager->GetIOSettings());
			lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

			if( !lImportStatus )
			{
				FBXSDK_printf("Call to FbxImporter::Initialize() failed.\n");
				FBXSDK_printf("Error returned: %s\n\n", lImporter->GetLastErrorString());

				if (lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedYet ||
					lImporter->GetLastErrorID() == FbxIOBase::eFileVersionNotSupportedAnymore)
				{
					FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
					FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
				}

				return false;
			}

			FBXSDK_printf("FBX file format version for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

			if (lImporter->IsFBX())
			{
				FBXSDK_printf("FBX file format version for file '%s' is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);

				// From this point, it is possible to access animation stack information without
				// the expense of loading the entire file.

				FBXSDK_printf("Animation Stack Information\n");

				lAnimStackCount = lImporter->GetAnimStackCount();

				FBXSDK_printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
				FBXSDK_printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
				FBXSDK_printf("\n");

				for(i = 0; i < lAnimStackCount; i++)
				{
					FbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

					FBXSDK_printf("    Animation Stack %d\n", i);
					FBXSDK_printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
					FBXSDK_printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

					// Change the value of the import name if the animation stack should be imported 
					// under a different name.
					FBXSDK_printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

					// Set the value of the import state to false if the animation stack should be not
					// be imported. 
					FBXSDK_printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
					FBXSDK_printf("\n");
				}

				// Set the import states. By default, the import states are always set to 
				// true. The code below shows how to change these states.
				IOS_REF.SetBoolProp(IMP_FBX_MATERIAL,        true);
				IOS_REF.SetBoolProp(IMP_FBX_TEXTURE,         true);
				IOS_REF.SetBoolProp(IMP_FBX_LINK,            true);
				IOS_REF.SetBoolProp(IMP_FBX_SHAPE,           true);
				IOS_REF.SetBoolProp(IMP_FBX_GOBO,            true);
				IOS_REF.SetBoolProp(IMP_FBX_ANIMATION,       true);
				IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
			}

			// Import the scene.
			lStatus = lImporter->Import(pScene);

			if(lStatus == false && lImporter->GetLastErrorID() == FbxIOBase::ePasswordError)
			{
				FBXSDK_printf("Please enter password: ");

				lPassword[0] = '\0';

				FBXSDK_CRT_SECURE_NO_WARNING_BEGIN
					scanf("%s", lPassword);
				FBXSDK_CRT_SECURE_NO_WARNING_END

					FbxString lString(lPassword);

				IOS_REF.SetStringProp(IMP_FBX_PASSWORD,      lString);
				IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

				lStatus = lImporter->Import(pScene);

				if(lStatus == false && lImporter->GetLastErrorID() == FbxIOBase::ePasswordError)
				{
					FBXSDK_printf("\nPassword is wrong, import aborted.\n");
				}
			}

			// Destroy the importer.
			lImporter->Destroy();

			return lStatus;
		}
	}
}
