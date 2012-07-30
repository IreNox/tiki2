
#include "Resources/ContentManagerModule.h"

namespace TikiEngine
{
	namespace Modules
	{
		ContentManagerModule::ContentManagerModule(Engine* engine)
			: IContentManager(engine)
		{
		}
		
		ContentManagerModule::~ContentManagerModule()
		{
		}

		void* ContentManagerModule::Load(string name)
		{
			return 0;
		}
	}
}