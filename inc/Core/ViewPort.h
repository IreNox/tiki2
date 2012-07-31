#pragma once

namespace TikiEngine
{
	struct ViewPort
	{
		int X;
		int Y;

		int Width;
		int Height;

		ViewPort()
			: X(0), Y(0), Width(0), Height(0)
		{
		}

		ViewPort(int x, int y, int width, int height)
			: X(x), Y(y), Width(width), Height(height)
		{
		}
	};
}