#include "Graphics/FbxLoader.h"

namespace TikiEngine
{
	namespace Resources
	{
		FbxLoader::FbxLoader(Engine* engine)
			: EngineObject(engine), fbxManager(0), scene(0), skeletonList()
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

		int FbxLoader::CountNodes(FbxNode* node, FbxNodeAttribute::EType type)
		{
			int result = 0;
			FbxNodeAttribute *attribute = node->GetNodeAttribute();
			
			if(attribute  && attribute->GetAttributeType() == type)
				result = 1;
			//if(attribute && attribute->GetAttributeType() == FbxNodeAttribute::eSkeleton)
			//{

			//	
			//}

			for(int i = 0; i < node->GetChildCount();i++)
				result += CountNodes(node->GetChild(i), type);

			return result;
		}

		void FbxLoader::InitializeAnimationStack()
		{
			scene->FillAnimStackNameArray(this->mAnimStackNameArray);
		}

		bool FbxLoader::SetCurrentAnimStack(int pIndex)
		{
			const int lAnimStackCount = mAnimStackNameArray.GetCount();
			if (!lAnimStackCount || pIndex >= lAnimStackCount)
			{
				return false;
			}

			FbxAnimStack* lCurrentAnimationStack = this->scene->FindMember<FbxAnimStack>(mAnimStackNameArray[pIndex]->Buffer());
			//// select the base layer from the animation stack
			if (lCurrentAnimationStack == NULL)
			{
				// this is a problem. The anim stack should be found in the scene!
				return false;
			}

			mCurrentAnimLayer = lCurrentAnimationStack->GetMember<FbxAnimLayer>();
			scene->GetEvaluator()->SetContext(lCurrentAnimationStack);

			return true;
		}

		Mesh* FbxLoader::LoadSkeleton(const wstring& name)
		{
			bool result = LoadScene(fbxManager, scene, name);

			InitializeAnimationStack();
			SetCurrentAnimStack(0);

			FbxNode *root = scene->GetRootNode();

			HandleNodeRecursive(root, FBXSDK_TIME_ONE_SECOND, GetGlobalPositionFbx(root));

			UINT skeletonCount = this->skeletonList.Count();
			UINT size = skeletonCount * sizeof(DefaultVertex);

			DefaultVertex *vertexData = new DefaultVertex[skeletonCount];
			ZeroMemory(vertexData, size);

			List<UInt32> indices = List<UInt32>();

			for(int i = 0; i < skeletonCount; i++)
			{
				ConvertToTiki(skeletonList[i], FbxVector4(), FbxVector4(), FbxVector4(), FbxVector2(), &vertexData[i]);
				indices.Add(i);
			}
				
			UINT indexBufferSize = indices.Count();
			UInt32 *indexBufferData = indices.ToArray();

			MeshIndexed* meshIndexed = new MeshIndexed(engine);

			meshIndexed->SetVertexData(vertexData, size);
			meshIndexed->SetIndexData(indexBufferData, indexBufferSize);
			meshIndexed->SetVertexDeclaration(DefaultVertex::Declaration,5);
			meshIndexed->SetPrimitiveTopology(PT_LineList);

			delete vertexData;
			vertexData = 0;
			delete indexBufferData;
			indexBufferData = 0;

			root->Destroy(true);		

			return meshIndexed;
		}

		Mesh* FbxLoader::LoadMesh(const wstring& name)
		{
			bool result = LoadScene(fbxManager, scene, name);

			FbxNode *root = scene->GetRootNode();
			FbxNode *mesh = NULL;
			FbxMesh *model = NULL;

			//FbxArray<FbxString*> mAnimStackNameArray;
			//scene->FillAnimStackNameArray(mAnimStackNameArray);

			//int countehhjhnr = mAnimStackNameArray.GetCount();

			//const char * animationName = scene->ActiveAnimStackName.GetNameAsCStr();

			//int rootchildcount = root->GetChildCount();

			//int bones = this->CountNodes(root, FbxNodeAttribute::eSkeleton);
			//int meshes = this->CountNodes(root, FbxNodeAttribute::eMesh);


			for(int i = 0; i < root->GetChildCount(); i++)
			{
				FbxNode *child = root->GetChild(i);

				FbxNodeAttribute::EType nodeType = child->GetNodeAttribute()->GetAttributeType();

				if(nodeType == FbxNodeAttribute::eMesh)
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

			UINT32 counter = 0;

			for(UInt32 i = 0; i < polygonVertexCount; i++)
			{
				Int32 verticesInPolygon = model->GetPolygonSize(i);


				indices.Add(counter);
				indices.Add(counter+1);
				indices.Add(counter+2);
					
				if(verticesInPolygon == 4)
				{
					indices.Add(counter);
					indices.Add(counter+2);
					indices.Add(counter+3);	
				}


				for(Int32 k = 0; k < verticesInPolygon; k++)
				{
					int position = model->GetPolygonVertex(i,k);

					FbxVector4 pos = model->GetControlPointAt(position);

					bool hasUVInformation = model->GetElementUVCount() != 0;

					FbxVector2 uv = FbxVector2(0,0);
					if(hasUVInformation)
					{
						int uvIndex = model->GetElementUV(0)->GetIndexArray().GetAt(counter);
						uv = model->GetElementUV(0)->GetDirectArray().GetAt(uvIndex);
					}

					//FbxLayerElementArrayTemplate<FbxVector4>* arr;

					//bool test = model->GetBinormals(&arr);

					FbxVector4 normals = model->GetElementNormal(0)->GetDirectArray().GetAt(counter);
					FbxVector4 binormal = FbxVector4(); //arr->GetAt(counter); // bn->GetDirectArray().GetAt(counter);
					FbxVector4 tangent = FbxVector4(); //model->GetElementTangent(0)->GetDirectArray().GetAt(counter);

					ConvertToTiki(
						pos, 
						normals,
						binormal,
						tangent,
						uv,
						&vertexData[counter]
					);	

					counter++;
				}
			}

			//const bool lHasVertexCache = model->GetDeformerCount(FbxDeformer::eVertexCache) &&
			//	(static_cast<FbxVertexCacheDeformer*>(model->GetDeformer(0, FbxDeformer::eVertexCache)))->IsActive();
			//const bool lHasShape = model->GetShapeCount() > 0;
			//const bool lHasSkin = model->GetDeformerCount(FbxDeformer::eSkin) > 0;
			//const bool lHasDeformation = lHasVertexCache || lHasShape || lHasSkin;
			

			UINT indexBufferSize = indices.Count();
			UInt32 *indexBufferData = indices.ToArray();

			MeshIndexed* meshIndexed = new MeshIndexed(engine);

			meshIndexed->SetVertexData(vertexData, size);
			meshIndexed->SetIndexData(indexBufferData, indexBufferSize);
			meshIndexed->SetVertexDeclaration(DefaultVertex::Declaration,5);

			delete vertexData;
			vertexData = 0;
			delete indexBufferData;
			indexBufferData = 0;

			root->Destroy(true);		

			return meshIndexed;
		}

		void FbxLoader::HandleNodeRecursive(FbxNode* node, FbxTime& pTime, FbxAMatrix& pParentGlobalPosition)
		{
			FbxAMatrix lGlobalPosition = GetGlobalPositionFbx(node);

			//root has no NodeAttribute
			if(node->GetNodeAttribute())
			{
				FbxAMatrix lGeometryOffset = GetGeometryFbx(node);
				FbxAMatrix lGlobalOffPosition = lGlobalPosition * lGeometryOffset;

				HandleNode(node, pTime, pParentGlobalPosition, lGlobalOffPosition);
			}
			for(int i = 0; i < node->GetChildCount(); i++)
			{
				HandleNodeRecursive(node->GetChild(i), pTime, lGlobalPosition);
			}
		}

		void FbxLoader::HandleNode(FbxNode* pNode, FbxTime& pTime, FbxAMatrix& pParentGlobalPosition, FbxAMatrix& pGlobalPosition)
		{
			if(pNode->GetNodeAttribute())
			{
				if(pNode->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
				{
					HandleSkeleton(pNode, pParentGlobalPosition, pGlobalPosition);
				}
			}
		}

		void FbxLoader::HandleSkeleton(FbxNode* pNode, FbxAMatrix& pParentGlobalPosition, FbxAMatrix& pGlobalPosition)
		{
			FbxSkeleton* lSkeleton = (FbxSkeleton*) pNode->GetNodeAttribute();

			//Only draw the skeleton if it's a limb node and if 
			//the parent also has an attribute of type skeleton.
			if (lSkeleton->GetSkeletonType() == FbxSkeleton::eLimbNode &&
				pNode->GetParent() &&
				pNode->GetParent()->GetNodeAttribute() &&
				pNode->GetParent()->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
			{
				//this->skeletonList.Add(ConvertToTiki(pParentGlobalPosition.GetT()));
				//this->skeletonList.Add(ConvertToTiki(pGlobalPosition.GetT()));
				this->skeletonList.Add(pParentGlobalPosition.GetT());
				this->skeletonList.Add(pGlobalPosition.GetT());
			}
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

		void FbxLoader::ConvertToTiki(const FbxVector4& vector, const FbxVector4& normals, const FbxVector4& binormals, const FbxVector4& tangent, const FbxVector2& uv, DefaultVertex* output)
		{
			//vertices
			output->Position[0] = (float)vector[0];
			output->Position[1] = (float)vector[1];
			output->Position[2] = (float)-vector[2];
			
			//texture coordinate
			output->UV[0] = (float)uv[0];
			output->UV[1] = (float)(1-uv[1]);

			//normals
			output->Normal[0] = (float)normals[0];
			output->Normal[1] = (float)normals[1];
			output->Normal[2] = (float)-normals[2];

			//binormals
			output->Binormal[0] = (float)binormals[0];
			output->Binormal[1] = (float)binormals[1];
			output->Binormal[2] = (float)-binormals[2];

			//tangent
			output->Tangent[0] = (float)tangent[0];
			output->Tangent[1] = (float)tangent[1];
			output->Tangent[2] = (float)-tangent[2];

			//return Vector4((float)vector[0], (float)vector[1], (float)vector[2], (float)vector[3]);
		}

		Matrix FbxLoader::ConvertToTiki(FbxAMatrix &matrix)
		{
			Matrix m = Matrix();
			for(int i = 0; i < 4; i++)
			{
				FbxVector4 row = matrix.GetRow(i);
				for(int j = 0; j < 4; j++)
					m.n[i * 4 + j] = (float)row[j];
			}
			return m;
		}

		Vector4 FbxLoader::ConvertToTiki(FbxVector4 &vector)
		{
			Vector4 v = Vector4(
				(float)vector[0],
				(float)vector[1],
				(float)vector[2],
				(float)vector[3]
			);

			return v;
		}

		Matrix& FbxLoader::GetGlobalPosition(FbxNode* node)
		{
			return ConvertToTiki(GetGlobalPositionFbx(node));
		}

		FbxAMatrix& FbxLoader::GetGlobalPositionFbx(FbxNode* node, FbxTime pTime)
		{
			return node->EvaluateGlobalTransform(pTime);
		}

		FbxAMatrix FbxLoader::GetGeometryFbx(FbxNode* node)
		{
			const FbxVector4 lT = node->GetGeometricTranslation(FbxNode::eSourcePivot);
			const FbxVector4 lR = node->GetGeometricRotation(FbxNode::eSourcePivot);
			const FbxVector4 lS = node->GetGeometricScaling(FbxNode::eSourcePivot);

			return FbxAMatrix(lT, lR, lS);
		}

		Matrix& FbxLoader::GetGeometry(FbxNode* node)
		{
			return ConvertToTiki(GetGeometryFbx(node));
		}

		

	}
}
