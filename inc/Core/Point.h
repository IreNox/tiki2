#pragma once

#include "Core/Vector2.h"

namespace TikiEngine
{
	struct Point 
	{
	public:

		union
		{
			struct
			{
				int X;
				int Y;
			};
			int arr[2];
		};

		Point()
			: X(0), Y(0)
		{
		}

		Point(int all)
			: X(all), Y(all)
		{
		}

		Point(int x, int y)
			: X(x), Y(y)
		{
		}

		~Point() {}

		Vector2 ToVector2()
		{
			return Vector2(X, Y);
		}

	};
}
