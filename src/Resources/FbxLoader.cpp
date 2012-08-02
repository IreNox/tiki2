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

			UINT polygonVertexCount = model->GetPolygonVertexCount();
			UINT size = polygonVertexCount * sizeof(DefaultVertex);

			DefaultVertex *vertexData = new DefaultVertex[polygonVertexCount];
			ZeroMemory(vertexData, size);

			List<UInt32> indices = List<UInt32>();

			Int32 counter = 0;

			for(Int32 i = 0; i < model->GetPolygonCount(); i++)
			{
				Int32 verticesInPolygon = model->GetPolygonSize(i);
				if(verticesInPolygon == 3)
				{
					indices.Add(counter);
					indices.Add(counter+1);
					indices.Add(counter+2);
				}else if(verticesInPolygon == 4)
				{
					indices.Add(counter);
					indices.Add(counter+1);
					indices.Add(counter+2);
					indices.Add(counter+1);
					indices.Add(counter+2);
					indices.Add(counter+3);
				}

				for(Int32 k = 0; k < verticesInPolygon;k++)
				{
					int position = model->GetPolygonVertex(i,k);

					ConvertToTiki(
						model->GetControlPointAt(position), 
						model->GetElementUV(0)->GetDirectArray().GetAt(i), 
						(float*)&vertexData[counter]);	
					counter++;
				}
			}

			UINT indexBufferSize = indices.Count();
			UInt32 *indexBufferData = indices.ToArray();

			MeshIndexed* meshIndexed = new MeshIndexed(engine);

			meshIndexed->SetVertexData(vertexData, size);
			meshIndexed->SetIndexData(indexBufferData, indexBufferSize);

			delete vertexData;
			vertexData = 0;
			delete indexBufferData;
			indexBufferData = 0;

			
			//FbxVector4 *vertexArray = new FbxVector4[model->GetControlPointsCount()];
			//memcpy(vertexArray, model->GetControlPoints(), model->GetControlPointsCount() * sizeof(FbxVector4));

			//int bla = model->GetTextureUVCount(FbxLayerElement::eTextureDiffuse);
			////FbxGeometryElement::EMappingMode map =  model->GetElementUV(0)->GetMappingMode(); //FbxGeometryElement::eByPolygonVertex
			//int uvIndexCount = model->GetElementUV(0)->GetIndexArray().GetCount();
			//int uvDirectCount = model->GetElementUV(0)->GetDirectArray().GetCount();
			////model->GetElementUV(0)->RemapIndexTo(FbxLayerElement::eByControlPoint);
			//
			//
			//


			//UInt32 count = model->GetControlPointsCount();
			//UInt32 size = count * sizeof(DefaultVertex);

			//DefaultVertex *vertexData = new DefaultVertex[count];
			//ZeroMemory(vertexData, size);

			//for(UInt32 i = 0; i < model->GetControlPointsCount(); i++)
			//	ConvertToTiki(vertexArray[i], model->GetElementUV(0)->GetDirectArray().GetAt(i), (float*)&vertexData[i]);		

			//MeshIndexed* mesh2 = new MeshIndexed(engine);
			//mesh2->SetVertexData(vertexData, sizeof(DefaultVertex) * model->GetControlPointsCount());

			//UInt32 *indices = (UInt32*)model->GetPolygonVertices();
			//UInt32 indicesCount = model->GetPolygonCount();

			//mesh2->SetIndexData(indices, indicesCount);
			//mesh2->SetVertexDeclaration(DefaultVertex::Declaration,3);

			root->Destroy(true);		

			return meshIndexed;//mesh2;
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
