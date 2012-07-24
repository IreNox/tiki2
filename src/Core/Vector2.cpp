
#pragma region Init
#include "Core/Vector2.h"
#include <Math.h>

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

#pragma region Add, Substract
Vector2 Vector2::Add(Vector2 vector)
{
	return Vector2(
		this->X + vector.X,
		this->Y + vector.Y
	);
}

Vector2 Vector2::Substract(Vector2 vector)
{
	return Vector2(
		this->X - vector.X,
		this->Y - vector.Y
	);
}
#pragma endregion

#pragma region Multiply, Divide
Vector2 Vector2::Multiply(float value)
{
	return Vector2(
		this->X * value,
		this->Y * value
	);
}

Vector2 Vector2::Divide(float value)
{
	return Vector2(
		this->X / value,
		this->Y / value
	);
}
#pragma endregion

#pragma region Dot, Cross, Negate, Reflect
float Vector2::Dot(Vector2 vector)
{
	return	(this->X * vector.X) +
			(this->Y * vector.Y);
}

Vector2 Vector2::Cross(Vector2 vector)
{
	return Vector2(0, 0);
}

Vector2 Vector2::Negate()
{
	return this->Multiply(-1.0f);
}

Vector2 Vector2::Reflect(Vector2 normal)
{
	Vector2 negate = normal.Negate();
	Vector2 twoDot = Vector2(2.0f) * this->Dot(normal);

	return this->Add(
		Vector2(
			twoDot.X * negate.X,
			twoDot.Y * negate.Y
		)
	);
}
#pragma endregion

#pragma region Length, Distance, Angle, Cross, Normalize
float Vector2::Length()
{
	return sqrt(
		(this->X * this->X) +
		(this->Y * this->Y)
	);
}

float Vector2::Distance(Vector2 vector)
{
	return (*this - vector).Length();
}

Vector2 Vector2::Normalize()
{
	return *this / this->Length();
}

float Vector2::Angle(Vector2 vector)
{
	return acos(
		this->Dot(vector) /
		(this->Length() * vector.Length())
	) * (180 / 3.1415926f);
}
#pragma endregion

#pragma region Operators
bool Vector2::operator== (Vector2 rhs)
{
	return	(this->X == rhs.X) &&
			(this->Y == rhs.Y);
}

bool Vector2::operator!= (Vector2 rhs)
{
	return	!(*this == rhs);
}

Vector2 Vector2::operator+ (Vector2 rhs)
{
	return this->Add(rhs);
}

Vector2 Vector2::operator+= (Vector2 rhs)
{
	return this->Add(rhs);
}

Vector2 Vector2::operator- ()
{
	return this->Negate();
}

Vector2 Vector2::operator- (Vector2 rhs)
{
	return this->Substract(rhs);
}

Vector2 Vector2::operator-= (Vector2 rhs)
{
	return this->Substract(rhs);
}

Vector2 Vector2::operator* (float rhs)
{
	return this->Multiply(rhs);
}

Vector2 Vector2::operator/ (float rhs)
{
	return this->Divide(rhs);
}
#pragma endregion
