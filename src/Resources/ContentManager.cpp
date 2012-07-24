
#include "Resources/ContentManager.h"

namespace TikiEngine
{
	namespace Modules
	{
		ContentManager::ContentManager(Engine* engine)
			: IContentManager(engine)
		{
		}
		
		ContentManager::~ContentManager()
		{
		}

		void* ContentManager::Load(string name)
		{
			return 0;
		}
	}
}

