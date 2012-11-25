#pragma  once

#include <string.h>
#include <stdlib.h>

#include "Core/Matrix.h"
#include "Core/DefaultVertex.h"

#include "FbxHelper.h"

#define FBXSDK_NEW_API
#include "fbxsdk.h"

#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pSdkManager->GetIOSettings()))
#endif

using namespace TikiEngine::Vertices;

namespace TikiEngine
{
	namespace Resources
	{
		class FbxLoader
		{
		public:
			FbxLoader();
			~FbxLoader();

			FbxManager& Manager();

			bool GetScene(wstring filename, FbxHelper* helper);
			bool GetScene(wstring filename, FbxScene** scene);
		private:

			void CreateNewScene(FbxScene** scene);

			void InitializeSdkObjects(FbxManager*& pManager);

			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, wstring filename);

			FbxManager* fbxManager;

		};
	}
}
