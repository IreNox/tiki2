#pragma once

namespace TikiEngine
{
	struct ViewPort
	{
		int X;
		int Y;

		int Width;
		int Height;

		float MinDepth;
		float MaxDepth;

		ViewPort()
			: X(0), Y(0), Width(0), Height(0), MinDepth(0), MaxDepth(0)
		{
		}

		ViewPort(int x, int y, int width, int height, float minDepth, float maxDepth)
			: X(x), Y(y), Width(width), Height(height), MinDepth(minDepth), MaxDepth(maxDepth)
		{
		}
	};
}