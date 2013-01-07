#pragma once

#include "Core/TypeInc.h"
#include "Core/TikiIOContext.h"

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine::IO;

		enum ResPartType
		{
			PT_String,
			PT_Array,
			PT_NoArray,
			PT_Byte,
			PT_Widechar,
			PT_UInt
		};

		struct ResBinaryFileHeader
		{
			char TIKI[4];

			UInt32 FileLength;
			UInt32 PartCount;

			UInt32 FileCount;
			UInt32 FilelistId;
			UInt32 DatalistId;
		};

		typedef TikiBinaryPart<ResPartType> ResBinaryPart;
		typedef TikiIOContext<ResBinaryFileHeader, ResPartType, PT_NoArray> ResIOContext;
	}
}