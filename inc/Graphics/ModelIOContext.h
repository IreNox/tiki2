#pragma once

#include "Graphics/ModelBinaryData.h"

#include "Core/TypeDef.h"
#include "Core/TypeGlobals.h"
#include "Core/Stream.h"

#include "Core/TikiIOContext.h"

namespace TikiEngine
{
	namespace Resources
	{
		using namespace TikiEngine::IO;

		typedef TikiBinaryPart<PartType> BinaryPart;
		typedef TikiIOContext<BinaryFileHeader, PartType, PT_NoArray> ModelIOContext;
	}
}