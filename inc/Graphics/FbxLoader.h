#pragma  once

#include <string.h>
#include <stdlib.h>

#include "Core/MeshIndexed.h"
#include "Core/Matrix.h"
#include "Core/DefaultVertex.h"

#define FBXSDK_NEW_API
#include "fbxsdk.h"

#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pSdkManager->GetIOSettings()))
#endif

using namespace TikiEngine::Vertices;
using namespace TikiEngine::Resources;

namespace TikiEngine
{
	namespace Resources
	{
		class FbxLoader : public EngineObject
		{
		public:
			FbxLoader(Engine* engine);
			~FbxLoader();

			Mesh* LoadMesh(const wstring& name);
			Mesh* LoadSkeleton(const wstring& name);

		private:

			void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
			void InitializeAnimationStack();
			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, wstring filename);
			
			int CountNodes(FbxNode* node, FbxNodeAttribute::EType type);

			void HandleNodeRecursive(FbxNode* node, FbxTime& pTime, FbxAMatrix& pParentGlobalPosition);
			void HandleNode(FbxNode* pNode, FbxTime& pTime, FbxAMatrix& pParentGlobalPosition, FbxAMatrix& pGlobalPosition);
			void HandleSkeleton(FbxNode* pNode, FbxAMatrix& pParentGlobalPosition, FbxAMatrix& pGlobalPosition);

			bool SetCurrentAnimStack(int pIndex);

			Matrix ConvertToTiki(FbxAMatrix &matrix);
			Vector4 ConvertToTiki(FbxVector4 &vector);
			void ConvertToTiki(const FbxVector4& vector, const FbxVector4& normals, const FbxVector4& binormals, const FbxVector4& tangent, const FbxVector2& uv, DefaultVertex* output);

			Matrix& GetGlobalPosition(FbxNode* node);
			Matrix& GetGeometry(FbxNode* node);

			FbxAMatrix GetGeometryFbx(FbxNode* node);
			FbxAMatrix& GetGlobalPositionFbx(FbxNode* node, FbxTime pTime=FBXSDK_TIME_INFINITE);

			List<FbxVector4> skeletonList;

			FbxArray<FbxString*> mAnimStackNameArray;
			FbxAnimLayer* mCurrentAnimLayer;

			FbxManager* fbxManager;
			FbxScene* scene;
		};
	}
}
