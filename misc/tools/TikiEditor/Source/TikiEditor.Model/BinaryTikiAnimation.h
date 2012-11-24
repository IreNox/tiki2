#pragma once

#include "Core/TypeDef.h"

namespace TikiEditor
{
	struct BinaryTikiAnimation
	{
		UInt32 NameId;

		double StartTime;
		double EndTime;

		UInt32 TimeStampsArrayId;

		UInt32 BSV;
	};
}