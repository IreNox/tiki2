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

			bool operator==(const SkinningVertex& rhs)
			{
				if(Position[0] != rhs.Position[0])
					return false;
				if(Position[1] != rhs.Position[1])
					return false;
				if(Position[2] != rhs.Position[2])
					return false;

				if(UV[0] != rhs.UV[0])
					return false;
				if(UV[1] != rhs.UV[1])
					return false;

				if(Normal[0] != rhs.Normal[0])
					return false;
				if(Normal[1] != rhs.Normal[1])
					return false;
				if(Normal[2] != rhs.Normal[2])
					return false;

				if(BlendWeights[0] != rhs.BlendWeights[0])
					return false;
				if(BlendWeights[1] != rhs.BlendWeights[1])
					return false;
				if(BlendWeights[2] != rhs.BlendWeights[2])
					return false;
				if(BlendWeights[3] != rhs.BlendWeights[3])
					return false;

				if(BlendIndices[0] != rhs.BlendIndices[0])
					return false;
				if(BlendIndices[1] != rhs.BlendIndices[1])
					return false;
				if(BlendIndices[2] != rhs.BlendIndices[2])
					return false;
				if(BlendIndices[3] != rhs.BlendIndices[3])
					return false;

				return true;
			}

		};
	}
}