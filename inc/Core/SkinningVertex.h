#pragma once

#include "Core/TypeInc.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Vertices
	{
		//TODO better position -> Global Graphics Settings or something like that
		const int MAXBONESPERVERTEX = 4;

		struct SkinningVertex
		{
			SkinningVertex(){}
			SkinningVertex(float x, float y, float z, float u, float v,
				float nx, float ny, float nz)
			{
				Position[0] = x;
				Position[1] = y;
				Position[2] = z;

				UV[0] = u;
				UV[1] = v;

				Normal[0] = nx;
				Normal[1] = ny;
				Normal[2] = nz;

				for(int i = 0;  i < MAXBONESPERVERTEX; i++)
				{
					BlendWeights[i] = 0;
					BlendIndices[i] = 0;
				}
			}

			Single Position[3];
			Single UV[2];

			Single Normal[3];

			Single BlendWeights[MAXBONESPERVERTEX];
			Single BlendIndices[MAXBONESPERVERTEX];

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
					Normal[2] != rhs.Normal[2])
					return false;

				for(int i = 0; i < MAXBONESPERVERTEX; i++)
				{
					if(BlendWeights[i] != rhs.BlendWeights[i] ||
						BlendIndices[i] != rhs.BlendIndices[i])
						return false;
				}

				return true;
			}

		};
	}
}