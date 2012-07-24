#pragma once

class Vector2
{
public:
	union
	{
		struct
		{
			float X;
			float Y;
		};

		float arr[2];
	};

	//float X;
	//float Y;

	Vector2(void);
	Vector2(float all);
	Vector2(float* arr);
	Vector2(float x, float y);

	~Vector2(void);

	Vector2 Add(Vector2 vector);	
	Vector2 Substract(Vector2 vector);

	Vector2 Divide(float value);
	Vector2 Multiply(float value);

	float Dot(Vector2 vector);
	float Angle(Vector2 vector);

	Vector2 Negate();
	Vector2 Cross(Vector2 vector);
	Vector2 Reflect(Vector2 normal);

	float Length();
	float Distance(Vector2 vector);

	Vector2 Normalize();
	void Vector2::Print();

	bool Vector2::operator== (Vector2 rhs);
	bool Vector2::operator!= (Vector2 rhs);

	Vector2 operator+ (Vector2 rhs);
	Vector2 operator+= (Vector2 rhs);

	Vector2 operator- ();
	Vector2 operator- (Vector2 rhs);
	Vector2 operator-= (Vector2 rhs);

	Vector2 operator* (float rhs);
	Vector2 operator/ (float rhs);

	static int Dimensions;
	static Vector2 Input();
};