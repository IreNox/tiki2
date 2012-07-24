
#include "Core/Vector4.h"
#include <Math.h>

#pragma region Init
Vector4::Vector4(void)
	: X(0), Y(0), Z(0)
{
}

Vector4::Vector4(float all)
	: X(all), Y(all), Z(all), W(all)
{
}

Vector4::Vector4(float x, float y, float z, float w)
	: X(x), Y(y), Z(z), W(w)
{
}

Vector4::Vector4(float* arr)
	: X(arr[0]), Y(arr[1]), Z(arr[2]), W(arr[3])
{
}

Vector4::~Vector4(void)
{
}
#pragma endregion

#pragma region Add, Substract
Vector4 Vector4::Add(Vector4 vector)
{
	return Vector4(
		this->X + vector.X,
		this->Y + vector.Y,
		this->Z + vector.Z,
		this->W + vector.W
	);
}

Vector4 Vector4::Substract(Vector4 vector)
{
	return Vector4(
		this->X - vector.X,
		this->Y - vector.Y,
		this->Z - vector.Z,
		this->W - vector.W
	);
}
#pragma endregion

#pragma region Multiply, Divide
Vector4 Vector4::Multiply(float value)
{
	return Vector4(
		this->X * value,
		this->Y * value,
		this->Z * value,
		this->W * value
	);
}

Vector4 Vector4::Divide(float value)
{
	return Vector4(
		this->X / value,
		this->Y / value,
		this->Z / value,
		this->W / value
	);
}
#pragma endregion

#pragma region Dot, Cross, Negate, Reflect
float Vector4::Dot(Vector4 vector)
{
	return	(this->X * vector.X) +
			(this->Y * vector.Y) +
			(this->Z * vector.Z) +
			(this->W * vector.W);
}

Vector4 Vector4::Cross(Vector4 vector)
{
	return Vector4(0, 0, 0, 0);
}

Vector4 Vector4::Negate()
{
	return this->Multiply(-1.0f);
}

Vector4 Vector4::Reflect(Vector4 normal)
{
	Vector4 negate = normal.Negate();
	Vector4 twoDot = Vector4(2.0f) * this->Dot(normal);

	return this->Add(
		Vector4(
			twoDot.X * negate.X,
			twoDot.Y * negate.Y,
			twoDot.Z * negate.Z,
			twoDot.W * negate.W
		)
	);
}
#pragma endregion

#pragma region Length, Distance, Angle, Print
float Vector4::Length()
{
	return sqrt(
		(this->X * this->X) +
		(this->Y * this->Y) +
		(this->Z * this->Z) +
		(this->W * this->W)
	);
}

float Vector4::Distance(Vector4 vector)
{
	return (*this - vector).Length();
}

float Vector4::Angle(Vector4 vector)
{
	return acos(
		this->Dot(vector) /
		(this->Length() * vector.Length())
	) * (180 / 3.1415926f);
}

Vector4 Vector4::Normalize()
{
	return *this / this->Length();
}
#pragma endregion

#pragma region Operators
bool Vector4::operator== (Vector4 rhs)
{
	return	(this->X == rhs.X) &&
			(this->Y == rhs.Y) &&
			(this->Z == rhs.Z) &&
			(this->W == rhs.W);
}

bool Vector4::operator!= (Vector4 rhs)
{
	return	!(*this == rhs);
}

Vector4 Vector4::operator+ (Vector4 rhs)
{
	return this->Add(rhs);
}

Vector4 Vector4::operator+= (Vector4 rhs)
{
	return this->Add(rhs);
}

Vector4 Vector4::operator- ()
{
	return this->Negate();
}

Vector4 Vector4::operator- (Vector4 rhs)
{
	return this->Substract(rhs);
}

Vector4 Vector4::operator-= (Vector4 rhs)
{
	return this->Substract(rhs);
}

Vector4 Vector4::operator* (float rhs)
{
	return this->Multiply(rhs);
}

Vector4 Vector4::operator* (Vector4 rhs)
{
	return this->Cross(rhs);
}

Vector4 Vector4::operator/ (float rhs)
{
	return this->Divide(rhs);
}
#pragma endregion