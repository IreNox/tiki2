#pragma once

#include "Enums.h"
#include "Core/TypeDef.h"

namespace TikiEditor
{
	struct MemoryPart
	{
		UInt32 Id;

		void* Pointer;
		PartType Type;
		PartType ArrayOf;
	};
}