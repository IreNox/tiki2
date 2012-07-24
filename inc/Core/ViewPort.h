#pragma once

namespace TikiEngine
{
	struct ViewPort
	{
		int Top;
		int Left;

		int Width;
		int Height;

		ViewPort()
			: Top(0), Left(0), Width(0), Height(0)
		{
		}

		ViewPort(int top, int left, int width, int height)
			: Top(top), Left(left), Width(width), Height(height)
		{
		}
	};
}