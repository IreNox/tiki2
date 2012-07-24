#pragma once

#include "Core/ModuleType.h"

#include <string>
using std::string;

namespace TikiEngine
{
	namespace Modules
	{
		struct ModuleRequest 
		{
			ModuleType Type;
			string ModuleName;
		};
	}

}

