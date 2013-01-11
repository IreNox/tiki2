
#include "Core/Vector2.h"

//#include <Math.h>
//#include <limits>
//
//const float MinFloat = (std::numeric_limits<float>::min)();

//bool Vector2::IsZero() const
//{
//	return (X*X + Y*Y) < MinFloat;
//}

void Vector2::Truncate(float maximum)
{
	if (this->Length() > maximum)
	{
		this->Normalize();

		*this = *this * maximum;
	}
}

#pragma region Cross, Negate, Reflect, Sign
Vector2 Vector2::Reflect(const Vector2& vector, const Vector2& normal)
{
	float num = vector.X * normal.X + vector.Y * normal.Y;
	return Vector2(vector.X - 2 * num * normal.X,vector.Y - 2 * num * normal.Y);
}
Vector2 Vector2::Clamp(const Vector2& value1, const Vector2& min, const Vector2& max)
{
	float num = value1.X;
	num = ((num > max.X) ? max.X : num);
	num = ((num < min.X) ? min.X : num);

	float num2 = value1.Y;
	num2 = ((num2 > max.Y) ? max.Y : num2);
	num2 = ((num2 < min.Y) ? min.Y : num2);

	return Vector2(num,num2);
}
Vector2 Vector2::Lerp(const Vector2& value1, const Vector2& value2, float amount)
{
	return Vector2(value1.X + (value2.X - value1.X) * amount, value1.Y + (value2.Y - value1.Y) * amount);
}
int Vector2::Sign(const Vector2& v2) const
{
	if (Y * v2.X > X * v2.Y)
		return -1;	// counterClockwise
	else 
		return 1;   // clockwise
}
#pragma endregion

#pragma region Length, Distance, Normalize Angle, Cross, Normalize, Perp
float Vector2::Distance(const Vector2& vector1, const Vector2& vector2)
{
	float num =  vector2.X - vector1.X;
	float num2 = vector2.Y - vector1.Y;
	return sqrt(num * num + num2 * num2);
}

float Vector2::DistanceSquared(const Vector2& vector1, const Vector2& vector2)
{
	float num =  vector2.X - vector1.X;
	float num2 = vector2.Y - vector1.Y;
	return num * num + num2 * num2;
}

void Vector2::Normalize()
{
	float num = 1 / sqrtf(this->X * this->X + this->Y * this->Y);
	this->X = this->X * num;
	this->Y = this->Y * num;
}

Vector2 Vector2::Normalize(const Vector2& vector)
{
	float num = 1 / sqrtf(vector.X * vector.X + vector.Y * vector.Y);
	return Vector2(vector.X * num, vector.Y * num);
}

Vector2 Vector2::Cross()
{
	return Vector2(-Y, X);
}


float Vector2::Angle(const Vector2& vector1, const Vector2& vector2)
{
	return acos(Dot(vector1,vector2) /(vector1.Length() * vector2.Length())) * (180 / 3.1415926f);
}
#pragma endregion

#pragma region Static
Vector2	Vector2::Zero  = Vector2(0.0f);
Vector2 Vector2::One   = Vector2(1.0f);
Vector2 Vector2::UnitX = Vector2(1.0f, 0.0f);
Vector2 Vector2::UnitY = Vector2(0.0f, 1.0f);
#pragma endregion
