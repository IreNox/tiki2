#pragma  once

#define FBXSDK_NEW_API
#include "fbxsdk.h"
#include <string.h>
#include "Core/Mesh.h"


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

		protected:
		};
	}
}
