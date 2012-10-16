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

			bool GetScene(wstring filename, FbxScene** scene);
		private:

			void CreateNewScene(FbxScene** scene);

			void InitializeSdkObjects(FbxManager*& pManager);

			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, wstring filename);

			FbxManager* fbxManager;

		};
	}
}
