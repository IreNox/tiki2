#pragma once

#include "Matrix.h"

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void);
	Vector3(float all);
	Vector3(float* arr);
	Vector3(float x, float y, float z);

	~Vector3(void);

	float Length() const;
	Vector3 Negate() const;
	Vector3 Normalize() const;
	Vector3 Transform(const Matrix& matrix) const;

	static float Dot(const Vector3& vector1, const Vector3& vector2);
	static float Angle(const Vector3& vector1, const Vector3& vector2);
	static float Distance(const Vector3& vector1, const Vector3& vector2);

	static Vector3 Cross(const Vector3& vector1, const Vector3& vector2);

	bool operator== (const Vector3& rhs) const;
	bool operator!= (const Vector3& rhs) const;

	Vector3 operator+ (const Vector3& rhs) const;
	Vector3 operator+= (const Vector3& rhs) const;

	Vector3 operator- () const ;
	Vector3 operator- (const Vector3& rhs) const;
	Vector3 operator-= (const Vector3& rhs) const;

	Vector3 operator* (float rhs) const;
	Vector3 operator/ (float rhs) const;
};