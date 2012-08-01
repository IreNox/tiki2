#pragma  once

#include <string.h>
#include <stdlib.h>

#include "Core/Mesh.h"

#define FBXSDK_NEW_API
#include "fbxsdk.h"

#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pSdkManager->GetIOSettings()))
#endif

using namespace TikiEngine::Resources;

namespace TikiEngine
{
	namespace Resources
	{

		class FbxLoader : public Object
		{
		public:
			FbxLoader();
			~FbxLoader();

			Mesh* LoadMesh(const wstring& name);

		private:

			void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
			bool LoadScene(FbxManager* pManager, FbxDocument* pScene, wstring filename);
			Vector4 ConvertToTiki(const FbxVector4& vector);

			FbxManager* fbxManager;
			FbxScene* scene;
		};
	}
}
