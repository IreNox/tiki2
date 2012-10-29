#pragma once

#include "Core/TypeInc.h"

namespace TikiEngine
{
	namespace Vertices
	{
		enum InputSemanticType
		{
			IST_Unknown,
			IST_Position,
			IST_Normal,
			IST_TexCoord,
			IST_Tangent,
			IST_Color,
			IST_Binormal,
			IST_SV_RenderTargetArrayIndex,
			IST_SkinningWeight,
			IST_SkinningIndices
		};

		enum InputElementFormat
		{
			IEF_Unknown,
			IEF_Float,
			IEF_UInt,
			IEF_Bool
		};

		struct InputElement
		{
			InputSemanticType	SemanticType;
			UInt32				SemanticIndex;

			InputElementFormat	ElementFormat;
			UInt32				ElementSize;

			InputElement()
				: SemanticType(IST_Unknown), SemanticIndex(0), ElementFormat(IEF_Unknown), ElementSize(0)
			{
			}

			InputElement(InputSemanticType semanticType, UInt32 semanticIndex, InputElementFormat elementFormat, UInt32 elementSize)
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