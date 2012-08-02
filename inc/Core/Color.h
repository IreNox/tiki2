#pragma once

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

	static Color TransparentBlack;
	static Color White;
	static Color Back;
	static Color Red;
	static Color Green;
	static Color Blue;
	static Color TikiBlue;
};