#pragma once

#include "Core/Vector2.h"
#include "Core/Vector3.h"

namespace TikiEngine
{
	enum CollisionType
	{
		Disjunct,
		Contain,
		Intersect
	};

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
		inline bool operator!=(const RectangleF& rhs)
		{
			return this->X != rhs.X || this->Y != rhs.Y || this->Width != rhs.Width && this->Height != rhs.Height;
		}

		inline bool operator==(const RectangleF& rhs)
		{
			return (this->X == rhs.X && this->Y == rhs.Y && this->Width == rhs.Width && this->Height == rhs.Height);
		}

		inline Vector3 TopLeft()
		{
			return Vector3(this->X, 0, this->Y);
		}

		inline Vector3 TopRight()
		{
			return Vector3(this->X + this->Width, 0, this->Y);
		}

		inline Vector3 BottomLeft()
		{
			return Vector3(this->X , 0, this->Y + this->Height);
		}

		inline Vector3 BottomRight()
		{
			return Vector3(this->X + this->Width, 0, this->Y + this->Height);
		}

		inline float Left() const
		{
			return this->X;
		}

		inline float Right() const
		{
			return this->X + this->Width;
		}

		inline float Top() const
		{
			return this->Y;
		}

		inline float Bottom() const
		{
			return this->Y + this->Height;
		}

		inline Vector2 Position()
		{
			return Vector2(X, Y);
		}	
			
		inline Vector2 Size()
		{
			return Vector2(Width, Height);
		}

		inline bool Contains(const Vector2& point)
		{
			return (this->X < point.X && this->Right() > point.X) &&
				   (this->Y < point.Y && this->Bottom() > point.Y);
		}

		inline CollisionType Collide(const RectangleF& rect)
		{
			if (this->Right() < rect.Left() || this->Left() > rect.Right()
				|| this->Bottom() < rect.Top() || this->Top() > rect.Bottom())
			{
				return Disjunct;
			}
			else if (this->Left() <= rect.Left() && this->Right() >= rect.Right()
				&& this->Top() <= rect.Top() && this->Bottom() >= rect.Bottom())
			{
				return Contain;
			}
			else
			{
				return Intersect;
			}
		}
	};
}
