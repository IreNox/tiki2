#pragma once

#include "Core/IContentManager.h"

namespace TikiEngine
{
	struct InitializationArgs
	{
		IContentManager* Content;

		InitializationArgs(IContentManager* content)
			: Content(content)
		{
		}
		
		~InitializationArgs()
		{
		}
	};
}

