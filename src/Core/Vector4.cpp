
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

Vector4::Vector4( const Vector3& vec, float w )
: X( vec.X ), Y( vec.Y ), Z( vec.Z ), W( w )
{
}

Vector4::~Vector4(void)
{
}
#pragma endregion

#pragma region Dot, Cross, Negate, Reflect
float Vector4::Dot(const Vector4& vector1, const Vector4& vector2)
{
	return vector1.X * vector2.X + vector1.Y * vector2.Y + vector1.Z * vector2.Z + vector1.W * vector2.W;
}

Vector4 Vector4::Cross(Vector4 vector)
{
	return Vector4(0, 0, 0, 0);
}

Vector4 Vector4::Negate()
{
	return *this * -1;
}
#pragma endregion

#pragma region Length, Distance, Angle, Print
float Vector4::Length()
{
	return sqrtf(
		(this->X * this->X) +
		(this->Y * this->Y) +
		(this->Z * this->Z) +
		(this->W * this->W)
	);
}
float Vector4::LengthSquared()
{
	return(this->X * this->X) + (this->Y * this->Y) + (this->Z * this->Z) + (this->W * this->W);
}

float Vector4::Distance(const Vector4& value1, const Vector4& value2)
{
	float num = value1.X - value2.X;
	float num2 = value1.Y - value2.Y;
	float num3 = value1.Z - value2.Z;
	float num4 = value1.W - value2.W;
	float num5 = num * num + num2 * num2 + num3 * num3 + num4 * num4;
	return sqrtf(num5);
}
float Vector4::DistanceSquared(const Vector4& value1, const Vector4& value2)
{
	float num = value1.X - value2.X;
	float num2 = value1.Y - value2.Y;
	float num3 = value1.Z - value2.Z;
	float num4 = value1.W - value2.W;
	return num * num + num2 * num2 + num3 * num3 + num4 * num4;
}

float Vector4::Angle(Vector4 vector)
{
	return acosf(Dot(*this, vector)/
		(this->Length() * vector.Length())
	) * (180 / 3.1415926f);
}

Vector4 Vector4::Normalize()
{
	return *this = *this / this->Length();
}
Vector4 Vector4::Normalize(const Vector4& vector)
{
	float num = vector.X * vector.X + vector.Y * vector.Y + vector.Z * vector.Z + vector.W * vector.W;
	return Vector4(vector.X / num, vector.Y / num, vector.Z / num, vector.W / num);
}
#pragma endregion

#pragma region Operators
bool Vector4::operator== (const Vector4& rhs) const
{
	return	(this->X == rhs.X) &&
			(this->Y == rhs.Y) &&
			(this->Z == rhs.Z) &&
			(this->W == rhs.W);
}

bool Vector4::operator!= (const Vector4& rhs) const
{
	return	!(*this == rhs);
}

Vector4 Vector4::operator+ (const Vector4& rhs) const
{
	return Vector4(this->X + rhs.X , this->Y + rhs.Y, this->Z + rhs.Z, this->W + rhs.W);
}

Vector4& Vector4::operator+= (const Vector4& rhs)
{
	return *this = *this + rhs;
}

Vector4 Vector4::operator- () const
{
	return *this * -1;
}

Vector4 Vector4::operator- (const Vector4& rhs) const
{
	return Vector4(this->X - rhs.X , this->Y - rhs.Y, this->Z - rhs.Z, this->W - rhs.W);
}

Vector4& Vector4::operator-= (const Vector4& rhs) 
{
	return *this = *this - rhs;
}

Vector4 Vector4::operator* (float rhs) const
{
	return Vector4(this->X * rhs, this->Y * rhs, this->Z * rhs, this->W * rhs);
}

Vector4 Vector4::operator/ (float rhs) const
{
	return Vector4(this->X / rhs, this->Y / rhs, this->Z / rhs, this->W / rhs);
}

Vector4 Vector4::Clamp( Vector4& value1, const Vector4& min, const Vector4& max )
{
	float num = value1.X;
	num = ((num > max.X) ? max.X : num);
	num = ((num < min.X) ? min.X : num);
	float num2 = value1.Y;
	num2 = ((num2 > max.Y) ? max.Y : num2);
	num2 = ((num2 < min.Y) ? min.Y : num2);
	float num3 = value1.Z;
	num3 = ((num3 > max.Z) ? max.Z : num3);
	num3 = ((num3 < min.Z) ? min.Z : num3);
	float num4 = value1.W;
	num4 = ((num4 > max.W) ? max.W : num4);
	num4 = ((num4 < min.W) ? min.W : num4);

	return Vector4(num, num2, num3, num4 );

}

Vector4 Vector4::Lerp( const Vector4& value1, const Vector4& value2, float amount )
{
	Vector4 result;
	result.X = value1.X + (value2.X - value1.X) * amount;
	result.Y = value1.Y + (value2.Y - value1.Y) * amount;
	result.Z = value1.Z + (value2.Z - value1.Z) * amount;
	result.W = value1.W + (value2.W - value1.W) * amount;
	return result;
}

#pragma endregion

#pragma region static attributes
Vector4 Vector4::Zero = Vector4(0,0,0,0); 
Vector4 Vector4::One = Vector4(1,1,1,1); 
Vector4 Vector4::UnitX = Vector4(1,0,0,0); 
Vector4 Vector4::UnitY = Vector4(0,1,0,0);
Vector4 Vector4::UnitZ = Vector4(0,0,1,0); 
Vector4 Vector4::UnitW = Vector4(0,0,0,1); 

#pragma endregion