#pragma once

#include "Enums.h"
#include "Core/TypeDef.h"

namespace TikiEditor
{
	struct BinaryPart
	{
		UInt32 Id;

		PartType Type;
		PartType ArrayOf;
		UInt32 ArrayCount;

		UInt32 Start;
		UInt32 Length;
	};
}