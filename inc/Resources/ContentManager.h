#pragma once

#include "Core/IContentManager.h"

namespace TikiEngine
{
	namespace Modules
	{
		class ContentManager : public IContentManager
		{
		public:
			ContentManager(Engine* engine);
			~ContentManager(void);

			void* Load(string name);
		};
	}
}

