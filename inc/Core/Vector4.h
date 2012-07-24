#pragma once

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;

	Vector4(void);
	Vector4(float all);
	Vector4(float* arr);
	Vector4(float x, float y, float z, float w);

	virtual ~Vector4(void);

	Vector4 Add(Vector4 vector);	
	Vector4 Substract(Vector4 vector);

	Vector4 Divide(float value);
	virtual Vector4 Multiply(float value);

	float Dot(Vector4 vector);
	float Angle(Vector4 vector);

	Vector4 Negate();
	Vector4 Cross(Vector4 vector);
	Vector4 Reflect(Vector4 normal);

	float Length();
	float Distance(Vector4 vector);

	Vector4 Normalize();

	void Vector4::Print();

	bool Vector4::operator== (Vector4 rhs);
	bool Vector4::operator!= (Vector4 rhs);

	Vector4 operator+ (Vector4 rhs);
	Vector4 operator+= (Vector4 rhs);

	Vector4 operator- ();
	Vector4 operator- (Vector4 rhs);
	Vector4 operator-= (Vector4 rhs);

	Vector4 operator* (float rhs);
	Vector4 operator* (Vector4 rhs);

	Vector4 operator/ (float rhs);

	static int Dimensions;
	static Vector4 Input();
};