#include "Resources/FbxLoader.h"

namespace TikiEngine
{
	namespace Resources
	{
		FbxLoader::FbxLoader(Engine* engine)
			: EngineObject(engine)
		{
			this->InitializeSdkObjects(this->fbxManager, this->scene);
		}
		FbxLoader::~FbxLoader()
		{
			if(this->fbxManager)
				fbxManager->Destroy();

		}

		Mesh* FbxLoader::LoadMesh(const wstring& name)
		{
			bool result = LoadScene(fbxManager, scene, name);

			FbxNode *root = scene->GetRootNode();
			FbxNode *mesh = NULL;
			FbxMesh *model = NULL;
			for(int i = 0; i < root->GetChildCount(); i++)
			{
				FbxNode *child = root->GetChild(i);
				if(child->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
				{
					mesh = root->GetChild(i);
					if(mesh->GetMesh() != NULL)
					{
						model = mesh->GetMesh();
					}
					break;
				}
			}
			int *vertices = model->GetPolygonVertices();

			FbxVector4 *vertexArray = new FbxVector4[model->GetControlPointsCount()];
			memcpy(vertexArray, model->GetControlPoints(), model->GetControlPointsCount() * sizeof(FbxVector4));

			UInt32 count = model->GetControlPointsCount();
			UInt32 size = count * sizeof(DefaultVertex);

			DefaultVertex *vertexData = new DefaultVertex[count];
			ZeroMemory(vertexData, size);

			for(int i = 0; i < model->GetControlPointsCount(); i++)
			{
				ConvertToTiki(vertexArray[i], (float*)&vertexData[i]);
			}				

			Mesh* mesh2 = new Mesh(engine);
			mesh2->SetVertexData(vertexData, sizeof(DefaultVertex) * model->GetControlPointsCount());

			return mesh2;
		}

		void FbxLoader::InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
		{
			pManager = FbxManager::Create();

			FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
			pManager->SetIOSettings(ios);

			pScene = FbxScene::Create(pManager, "");
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

		void FbxLoader::ConvertToTiki(const FbxVector4& vector, float* output)
		{
			output[0] = (float)vector[0];
			output[1] = (float)vector[1];
			output[2] = (float)vector[2];

			//return Vector4((float), (float)vector[1], (float)vector[2], (float)vector[3]);
		}

	}
}
