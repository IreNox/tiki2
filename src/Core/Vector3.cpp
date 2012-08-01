

#include "Core/Vector3.h"

#pragma region Init
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

#pragma region Methods
float Vector3::Length() const
{
	return sqrt(
		(this->X * this->X) +
		(this->Y * this->Y) +
		(this->Z * this->Z)
		);
}
float Vector3::LengthSquared() const
{
	return (this->X * this->X) + (this->Y * this->Y) + (this->Z * this->Z);
}

void Vector3::Negate() 
{
	this->X = -this->X;
	this->Y = -this->Y;
	this->Z = -this->Z;
}
#pragma endregion Methods

#pragma region static Methods
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
float Vector3::DistanceSquared(const Vector3& vector1, const Vector3& vector2)
{
	return (vector1-vector2).LengthSquared();
}

Vector3 Vector3::Cross(const Vector3& vector1, const Vector3& vector2)
{
	return Vector3(
		(vector1.Y * vector2.Z) - (vector1.Z * vector2.Y),
		(vector1.Z * vector2.X) - (vector1.X * vector2.Z),
		(vector1.X * vector2.Y) - (vector1.Y * vector2.X)
	);
}

Vector3 Vector3::Negate(const Vector3& vector) 
{
	return Vector3(-vector.X, -vector.Y, - vector.Z);
}

Vector3 Vector3::Normalize(const Vector3& vector) 
{
	float length = sqrt(vector.X * vector.X + vector.Y * vector.Y + vector.Z * vector.Z);
	return Vector3(vector.X / length, vector.Y / length, vector.Z / length);

}
#pragma endregion


#pragma region Transform
Vector3 Vector3::Transform(const Matrix& matrix) const
{
	return Vector3();
	//return Vector3(
	//	this->X * matrix.M00 + this->Y * matrix.M01 + this->Z * matrix.M02 + matrix.M03,
	//	this->X * matrix.M10 + this->Y * matrix.M11 + this->Z * matrix.M12 + matrix.M13,
	//	this->X * matrix.M20 + this->Y * matrix.M21 + this->Z * matrix.M22 + matrix.M23
	//);
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

Vector3& Vector3::operator+= (const Vector3& rhs) 
{
	return *this = (*this + rhs);
}

Vector3 Vector3::operator- () const
{
	return Vector3(-this->X, -this->Y, -this->Z);
}

Vector3 Vector3::operator- (const Vector3& vector) const
{
	return Vector3(
		this->X - vector.X,
		this->Y - vector.Y,
		this->Z - vector.Z
	);
}

Vector3& Vector3::operator-= (const Vector3& rhs) 
{
	return *this = *this - rhs;
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

Vector3 Vector3::Reflect( const Vector3& vector, const Vector3& normal )
{
	float num = vector.X * normal.X + vector.Y * normal.Y + vector.Z * normal.Z;

	return Vector3(
		vector.X - 2 * num * normal.X,
		vector.Y - 2 * num * normal.Y,
		vector.Z - 2 * num * normal.Z);
}

Vector3 Vector3::Clamp( const Vector3& value1, const Vector3& min, const Vector3& max )
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

	return Vector3(num,num2,num3);
}

Vector3 Vector3::Lerp( const Vector3& value1, const Vector3& value2,const float amount )
{
	return Vector3(
		value1.X + (value2.X - value1.X) * amount,
		value1.Y + (value2.Y - value1.Y) * amount,
		value1.Z + (value2.Z - value1.Z) * amount);
}

#pragma endregion

#pragma region statics
Vector3 Vector3::Zero = Vector3(0.0);
Vector3 Vector3::One = Vector3(1.0);
Vector3 Vector3::UnitX = Vector3(1,0,0);
Vector3 Vector3::UnitY = Vector3(0,1,0);
Vector3 Vector3::UnitZ = Vector3(0,0,1);

Vector3 Vector3::Up = Vector3(0,1,0);
Vector3 Vector3::Down = Vector3(0,-1,0);
Vector3 Vector3::Right = Vector3(1,0,0);
Vector3 Vector3::Left = Vector3(-1,0,0);

Vector3 Vector3::ForwardRH = Vector3(0,0,-1);
Vector3 Vector3::BackwardRH = Vector3(0,0,1);
Vector3 Vector3::ForwardLH = Vector3(0,0,1);
Vector3 Vector3::BackwardLH = Vector3(0,0,-1);
#pragma endregion statics