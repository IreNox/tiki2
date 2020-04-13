#pragma once

#include <math.h>
#include <limits>

const float MinFloat = (std::numeric_limits<float>::min)();

//TODO INLINE
class Vector2
{
public:

	#pragma region Vars
	union
	{
		struct
		{
			float X;
			float Y;
		};

		float arr[2];
	};
	#pragma endregion

	#pragma region Class	
	inline Vector2() : X(0), Y(0) {}
	inline Vector2(float all) : X(all), Y(all) {}
	inline Vector2(float* arr) : X(arr[0]), Y(arr[1]) {}
	inline Vector2(float x, float y) : X(x), Y(y) {}

	inline ~Vector2() {}
	#pragma endregion

	/*! @brief returns true if both x and y are near zero */
	inline bool IsZero() const { return (X*X + Y*Y) < MinFloat; }

	// adjusts x and y so that the length of the vector does not exceed max
	void Truncate(float maximum);
	
	float Length() const { return sqrtf((X * X) + (Y * Y)); }
	inline float LengthSquared() const { return (X * X) + (Y * Y); }

	void Normalize();
	static Vector2 Normalize(const Vector2& vector);

	// returns a vector perpendicular to this vector
	Vector2 Cross();

	static float Distance(const Vector2& vector1, const Vector2& vector2);
	static float DistanceSquared(const Vector2& vector1, const Vector2& vector2);

	inline static float Dot(const Vector2& vector1, const Vector2& vector2) { return vector1.X * vector2.X + vector1.Y * vector2.Y; }
	static float Angle(const Vector2& vector1, const Vector2& vector2);
	static Vector2 Reflect(const Vector2& vector, const Vector2& normal);
	static Vector2 Clamp(const Vector2& value1, const Vector2& min, const Vector2& max);
	static Vector2 Lerp(const Vector2& value1, const Vector2& value2, float amount);

	//returns positive if v2 is clockwise of this vector,
	//negative if anticlockwise (assuming the Y axis is pointing down,
	//X axis to right like a Window app)
	int Sign(const Vector2& v2) const;

	//boolean comparison
	inline bool Vector2::operator== (const Vector2& rhs) const { return X == rhs.X && Y == rhs.Y; }
	inline bool Vector2::operator!= (const Vector2& rhs) const  { return X != rhs.X || Y != rhs.Y; }

	//arithmetic operations
	inline Vector2 operator+ (const Vector2& rhs) const { return Vector2(X + rhs.X, Y + rhs.Y); }
	inline Vector2 operator- (const Vector2& rhs) const { return Vector2(X - rhs.X, Y - rhs.Y); }
	inline Vector2 operator* (const float& rhs) const { return Vector2(X * rhs, Y * rhs); }
	inline Vector2 operator/ (const float& rhs) const { return Vector2(X / rhs, Y / rhs); }
	inline Vector2 operator- () const { return Vector2(-X, -Y); }

	//arithmetic updates
	inline Vector2& operator+= (const Vector2& rhs) { X += rhs.X; Y += rhs.Y; return *this; }
	inline Vector2& operator-= (const Vector2& rhs) { X -= rhs.X; Y -= rhs.Y; return *this; }

	inline Vector2& operator*= (const float& rhs) { X *= rhs; Y *= rhs; return *this; }
	inline Vector2& operator/= (const float& rhs) { X /= rhs; Y /= rhs; return *this; }

	inline float operator[](const int& index) { return arr[index]; }

	//static attributes
	static Vector2 Zero;
	static Vector2 One;
	static Vector2 UnitX;
	static Vector2 UnitY;
};