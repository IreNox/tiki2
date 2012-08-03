#pragma once

#include "Core/Vector3.h"
#include "Core/Vector4.h"

struct Color
{
	union
	{
		struct  
		{
			float R;
			float G;
			float B;
			float A;
		};
		float arr[4];
	};

	Color()
		: R(0), G(0), B(0), A(0)
	{
	}

	Color(float r,float g, float b, float a)
		: R(r), G(g), B(b), A(a)
	{
	}

	~Color()
	{
	}

	Vector3 ToVector3()
	{
		return Vector3(R, G, B);
	}

	Vector4 ToVector4()
	{
		return Vector4(R, G, B, A);
	}

	static Color TransparentBlack;
	static Color White;
	static Color Back;
	static Color Red;
	static Color Green;
	static Color Blue;
	static Color TikiBlue;
};