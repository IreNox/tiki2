
#include "Core/ColorVertex.h"
#include "Core/DefaultVertex.h"
#include "Core/PostProcessVertex.h"
#include "Core/SimpleVertex.h"
#include "Core/SkinningVertex.h"

namespace TikiEngine
{
	namespace Vertices
	{
		#pragma region ColorVertex
		bool ColorVertex::operator==(const ColorVertex& rhs)
		{
			return (this->Position[0] == rhs.Position[0]) &&
				(this->Position[1] == rhs.Position[1]) &&
				(this->Position[2] == rhs.Position[2]) &&
				(this->Color[0] == rhs.Color[0]) &&
				(this->Color[1] == rhs.Color[1]) &&
				(this->Color[2] == rhs.Color[2]) &&
				(this->Color[3] == rhs.Color[3]);
		}

		UInt32 ColorVertex::DeclarationCount = 2;

		InputElement ColorVertex::Declaration[2] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_Color,    0, IEF_Float, 4)
		};
		#pragma endregion

		#pragma region DefaultVertex
		UInt32 DefaultVertex::DeclarationCount = 3;

		InputElement DefaultVertex::Declaration[3] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 2),
			InputElement(IST_Normal,   0, IEF_Float, 3)
		};
		#pragma endregion

		#pragma region PostProcessVertex
		UInt32 PostProcessVertex::DeclarationCount = 2;

		InputElement PostProcessVertex::Declaration[2] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 2)
		};
		#pragma endregion

		#pragma region SimpleVertex
		InputElement SimpleVertex::Declaration[1] = {
			InputElement(IST_Position, 0, IEF_Float, 3)
		};
		#pragma endregion

		#pragma region SkinningVertex
		UInt32 SkinningVertex::DeclarationCount = 5;

		InputElement SkinningVertex::Declaration[5] = {
			InputElement(IST_Position, 0, IEF_Float, 3),
			InputElement(IST_TexCoord, 0, IEF_Float, 2),
			InputElement(IST_Normal,   0, IEF_Float, 3),
			InputElement(IST_BlendWeight,0,IEF_Float,4),
			InputElement(IST_BlendIndices,0,IEF_Float,4)
		};
		#pragma endregion
	}
}
