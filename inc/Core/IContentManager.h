#pragma once

#include "Core/IModule.h"

#include "Core/Mesh.h"
#include "Core/ITexture.h"
#include "Core/Material.h"
#include "Core/IPhysicsMaterial.h"

namespace TikiEngine
{
	namespace Modules
	{
		using namespace TikiEngine::Resources;

		class IContentManager : public IModule
		{
		public:

			IContentManager(Engine* engine)
				: IModule(engine)
			{
			}
			virtual ~IContentManager() {}

			virtual IResource* Load(IntPtr hash, wstring name) = 0;

			virtual Mesh* LoadMesh(const wstring& name) = 0;
			virtual Mesh* LoadFbxMesh(const wstring& name) = 0;
			virtual ITexture* LoadTexture(const wstring& name) = 0;
			virtual Material* LoadMaterial(const wstring& name) = 0;
			virtual IPhysicsMaterial* LoadPhysicsMaterial(const wstring& name) = 0;

			virtual wstring GetWorkingPath() = 0;
			virtual wstring GetRealFilePath(wstring fileName) = 0;
		};
	}
}