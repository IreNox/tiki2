#pragma once

class Vector4
{
public:
	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};
		float arr[4];
	};

	Vector4(void);
	Vector4(float all);
	Vector4(float* arr);
	Vector4(float x, float y, float z, float w);

	virtual ~Vector4(void);

	
	float Angle(Vector4 vector);

	Vector4 Negate();
	Vector4 Cross(Vector4 vector);

	float Length();
	float LengthSquared();
	static float Distance(const Vector4& vector1, const Vector4& vector2);
	static float DistanceSquared(const Vector4& vector1, const Vector4& vector2);
	static float Dot(const Vector4& vector1, const Vector4& vector2);

	Vector4 Normalize();
	static Vector4 Normalize(const Vector4& vector);
	static Vector4 Clamp(Vector4& value1, const Vector4& min, const Vector4& max);
	static Vector4 Lerp(const Vector4& value1, const Vector4& value2, float amount);


	//boolean operators
	bool Vector4::operator== (const Vector4& rhs) const;
	bool Vector4::operator!= (const Vector4& rhs) const;

	//arithmetic operation
	Vector4 operator+ (const Vector4& rhs) const;
	Vector4 operator- () const;
	Vector4 operator- (const Vector4& rhs) const;
	Vector4 operator* (float rhs ) const;
	Vector4 operator/ (float rhs) const;

	//arithmetic updates
	Vector4& operator+= (const Vector4& rhs);
	Vector4& operator-= (const Vector4& rhs);

	static int Dimensions;
	static Vector4 Input();

	//static attributes

	static Vector4 Identity;
	static Vector4 Zero; 
	static Vector4 One; 
	static Vector4 UnitX; 
	static Vector4 UnitY;
	static Vector4 UnitZ; 
	static Vector4 UnitW; 
};