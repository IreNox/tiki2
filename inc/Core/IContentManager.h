#pragma once

#include "Core/IModule.h"

namespace TikiEngine
{
	class IContentManager : public IModule
	{
	public:

		IContentManager(Engine* engine)
			: IModule(engine)
		{
		}
		virtual ~IContentManager() {}

		virtual void* Load(string name) = 0;

		// coming soon
		//virtual IMesh* LoadMesh(string name) = 0;
		//virtual ITexture* LoadTexture(string name) = 0;
		//virtual IMaterial* LoadMaterial(string name) = 0;

	};
}

