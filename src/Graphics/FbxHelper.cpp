#include "Graphics/FbxHelper.h"
#include "Core/DefaultVertex.h"
#include "Core/SkinningVertex.h"

namespace TikiEngine
{
	namespace Resources
	{
		FbxHelper::FbxHelper()
			: scene(0), rootBone(0), animation(0)
		{

		}
		FbxHelper::~FbxHelper()
		{

		}

		FbxScene* FbxHelper::GetScene()
		{
			return this->scene;
		}

		void FbxHelper::SetScene(FbxScene* scene)
		{
			this->scene = scene;
			Initialize();
		}

		TikiBone* FbxHelper::GetRootBone()
		{
			return this->rootBone;
		}

		TikiAnimation* FbxHelper::GetAnimation()
		{
			return this->animation;
		}

		List<TikiBone*>& FbxHelper::GetConstantBufferIndices()
		{
			return this->constantBufferIndices;
		}
		List<TikiMesh*>& FbxHelper::GetMeshes()
		{
			return this->meshes;
		}

		void FbxHelper::Initialize()
		{
			FbxNode* root = this->scene->GetRootNode();
			RecursiveBone(root);
			BuildBoneHierachy(root);

			//int tmp = rootBone->Count();

			FlagBones();
			CleanBones();

			InitializeAnimation();

			for(int i = 0; i < fbxNodes.Count(); i++)
				InitializeAnimationLayer(fbxNodes[i]);

			//FindMeshes();
		}

		void FbxHelper::FindMeshes()
		{
			int meshCount = scene->GetSrcObjectCount<FbxMesh>();
			for(int i = 0; i < meshCount; i++)
				InitializeMesh(scene->GetSrcObject<FbxMesh>(i));
		}

		void FbxHelper::FlagBones()
		{
			if(rootBone == 0)
				return;

			int meshCount = scene->GetSrcObjectCount<FbxMesh>();
			for(int meshIndex = 0; meshIndex < meshCount; meshIndex++)
			{
				FbxMesh* mesh = scene->GetSrcObject<FbxMesh>(meshIndex);
				
				int skinCount =  mesh->GetDeformerCount(FbxDeformer::eSkin);
				for(int skinIndex = 0; skinIndex < skinCount; skinIndex++)
				{
					FbxSkin* skin = (FbxSkin*) mesh->GetDeformer(skinIndex, FbxDeformer::eSkin);

					int clustCount = skin->GetClusterCount();
					for(int clustIndex = 0; clustIndex < clustCount; clustIndex++)
					{
						FbxCluster* cluster = skin->GetCluster(clustIndex);
						if(!cluster->GetLink())
							continue;
						TikiBone* bone = rootBone->GetBoneByName(cluster->GetLink()->GetName());
						if(bone == 0)
							_CrtDbgBreak();
						bone->SetConstantBufferIndex(1);
					}
				}
			}
		}

		void FbxHelper::CleanBones()
		{
			if(rootBone == 0)
				return;

			rootBone->Clean();
			rootBone->CreateMapping(constantBufferIndices);
		}

		void FbxHelper::RecursiveBone(FbxNode* node)
		{
			fbxNodes.Add(node);
			for(int i = 0; i < node->GetChildCount(); i++)
				RecursiveBone(node->GetChild(i));
		}

		void FbxHelper::BuildBoneHierachy(FbxNode* node, TikiBone* parent)
		{
			TikiBone* bone = new TikiBone();
			bone->SetName(node->GetName());
			bone->SetBoneInitTransform(GlobalTransform(node));
			//bone->SetFbxNode(node); //TODO kicken

			this->tikiBones.Add(bone);

			if(parent == 0)
				rootBone = bone;
			else
			{
				parent->AddChild(bone);
				bone->SetParent(parent);
			}
			for(int i = 0; i < node->GetChildCount(); i++)
			{
				this->BuildBoneHierachy(node->GetChild(i), bone);
			}
		}

		void FbxHelper::InitializeMesh(FbxMesh* mesh)
		{
			TikiMesh* tiki = new TikiMesh();
			tiki->SetName(mesh->GetName());

			int vertexCount = mesh->GetControlPointsCount();

			List<Vector3> vertexList;
			GetGlobalVertices(vertexList, mesh);
			List<VertexBufferInput> vertexBufferInput;
			List<SkinningInput> skinningInput;
			List<UInt32> indices;

			int skinCount = mesh->GetDeformerCount(FbxDeformer::eSkin);
			tiki->SetDeformation(skinCount > 0);

			int maxBonesPerVertex = MaxBonesPerVertex(mesh);
#if _DEBUG
			if(tiki->UseDeformation() && maxBonesPerVertex > 4)
				_CrtDbgBreak();
#endif
			UInt32 counter = 0;
			Int32 polygonCount = mesh->GetPolygonCount();
			for(Int32 i = 0; i < polygonCount; i++)
			{
				Int32 verticesInPolygon = mesh->GetPolygonSize(i);
				if(verticesInPolygon != 3 && verticesInPolygon != 4)
					_CrtDbgBreak();

				UInt32 indicesArray[4];

				for(Int32 k = 0; k < verticesInPolygon; k++)
				{
					int index = mesh->GetPolygonVertex(i,k);

					Vector3 position = vertexList[index];

					Vector2 uv = Vector2(0,0);
					int uvIndex = -1;

					if(mesh->GetElementUVCount() != 0)
					{
						uvIndex = mesh->GetElementUV(0)->GetIndexArray().GetAt(counter);
						uv = FBXConverter::Convert(mesh->GetElementUV(0)->GetDirectArray().GetAt(uvIndex));
					}

					Vector3 normals = FBXConverter::ConvertDrop(mesh->GetElementNormal(0)->GetDirectArray().GetAt(counter));

					VertexBufferInput vbi( position, uv, normals);

					
					indicesArray[k] = vertexBufferInput.IndexOf(vbi);
					if(indicesArray[k] == -1)
					{
						indicesArray[k] = vertexBufferInput.Count();
						vertexBufferInput.Add(vbi);
						skinningInput.Add(SkinningInput());
					}
					counter++;
				}

				indices.Add(indicesArray[0]);
				indices.Add(indicesArray[1]);
				indices.Add(indicesArray[2]);

				if(verticesInPolygon == 4)
				{
					indices.Add(indicesArray[0]);
					indices.Add(indicesArray[2]);
					indices.Add(indicesArray[3]);
				}
			}

			for(int skinIndex = 0; skinIndex < skinCount; skinIndex++)
			{
				FbxSkin* skin = (FbxSkin*) mesh->GetDeformer(skinIndex, FbxDeformer::eSkin);

				int clustCount = skin->GetClusterCount();
				for(int clustIndex = 0; clustIndex < clustCount; clustIndex++)
				{
					FbxCluster* cluster = skin->GetCluster(clustIndex);
					if(!cluster->GetLink())
						continue;

					int vertexCount = cluster->GetControlPointIndicesCount();
					for(int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
					{
		/*				if(vertexIndex == 1270)
							_CrtDbgBreak();*/
						int index = cluster->GetControlPointIndices()[vertexIndex];

						if (index >= mesh->GetControlPointsCount())
							continue;

						Vector3 position = vertexList[index];

						int updatestructureCount = vertexBufferInput.Count();
						for(int i = 0; i < updatestructureCount; i++)
						{
							if(vertexBufferInput[i].Position == position)
							{
								SkinningInput s = skinningInput[i];
								int vsIndex = 0;
								while(s.Weights[vsIndex] != -1)
								{
									if(vsIndex > 4)
										_CrtDbgBreak();
									vsIndex++;
								}

								if(vsIndex == 5)
									_CrtDbgBreak();

								s.Indices[vsIndex] = (float)clustIndex;
								s.Weights[vsIndex] = (float)cluster->GetControlPointWeights()[vertexIndex];
								skinningInput.Set(i,s);
							}
						}
					}
				}
			}

			int vertexBufferCount = vertexBufferInput.Count();
			for(int index = 0; index < vertexBufferCount; index++)
			{
				for(int i = 0; i < 4; i++)
				{
					if(skinningInput[index].Weights[i] == -1)
						skinningInput[index].Weights[i] = 0;
				}
			}

			List<SkinningVertex> skinning;
			List<DefaultVertex> default;

			for(int i = 0; i < vertexBufferCount; i++)
			{
				VertexBufferInput vbi = vertexBufferInput[i];
				SkinningInput skin = skinningInput[i];

				SkinningVertex s(vbi.Position.arr[0], vbi.Position.arr[1], vbi.Position.arr[2],
					vbi.UV.arr[0], vbi.UV.arr[1], 
					vbi.Normal.arr[0], vbi.Normal.arr[1], vbi.Normal.arr[2]);

				for(int k = 0; k < MAXBONESPERVERTEX; k++)
				{
					s.BlendIndices[k] = skin.Indices[k];
					s.BlendWeights[k] = skin.Weights[k];
				}
				skinning.Add(s);

				DefaultVertex d = {vbi.Position.arr[0], vbi.Position.arr[1], vbi.Position.arr[2],
					vbi.UV.arr[0], vbi.UV.arr[1], 
					vbi.Normal.arr[0], vbi.Normal.arr[1], vbi.Normal.arr[2]};
				default.Add(d);
			}
			tiki->SetIndices(indices);
			tiki->SetDefaultVertexData(default);
			tiki->SetSkinningVertexData(skinning);

			meshes.Add(tiki);
		}

		void FbxHelper::GetGlobalVertices(List<Vector3>& list, FbxMesh* mesh)
		{
			int vertexCount = mesh->GetControlPointsCount();

			FbxVector4* vertexArray = new FbxVector4[vertexCount];
			memcpy(vertexArray, mesh->GetControlPoints(), vertexCount * sizeof(FbxVector4));

			for(int i = 0; i < vertexCount; i++)
			{
				vertexArray[i] = (static_cast<FbxMatrix>(mesh->GetNode()->EvaluateGlobalTransform(FBXSDK_TIME_INFINITE)).
					MultNormalize(vertexArray[i]));
				list.Add(FBXConverter::ConvertDrop(vertexArray[i]));
			}

			delete[]vertexArray;
			vertexArray = 0;
		}

		void FbxHelper::InitializeAnimation()
		{
			this->animation = new TikiAnimation();

			FbxAnimStack* stack = scene->GetSrcObject<FbxAnimStack>(0);
			animation->SetName(stack->GetName());

			for(int layerIndex = 0; layerIndex < stack->GetSrcObjectCount(); layerIndex++)
			{
				FbxAnimLayer* layer = stack->GetSrcObject<FbxAnimLayer>(layerIndex);
				for(int i = 0; i < fbxNodes.Count(); i++)
				{
					FbxAnimCurve* curve = fbxNodes[i]->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
					FillTimeStamp(curve);
					curve = fbxNodes[i]->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
					FillTimeStamp(curve);
					curve = fbxNodes[i]->LclTranslation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
					FillTimeStamp(curve);

					curve = fbxNodes[i]->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_X);
					FillTimeStamp(curve);
					curve = fbxNodes[i]->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Y);
					FillTimeStamp(curve);
					curve = fbxNodes[i]->LclRotation.GetCurve(layer, FBXSDK_CURVENODE_COMPONENT_Z);
					FillTimeStamp(curve);
				}
			}

			int bsv = 1;
			while(bsv*2 < animation->GetTimeStamps().Count())
				bsv *= 2;
			animation->SetBSV(bsv);
		}

		void FbxHelper::FillTimeStamp(FbxAnimCurve* curve)
		{
			if(curve == 0)
				return;

			for(int i = 0; i < curve->KeyGetCount(); i++)
			{
				animation->AddTimeStampKey(curve->KeyGetTime(i).GetSecondDouble());
			}
		}

		void FbxHelper::InitializeAnimationLayer(FbxNode* node)
		{
			TikiBone* bone = 0;
			for(int i = 0; i < tikiBones.Count(); i++)
			{
				if(node->GetName() == tikiBones[i]->GetName())
				{
					bone = tikiBones[i];
					break;
				}
			}
			if(bone == 0)
				return;

			AnimationLayer layer;

			if(animation->GetTimeStamps().Count() == 0) // defaultValues
			{
				FbxAMatrix transform = node->EvaluateLocalTransform();

				layer.GetTranslation().Add(FBXConverter::ConvertDrop(transform.GetT()));
				layer.GetQuaternion().Add(FBXConverter::Convert(transform.GetQ()));
			}
			else
			{
				for(int i = 0; i < animation->GetTimeStamps().Count(); i++)
				{
					FbxTime time;
					time.SetSecondDouble(animation->GetTimeStamps()[i]);
					FbxAMatrix transform = node->EvaluateLocalTransform(time);

					layer.GetTranslation().Add(FBXConverter::ConvertDrop(transform.GetT()));
					layer.GetQuaternion().Add(FBXConverter::Convert(transform.GetQ()));
				}
			}

			bone->AddAnimation(this->animation, layer);
		}

		void FbxHelper::MergeAnimation(TikiAnimation* animation, TikiBone* destination, TikiBone* source)
		{
			TikiBone* bone = source->GetBoneByName(destination->GetName());
			if(bone == 0)
				_CrtDbgBreak();

			destination->AddAnimation(animation, bone->GetAnimationLayer(animation));

			for(int i = 0; i < destination->GetChilds()->Count(); i++)
				MergeAnimation(animation, destination->GetChilds()->Get(i), source);
		}


#pragma region NodeHelper
		Matrix FbxHelper::LocalTransform(FbxNode* node, FbxTime& time )
		{
			return FBXConverter::ConvertTranspose(node->EvaluateLocalTransform(time));
		}

		Matrix FbxHelper::GlobalTransform(FbxNode* node, FbxTime& time )
		{
			return FBXConverter::ConvertTranspose(node->EvaluateGlobalTransform(time));
		}
		int FbxHelper::MaxBonesPerVertex(FbxMesh* mesh)
		{
			bool hasSkin = mesh->GetDeformerCount(FbxDeformer::eSkin) > 0;

			if(!hasSkin)
				return -1;

			int* testData = new int[mesh->GetControlPointsCount()];
			for(int i = 0; i < mesh->GetControlPointsCount(); i++)
				testData[i] = 0;

			int skinCount =  mesh->GetDeformerCount(FbxDeformer::eSkin);
			for(int skinIndex = 0; skinIndex < skinCount; skinIndex++)
			{
				FbxSkin *  skinDeformer = (FbxSkin*) mesh->GetDeformer(skinIndex, FbxDeformer::eSkin);

				int clusterCount = skinDeformer->GetClusterCount();
				for(int clusterIndex = 0; clusterIndex < clusterCount; clusterIndex++)
				{
					FbxCluster* cluster = skinDeformer->GetCluster(clusterIndex);
					if (!cluster->GetLink())
						continue;
					int vertexCount = cluster->GetControlPointIndicesCount();
					for(int vertexIndex = 0; vertexIndex < vertexCount; vertexIndex++)
					{
						int index = cluster->GetControlPointIndices()[vertexIndex];

						if (index >= mesh->GetControlPointsCount())
							continue;

						testData[index]++;
					}

				}
			}

			int max = 0;
			for(int i = 0; i < mesh->GetControlPointsCount(); i++)
			{
				if(testData[i] > max)
					max = testData[i];

			}

			delete[] testData;
			return max;
		}
#pragma endregion

	}
}