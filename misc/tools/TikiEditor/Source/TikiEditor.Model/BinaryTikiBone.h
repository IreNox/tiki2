#pragma once

#include "Core/TypeInc.h"

namespace TikiEditor
{
	struct BinaryTikiBone
	{
		UInt32 NameId;

		UInt32 ParentId;
		UInt32 ChildsArrayId;
		UInt32 LayerArrayId;
		
		Matrix Init;

		UInt32 ConstanBufferIndex;
	};
}