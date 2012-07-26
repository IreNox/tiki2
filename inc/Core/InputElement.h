#pragma once

#include "Core/TypeInc.h"

namespace TikiEngine
{
	namespace Vertices
	{
		enum InputElementType
		{
			Position,
			Normal,
			TexCoord,
			Tangent,
			Color,
			Binormal
		};

		enum InputElementFormat
		{
			Float,
			UInt,
			Bool
		};

		struct InputElement
		{
			InputElementType	SemanticType;
			UInt32				SemanticIndex;

			UInt32				ElementSize;
			InputElementFormat	ElementFormat;
		};
	}
}