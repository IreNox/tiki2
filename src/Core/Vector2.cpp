
#pragma region Init
#include "Core/Vector2.h"
#include <Math.h>
#include <limits>

const float MinFloat = (std::numeric_limits<float>::min)();

int Vector2::Dimensions = 2;

Vector2::Vector2(void)
	: X(0), Y(0)
{
}

Vector2::Vector2(float all)
	: X(all), Y(all)
{
}

Vector2::Vector2(float x, float y)
	: X(x), Y(y)
{
}

Vector2::Vector2(float* arr)
	: X(arr[0]), Y(arr[1])
{
}

Vector2::~Vector2(void)
{
}
#pragma endregion

bool Vector2::IsZero() const
{
	return (X*X + Y*Y) < MinFloat;
}

void Vector2::Truncate(float maximum)
{
	if (this->Length() > maximum)
	{
		this->Normalize();

		*this = *this * maximum;
	}
}

#pragma region Dot, Cross, Negate, Reflect, Sign
float Vector2::Dot(const Vector2& vector1, const Vector2& vector2)
{
	return vector1.X * vector2.X + vector1.Y * vector2.Y;
}

void Vector2::Negate()
{
	this->X = -this->X;
	this->Y = -this->Y;
}
Vector2 Vector2::Negate(const Vector2& vector)
{
	return Vector2(-vector.X, -vector.Y);
}

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
float Vector2::Length() const
{
	return sqrt(
		(this->X * this->X) +
		(this->Y * this->Y)
	);
}
float Vector2::LengthSquared() const
{
	return (this->X * this->X) + (this->Y * this->Y);
}

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

#pragma region Operators
#pragma region bool operations
bool Vector2::operator== (const Vector2& rhs) const
{
	return	(this->X == rhs.X) &&
		(this->Y == rhs.Y);
}

bool Vector2::operator!= (const Vector2& rhs) const
{
	return this->X != rhs.X || this->Y != rhs.Y;
}
#pragma endregion bool operations

#pragma region arithmetic operations
Vector2 Vector2::operator+ (const Vector2& rhs) const
{
	return Vector2(this->X + rhs.X, this->Y + rhs.Y);
}
Vector2 Vector2::operator- () const
{
	return Vector2(-this->X,-this->Y);
}
Vector2 Vector2::operator- (const Vector2& rhs) const
{
	return Vector2(this->X - rhs.X , this->Y - rhs.Y);
}
Vector2 Vector2::operator* (const float& rhs) const
{
	return Vector2(this->X * rhs, this->Y * rhs);
}
Vector2 Vector2::operator/ (const float& rhs) const
{
	return Vector2(this->X / rhs, this->Y / rhs);
}
#pragma endregion arithmetic operations

#pragma region arithmetic updates
Vector2& Vector2::operator+= (const Vector2& rhs)
{
	return *this = *this + rhs;
}
Vector2& Vector2::operator-= (const Vector2& rhs)
{
	return *this = *this - rhs;
}

Vector2& Vector2::operator*= (const float& rhs)
{
	return *this = *this * rhs;
}

Vector2& Vector2::operator/= (const float& rhs)
{
	return *this = *this / rhs;
}

#pragma endregion arithmetic updates

#pragma endregion

#pragma region static attributes
Vector2	Vector2::Zero = Vector2(0.0);
Vector2 Vector2::One = Vector2(1.0);
Vector2 Vector2::UnitX = Vector2(1.0,0.0);
Vector2 Vector2::UnitY = Vector2(0.0,1.0);

#pragma endregion
