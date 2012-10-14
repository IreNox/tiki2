#pragma once

#include "Core/RectangleF.h"

namespace TikiEngine
{
	struct Rectangle
	{
	public:

		union
		{
			struct
			{
				int X;
				int Y;
				int Width;
				int Height;
			};
			int arr[4];
		};

		Rectangle()
			: X(0), Y(0)
		{
		}

		Rectangle(int x, int y, int width, int height)
			: X(x), Y(y), Width(width), Height(height)
		{
		}

		~Rectangle() {}

		bool operator==(const Rectangle& rhs)
		{
			return (this->X == rhs.X) && (this->Y == rhs.Y) && (this->Width == rhs.Width) && (this->Height == rhs.Height);
		}

		operator RectangleF()
		{
			return RectangleF(
				(float)X,
				(float)Y,
				(float)Width,
				(float)Height
			);
		}

	};
}
