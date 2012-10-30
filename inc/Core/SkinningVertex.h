#pragma once

#include "Core/TypeInc.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Vertices
	{
		struct SkinningVertex
		{
			Single Position[3];
			Single UV[2];

			Single Normal[3];

			Single BlendWeights[4];
			Single BlendIndices[4];

			static UInt32 DeclarationCount;
			static InputElement Declaration[5];

			inline bool operator==(const SkinningVertex& rhs)
			{
				if(Position[0] != rhs.Position[0] ||
					Position[1] != rhs.Position[1] ||
					Position[2] != rhs.Position[2] ||
					UV[0] != rhs.UV[0] ||
					UV[1] != rhs.UV[1] ||
					Normal[0] != rhs.Normal[0] ||
					Normal[1] != rhs.Normal[1] ||
					Normal[2] != rhs.Normal[2] ||
					BlendWeights[0] != rhs.BlendWeights[0] ||
					BlendWeights[1] != rhs.BlendWeights[1] ||
					BlendWeights[2] != rhs.BlendWeights[2] ||
					BlendWeights[3] != rhs.BlendWeights[3] ||
					BlendIndices[0] != rhs.BlendIndices[0] ||
					BlendIndices[1] != rhs.BlendIndices[1] ||
					BlendIndices[2] != rhs.BlendIndices[2] ||
					BlendIndices[3] != rhs.BlendIndices[3])
					return false;

				return true;
			}

		};
	}
}