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

		static RectangleF Create(const Vector2& pos, const Vector2& size)
		{
			RectangleF rect = { pos.X, pos.Y, size.X, size.Y };

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

		inline Vector3 TopLeft(float height = 0)
		{
			return Vector3(this->X, height, this->Y);
		}

		inline Vector3 TopRight(float height = 0)
		{
			return Vector3(this->X + this->Width, height, this->Y);
		}

		inline Vector3 BottomLeft(float height = 0)
		{
			return Vector3(this->X , height, this->Y + this->Height);
		}

		inline Vector3 BottomRight(float height = 0)
		{
			return Vector3(this->X + this->Width, height, this->Y + this->Height);
		}

		inline Vector2 Center()
		{
			return Vector2(this->X + this->Width * 0.5f, this->Y + this->Height * 0.5f);
		}

		inline Vector3 GetVertexP(const Vector3& normal, float height = 0)
		{						
			Vector3 p = TopLeft(height);

			if(normal.X >= 0) p.X = BottomRight(height).X;
			if(normal.Z >= 0) p.Z = BottomRight(height).Z;

			return p;
		}

		inline Vector3 GetVertexN(const Vector3& normal, float height = 0)
		{
			Vector3 p = BottomRight(height);

			if(normal.X >= 0) p.X = TopLeft(height).X;
			if(normal.Z >= 0) p.Z = TopLeft(height).Z;

			return p;
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
