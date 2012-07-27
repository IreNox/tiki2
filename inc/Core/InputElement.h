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

			bool operator==(const InputElement& rhs)
			{
				return (this->SemanticType == rhs.SemanticType) && (this->SemanticIndex == rhs.SemanticIndex) &&
					   (this->ElementFormat == rhs.ElementFormat) && (this->ElementSize == rhs.ElementSize);
			}

			bool operator!=(const InputElement& rhs)
			{
				return !(*this == rhs);
			}
		};
	}
}