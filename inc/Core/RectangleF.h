#pragma once

#include "Core/Vector2.h"

namespace TikiEngine
{
	struct RectangleF
	{
	public:

		union
		{
			struct
			{
				float X;
				float Y;
				float Width;
				float Height;
			};
			float arr[4];
		};

		static RectangleF Create(float x, float y, float width, float height)		
		{
			RectangleF rect = { x, y, width, height };

			return rect;
		}

		//RectangleF()
		//	: X(0), Y(0)
		//{
		//}

		//RectangleF(float x, float y, float width, float height)
		//	: X(x), Y(y), Width(width), Height(height)
		//{
		//}

		//~RectangleF() {}

		inline bool operator==(const RectangleF& rhs)
		{
			return (this->X == rhs.X && this->Y == rhs.Y && this->Width == rhs.Width && this->Height == rhs.Height);
		}

		inline float Right() const
		{
			return this->X + this->Width;
		}

		inline float Bottom() const
		{
			return this->Y + this->Height;
		}

		inline bool Contains(const Vector2& point)
		{
			return (this->X < point.X && this->Right() > point.X) &&
				   (this->Y < point.Y && this->Bottom() > point.Y);
		}

	};
}
