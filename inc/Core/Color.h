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

	~Color()
	{
	}
};