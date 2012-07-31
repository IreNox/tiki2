#pragma  once

#define FBXSDK_NEW_API
#include "fbxsdk.h"
#include <string.h>
#include "Core/Mesh.h"

#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pManager->GetIOSettings()))
#endif


using namespace TikiEngine::Graphics;

namespace TikiEngine
{
	namespace Resources
	{
		class FbxLoader
		{
		public:
			FbxLoader();
			~FbxLoader();

			static Mesh* LoadMesh(const wstring& name);

		private:

			static void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
			static bool LoadScene(FbxManager* pManager, FbxDocument* pScene, const char* pFilename);


		protected:
		};
	}
}
