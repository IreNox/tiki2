
#include <Math.h>
#include "Core/Vector3.h"

#pragma region Class
Vector3::Vector3(void)
	: X(0), Y(0), Z(0)
{
}

Vector3::Vector3(float all)
	: X(all), Y(all), Z(all)
{
}

Vector3::Vector3(float x, float y, float z)
	: X(x), Y(y), Z(z)
{
}

Vector3::Vector3(float* arr)
	: X(arr[0]), Y(arr[1]), Z(arr[2])
{
}

Vector3::~Vector3(void)
{
}
#pragma endregion

#pragma region Dot, Distance, Cross
float Vector3::Dot(const Vector3& vector1, const Vector3& vector2)
{
	return	(vector1.X * vector2.X) +
			(vector1.Y * vector2.Y) +
			(vector1.Z * vector2.Z);
}

float Vector3::Angle(const Vector3& vector1, const Vector3& vector2)
{
	float dot = Vector3::Dot(vector1, vector2);
	float len = vector1.Length() * vector2.Length();

	return acos(dot / len) * (180 / 3.1415926f);
}

float Vector3::Distance(const Vector3& vector1, const Vector3& vector2)
{
	return (vector1 - vector2).Length();
}

Vector3 Vector3::Cross(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(
		(vector1.Y * vector2.Z) - (vector1.Z * vector2.Y),
		(vector1.Z * vector2.X) - (vector1.X * vector2.Z),
		(vector1.X * vector2.Y) - (vector1.Y * vector2.X)
	);
}
#pragma endregion

#pragma region Length, Negate, Normalize
float Vector3::Length() const
{
	return sqrt(
		(this->X * this->X) +
		(this->Y * this->Y) +
		(this->Z * this->Z)
	);
}

Vector3 Vector3::Negate() const
{
	return Vector3(
		-this->X,
		-this->Y,
		-this->Z
		);
}

Vector3 Vector3::Normalize() const
{
	return *this / this->Length();
}
#pragma endregion

#pragma region Transform
Vector3 Vector3::Transform(const Matrix& matrix) const
{
	return Vector3(
		this->X * matrix.M00 + this->Y * matrix.M01 + this->Z * matrix.M02 + matrix.M03,
		this->X * matrix.M10 + this->Y * matrix.M11 + this->Z * matrix.M12 + matrix.M13,
		this->X * matrix.M20 + this->Y * matrix.M21 + this->Z * matrix.M22 + matrix.M23
	);
}
#pragma endregion

#pragma region Operators
bool Vector3::operator== (const Vector3& rhs) const
{
	return	(this->X == rhs.X) &&
			(this->Y == rhs.Y) &&
			(this->Z == rhs.Z);
}

bool Vector3::operator!= (const Vector3& rhs) const
{
	return	!(*this == rhs);
}

Vector3 Vector3::operator+ (const Vector3& vector) const
{
	return Vector3(
		this->X + vector.X,
		this->Y + vector.Y,
		this->Z + vector.Z
	);
}

Vector3 Vector3::operator+= (const Vector3& rhs) const
{
	return *this + rhs;
}

Vector3 Vector3::operator- () const
{
	return this->Negate();
}

Vector3 Vector3::operator- (const Vector3& vector) const
{
	return Vector3(
		this->X - vector.X,
		this->Y - vector.Y,
		this->Z - vector.Z
	);
}

Vector3 Vector3::operator-= (const Vector3& rhs) const
{
	return *this - rhs;
}

Vector3 Vector3::operator* (float rhs) const
{
	return Vector3(
		this->X * rhs,
		this->Y * rhs,
		this->Z * rhs
	);
}

Vector3 Vector3::operator/ (float rhs) const 
{
	return Vector3(
		this->X / rhs,
		this->Y / rhs,
		this->Z / rhs
	);
}
#pragma endregion