
#define TIKI_EDITOR

#include "FbxLoader.h"

namespace TikiEditor
{
	FbxLoader::FbxLoader()
		: fbxManager(0)
	{
		this->InitializeSdkObjects(this->fbxManager);
	}

	FbxLoader::~FbxLoader()
	{

		if(this->fbxManager)
		{
			fbxManager->Destroy();
		}

	}
	void FbxLoader::InitializeSdkObjects(FbxManager*& pManager)
	{
		pManager = FbxManager::Create();

		FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
		pManager->SetIOSettings(ios);

	}
	FbxManager& FbxLoader::Manager()
	{
		return *this->fbxManager;
	}

	void FbxLoader::CreateNewScene(FbxScene** scene)
	{
		*scene = FbxScene::Create(this->fbxManager, "");
	}

	bool FbxLoader::GetScene(wstring filename, FbxHelper* helper)
	{
		FbxScene* scene = FbxScene::Create(this->fbxManager, "");

		if(LoadScene(fbxManager, scene, filename))
		{
			helper->SetScene(scene);
			return true;
		}
		else
			return false;
	}

	bool FbxLoader::GetScene(wstring filename, FbxScene** scene)
	{
		CreateNewScene(scene);
		return this->LoadScene(fbxManager, *scene, filename);
	}

	bool FbxLoader::LoadScene(FbxManager* pSdkManager, FbxDocument* pScene, wstring filename)
	{
		//TODO: Convert Function wstring to char*
		bool lStatus;
		size_t blatmpscheissegal;
		char* pFbxFilePath = new char[filename.length()+1];
		wcstombs_s(&blatmpscheissegal,pFbxFilePath,  filename.length() + 1, filename.c_str(), filename.length() + 1);

		// Create an importer.
		FbxImporter* lImporter = FbxImporter::Create(pSdkManager,"");

		// Initialize the importer by providing a filename.
		bool lImportStatus = lImporter->Initialize(pFbxFilePath, -1, pSdkManager->GetIOSettings() );
		delete pFbxFilePath;

		if( !lImportStatus )
		{
			// Destroy the importer
			lImporter->Destroy();
			return false;
		}

		if (lImporter->IsFBX())
		{
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

		// Import the scene
		lStatus = lImporter->Import(pScene);

		// Destroy the importer
		lImporter->Destroy();

		return lStatus;
	}
}
