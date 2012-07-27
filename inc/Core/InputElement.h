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

			InputElementFormat	ElementFormat;
			UInt32				ElementSize;

			InputElement(InputElementType semanticType, UInt32 semanticIndex, InputElementFormat elementFormat, UInt32 elementSize)
				: SemanticType(semanticType), SemanticIndex(semanticIndex), ElementFormat(elementFormat), ElementSize(elementSize)
			{
			}

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