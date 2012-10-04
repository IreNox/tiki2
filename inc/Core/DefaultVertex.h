#pragma once

#include "Core/TypeInc.h"
#include "Core/InputElement.h"

namespace TikiEngine
{
	namespace Vertices
	{
		struct DefaultVertex
		{
			Single Position[3];
			Single UV[2];

			Single Normal[3];
			Single Binormal[3];
			Single Tangent[3];

			static UInt32 DeclarationCount;
			static InputElement Declaration[5];

			bool operator==(const DefaultVertex& rhs)
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

				return true;
			}

		};
	}
}