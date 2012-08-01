#pragma  once

#include <string.h>
#include <stdlib.h>

#include "Core/Mesh.h"
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

		private:

			void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, wstring filename);
			void ConvertToTiki(const FbxVector4& vector, float* output);

			FbxManager* fbxManager;
			FbxScene* scene;
		};
	}
}
