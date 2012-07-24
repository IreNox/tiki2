#pragma once

#include "Core/TypeDef.h"

struct Quaternion
{
	union
	{
		struct
		{
			Single X;
			Single Y;
			Single Z;
			Single W;
		};
		Single arr[4];
	};

	Quaternion();
	~Quaternion();

};