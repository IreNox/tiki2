#include "Resources/FbxLoader.h"

namespace TikiEngine
{
	namespace Resources
	{
		FbxLoader::FbxLoader(Engine* engine)
			: EngineObject(engine), fbxManager(0), scene(0)
		{
			this->InitializeSdkObjects(this->fbxManager, this->scene);
		}
		FbxLoader::~FbxLoader()
		{
			if(this->scene)
			{
				scene->Destroy();
				scene = 0;
			}
			if(this->fbxManager)
			{
				fbxManager->Destroy();
				fbxManager = 0;
			}

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

			if(!model->IsTriangleMesh())
			{
				FbxGeometryConverter converter(this->fbxManager);
				model = converter.TriangulateMesh(model);
			}

			FbxVector4 *vertexArray = new FbxVector4[model->GetControlPointsCount()];
			memcpy(vertexArray, model->GetControlPoints(), model->GetControlPointsCount() * sizeof(FbxVector4));

			//FbxGeometryElement::EMappingMode map =  model->GetElementUV(0)->GetMappingMode(); //FbxGeometryElement::eByPolygonVertex
			

			UInt32 count = model->GetControlPointsCount();
			UInt32 size = count * sizeof(DefaultVertex);

			DefaultVertex *vertexData = new DefaultVertex[count];
			ZeroMemory(vertexData, size);

			for(int i = 0; i < model->GetControlPointsCount(); i++)
				ConvertToTiki(vertexArray[i], model->GetElementUV(0)->GetDirectArray().GetAt(i), (float*)&vertexData[i]);		

			MeshIndexed* mesh2 = new MeshIndexed(engine);
			mesh2->SetVertexData(vertexData, sizeof(DefaultVertex) * model->GetControlPointsCount());

			UInt32 *indices = (UInt32*)model->GetPolygonVertices();
			UInt32 indicesCount = model->GetPolygonCount();

			mesh2->SetIndexData(indices, indicesCount);
			mesh2->SetVertexDeclaration(DefaultVertex::Declaration,3);

			root->Destroy(true);		

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

		void FbxLoader::ConvertToTiki(const FbxVector4& vector, const FbxVector2& uv, float* output)
		{
			//vertices
			output[0] = (float)vector[0];
			output[1] = (float)vector[1];
			output[2] = (float)vector[2];
			//normals
			/*
			output[3] = (float)vector[0];
			output[4] = (float)vector[1];
			output[5] = (float)vector[2];*/
			//uvs
			output[6] = (float)uv[0];
			output[7] = (float)uv[1];




			//return Vector4((float)vector[0], (float)vector[1], (float)vector[2], (float)vector[3]);
		}

	}
}
