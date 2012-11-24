#pragma once

#include "Core/TypeDef.h"

namespace TikiEditor
{
	struct BinaryFileHeader
	{
		char TIKI[4];

		UInt32 FileLength;
		UInt32 PartCount;

		UInt32 RootBoneId;

		UInt32 MeshArrayId;
		UInt32 AnimationArrayId;
	};
}