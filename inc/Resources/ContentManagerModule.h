#pragma once

#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Modules
	{
		class ContentManagerModule : public IContentManager
		{
		public:
			ContentManagerModule(Engine* engine);
			~ContentManagerModule(void);

			void* Load(string name);
		};
	}
}

