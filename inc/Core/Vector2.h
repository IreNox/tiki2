#pragma once

class Vector2
{
public:

	//struct
	union
	{
		struct
		{
			float X;
			float Y;
		};

		float arr[2];
	};

	//constructor
	Vector2(void);
	Vector2(float all);
	Vector2(float* arr);
	Vector2(float x, float y);

	~Vector2(void);

	float Length() const;
	float LengthSquared() const;

	void Negate();
	static Vector2 Negate(const Vector2& vector);

	void Normalize();
	static Vector2 Normalize(const Vector2& vector);

	static float Distance(const Vector2& vector1, const Vector2& vector2);
	static float DistanceSquared(const Vector2& vector1, const Vector2& vector2);

	static float Dot(const Vector2& vector1, const Vector2& vector2);
	static float Angle(const Vector2& vector1, const Vector2& vector2);
	static Vector2 Reflect(const Vector2& vector, const Vector2& normal);
	static Vector2 Clamp(const Vector2& value1, const Vector2& min, const Vector2& max);
	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);


	//boolean comparison
	bool Vector2::operator== (const Vector2& rhs) const;
	bool Vector2::operator!= (const Vector2& rhs) const;

	//arithmetic operations
	Vector2 operator+ (const Vector2& rhs) const;
	Vector2 operator- (const Vector2& rhs) const;
	Vector2 operator- () const;
	Vector2 operator* (const float& rhs) const;
	Vector2 operator/ (const float& rhs) const;

	//arithmetic updates
	Vector2& operator+= (const Vector2& rhs);
	Vector2& operator-= (const Vector2& rhs);


	static int Dimensions;
	static Vector2 Input();

	//static attributes
	static Vector2 Zero;
	static Vector2 One;
	static Vector2 UnitX;
	static Vector2 UnitY;
};