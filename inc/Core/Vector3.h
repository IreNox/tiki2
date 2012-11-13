#pragma once

#include "Core/Matrix.h"
#include "Core/Vector2.h"

#include <Math.h>

class Vector3
{
public:
	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
		};
		float arr[3];
	};

	Vector3(void);
	Vector3(float all);
	Vector3(float* arr);
	Vector3(Vector2 v, float z);
	Vector3(float x, float y, float z);

	~Vector3(void);

	float Length() const;
	float LengthSquared() const;

	void Negate();
	static Vector3 Negate(const Vector3& vector);

	void Normalize();
	static Vector3 Normalize(const Vector3& vector);

	// Projects a 3D vector from object space into screen space. 
	static Vector3 Project(const Vector3& vec, float x, float y, float width, float height, 
						   float minZ, float maxZ, const Matrix& worldViewProjection);

	// Projects a 3D vector from screen space into object space. 
	static Vector3 Unproject(const Vector3& vector, float x, float y, float width, float height, 
							 float minZ, float maxZ, const Matrix& worldViewProjection);

	//  Performs a coordinate transformation using the given transform matrix
	static Vector3 TransformCoordinate(const Vector3& coord, const Matrix& transform); // rework maybe? // is this ok?

	static float Dot(const Vector3& vector1, const Vector3& vector2);
	static Vector3 Cross(const Vector3& vector1, const Vector3& vector2);
	static float Angle(const Vector3& vector1, const Vector3& vector2);
	static float Distance(const Vector3& vector1, const Vector3& vector2);
	static float DistanceSquared(const Vector3& vector1, const Vector3& vector2);
	static Vector3 Reflect(const Vector3& vector, const Vector3& normal);
	static Vector3 Clamp(const Vector3& value1, const Vector3& min, const Vector3& max);
	static Vector3 Lerp(const Vector3& value1, const Vector3& value2,const float amount);

	static inline bool Compare(const Vector3& lhs, const Vector3& rhs, float tolerance = 0.0f)
	{		
		return (abs(lhs.X - rhs.X) <= tolerance) ||
			(abs(lhs.Y - rhs.Y) <= tolerance) ||
			(abs(lhs.Z - rhs.Z) <= tolerance);
	}

	#pragma region Operators - Boolean
	inline bool operator==(const Vector3& rhs) const
	{
		return this->X == rhs.X && this->Y == rhs.Y && this->Z == rhs.Z;
	}

	inline bool operator!=(const Vector3& rhs) const
	{
		return !(this->X == rhs.X && this->Y == rhs.Y && this->Z == rhs.Z);
	}
	#pragma endregion

	#pragma region Operations - Arithmetic
	inline Vector3 operator+ (const Vector3& vector) const
	{
		return Vector3(this->X + vector.X, this->Y + vector.Y, this->Z + vector.Z);
	}

	inline Vector3 operator- () const
	{
		return Vector3(-this->X, -this->Y, -this->Z);
	}

	inline Vector3 operator- (const Vector3& vector) const
	{
		return Vector3(this->X - vector.X, this->Y - vector.Y, this->Z - vector.Z);
	}

	inline Vector3 operator* (float rhs) const
	{
		return Vector3(this->X * rhs, this->Y * rhs, this->Z * rhs);
	}

	inline Vector3 operator/ (float rhs) const 
	{
		return Vector3(this->X / rhs, this->Y / rhs, this->Z / rhs);
	}
	#pragma endregion

	#pragma region Operations - Arithmetic - Update
	inline Vector3& Vector3::operator+= (const Vector3& rhs) 
	{
		this->X += rhs.X;
		this->Y += rhs.Y;
		this->Z += rhs.Z;

		return *this;
	}
	
	inline Vector3& Vector3::operator-= (const Vector3& rhs) 
	{
		this->X -= rhs.X;
		this->Y -= rhs.Y;
		this->Z -= rhs.Z;

		return *this;
	}
	#pragma endregion

	//static attributes
	static Vector3 Zero;
	static Vector3 One;
	static Vector3 UnitX;
	static Vector3 UnitY;
	static Vector3 UnitZ;

	static Vector3 Up;
	static Vector3 Down;
	static Vector3 Right;
	static Vector3 Left;
	static Vector3 Forward;
	static Vector3 Backward;

};
