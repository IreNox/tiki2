#pragma once

#include "Core/Object.h"
#include "Core/ModuleType.h"

namespace TikiEngine
{
	namespace Modules
	{
		struct ModuleResponse
		{
			ModuleType Type;
			Object* Pointer;
		};
	}
}