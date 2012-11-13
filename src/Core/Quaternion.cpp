#include "Core/Quaternion.h"
#include <math.h>

Quaternion::Quaternion()
	:X(0), Y(0), Z(0), W(0)
{

}
Quaternion::Quaternion(float x, float y, float z, float w)
	:X(x), Y(y), Z(z), W(w)
{

}
Quaternion::~Quaternion()
{

}
#pragma region methods
float Quaternion::LengthSquared()
{
	return X * X + Y * Y + Z * Z + W * W;
}
float Quaternion::Length()
{
	return sqrtf(X * X + Y * Y + Z * Z + W * W);
}

void Quaternion::Normalize()
{
	float num = 1 / sqrtf(X * X + Y * Y + Z * Z + W * W);
	X *= num;
	Y *= num;
	Z *= num;
	W *= num;
}
Quaternion Quaternion::Normalize(const Quaternion& quat)
{
	float num = 1 / sqrtf(quat.X * quat.X + quat.Y * quat.Y + quat.Z * quat.Z + quat.W * quat.W);
	return Quaternion(quat.X * num, quat.Y * num, quat.Z * num, quat.W * num);
}

void Quaternion::Conjugate()
{
	this->X = -this->X;
	this->Y = -this->Y;
	this->Z = -this->Z;
}
Quaternion Quaternion::Conjugate(const Quaternion& quat)
{
	return Quaternion(-quat.X,-quat.Y,-quat.Z,quat.W);
}

void Quaternion::Inverse()
{
	float num = 1 / sqrtf(X * X + Y * Y + Z * Z + W * W);
	this->X = -this->X * num;
	this->Y = -this->Y * num;
	this->Z = -this->Z * num;
	this->W = this->W * num;
}
Quaternion Quaternion::Inverse(const Quaternion& quat)
{
	float num = 1 / sqrtf(quat.X * quat.X + quat.Y * quat.Y + quat.Z * quat.Z + quat.W * quat.W);
	return Quaternion(-quat.X * num, -quat.Y * num, -quat.Z * num, quat.W * num);
}

void Quaternion::Negate()
{
	this->X = -this->X;
	this->Y = -this->Y;
	this->Z = -this->Z;
	this->W = -this->W;
}
Quaternion Quaternion::Negate(const Quaternion& quat)
{
	return Quaternion(-quat.X, -quat.Y, -quat.Z, -quat.W);
}

float Quaternion::Dot(const Quaternion& quaternion1, const Quaternion& quaternion2)
{
	return quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W;
}
Quaternion Quaternion::Concatenate(const Quaternion& quaternion1, const Quaternion& quaternion2)
{
	float x = quaternion2.X;
	float y = quaternion2.Y;
	float z = quaternion2.Z;
	float w = quaternion2.W;

	float x2 = quaternion1.X;
	float y2 = quaternion1.Y;
	float z2 = quaternion1.Z;
	float w2 = quaternion1.W;

	float num = y * z2 - z * y2;
	float num2 = z * x2 - x * z2;
	float num3 = x * y2 - y * x2;
	float num4 = x * x2 + y * y2 + z * z2;

	return Quaternion(x * w2 + x2 * w + num, y * w2 + y2 * w + num2, z * w2 + z2 * w + num3, w * w2 - num4);
}

Quaternion Quaternion::Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, float amount)
{
	float num = quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W;
	bool flag = false;
	if (num < 0)
	{
		flag = true;
		num = -num;
	}
	float num2;
	float num3;
	if (num > 0.999999f)
	{
		num2 = 1 - amount;
		num3 = (flag ? (-amount) : amount);
	}
	else
	{
		float num4 = (float)acos((double)num);
		float num5 = (float)(1.0 / sin((double)num4));
		num2 = (float)sin((double)((1 - amount) * num4)) * num5;
		num3 = (flag ? ((float)(-(float)sin((double)(amount * num4))) * num5) : ((float)sin((double)(amount * num4)) * num5));
	}
	Quaternion result;
	result.X = num2 * quaternion1.X + num3 * quaternion2.X;
	result.Y = num2 * quaternion1.Y + num3 * quaternion2.Y;
	result.Z = num2 * quaternion1.Z + num3 * quaternion2.Z;
	result.W = num2 * quaternion1.W + num3 * quaternion2.W;
	return result;
}
Quaternion Quaternion::Lerp(const Quaternion& quaternion1, const Quaternion& quaternion2, float amount)
{
	float num = 1 - amount;
	Quaternion result;
	float num2 = quaternion1.X * quaternion2.X + quaternion1.Y * quaternion2.Y + quaternion1.Z * quaternion2.Z + quaternion1.W * quaternion2.W;
	if (num2 >= 0)
	{
		result.X = num * quaternion1.X + amount * quaternion2.X;
		result.Y = num * quaternion1.Y + amount * quaternion2.Y;
		result.Z = num * quaternion1.Z + amount * quaternion2.Z;
		result.W = num * quaternion1.W + amount * quaternion2.W;
	}
	else
	{
		result.X = num * quaternion1.X - amount * quaternion2.X;
		result.Y = num * quaternion1.Y - amount * quaternion2.Y;
		result.Z = num * quaternion1.Z - amount * quaternion2.Z;
		result.W = num * quaternion1.W - amount * quaternion2.W;
	}
	float num3 = result.X * result.X + result.Y * result.Y + result.Z * result.Z + result.W * result.W;
	float num4 = 1 / (float)sqrt((double)num3);
	result.X *= num4;
	result.Y *= num4;
	result.Z *= num4;
	result.W *= num4;
	return result;
}


#pragma endregion

#pragma region static methods

Quaternion Quaternion::Identity = Quaternion(0,0,0,1);

#pragma endregion


#pragma region operators

bool Quaternion::operator==(const Quaternion& q2)
{
	return X == q2.X && Y == q2.Y && Z == q2.Z && W == q2.W;
}
bool Quaternion::operator!=(const Quaternion& q2)
{
	return X != q2.X || Y != q2.Y || Z != q2.Z || W != q2.W;
}

Quaternion Quaternion::operator+(const Quaternion& rhs) const
{
	return Quaternion(this->X + rhs.X, this->Y + rhs.Y,  this->Z + rhs.Z, this->W + rhs.W);
}
Quaternion& Quaternion::operator+=(const Quaternion& rhs)
{
	return  *this = *this + rhs;
}

Quaternion Quaternion::operator-(const Quaternion& rhs) const
{
	return Quaternion(X - rhs.X, Y - rhs.Y,  Z - rhs.Z, W - rhs.W);
}
Quaternion& Quaternion::operator-=(const Quaternion& rhs)
{
	return *this = *this - rhs;
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const
{
	float x = X;
	float y = Y;
	float z = Z;
	float w = W;

	float x2 = rhs.X;
	float y2 = rhs.Y;
	float z2 = rhs.Z;
	float w2 = rhs.W;

	float num = y * z2 - z * y2;
	float num2 = z * x2 - x * z2;
	float num3 = x * y2 - y * x2;
	float num4 = x * x2 + y * y2 + z * z2;

	Quaternion result;
	result.X = x * w2 + x2 * w + num;
	result.Y = y * w2 + y2 * w + num2;
	result.Z = z * w2 + z2 * w + num3;
	result.W = w * w2 - num4;
	return result;
}

Vector3 Quaternion::operator *(const Vector3& point) const
{
	Vector3 vector;

	float num =   this->X *  2.0f;
	float num2 =  this->Y * 2.0f;
	float num3 =  this->Z * 2.0f;
	float num4 =  this->X * num;
	float num5 =  this->Y * num2;
	float num6 =  this->Z * num3;
	float num7 =  this->X * num2;
	float num8 =  this->X * num3;
	float num9 =  this->Y * num3;
	float num10 = this->W * num;
	float num11 = this->W * num2;
	float num12 = this->W * num3;
	vector.X = (((1.0f - (num5 + num6)) * point.X) + ((num7 - num12) * point.Y)) + ((num8 + num11) * point.Z);
	vector.Y = (((num7 + num12) * point.X) + ((1.0f - (num4 + num6)) * point.Y)) + ((num9 - num10) * point.Z);
	vector.Z = (((num8 - num11) * point.X) + ((num9 + num10) * point.Y)) + ((1.0f - (num4 + num5)) * point.Z);

	return vector;
}


Quaternion& Quaternion::operator*=(const Quaternion& rhs)
{
	return *this = *this * rhs;
}

Quaternion Quaternion::operator/(const Quaternion& rhs) const
{
	float x = X;
	float y = Y;
	float z = Z;
	float w = W;
	float num = rhs.X * rhs.X + rhs.Y * rhs.Y + rhs.Z * rhs.Z + rhs.W * rhs.W;
	float num2 = 1 / num;
	float num3 = -rhs.X * num2;
	float num4 = -rhs.Y * num2;
	float num5 = -rhs.Z * num2;
	float num6 = rhs.W * num2;
	float num7 = y * num5 - z * num4;
	float num8 = z * num3 - x * num5;
	float num9 = x * num4 - y * num3;
	float num10 = x * num3 + y * num4 + z * num5;
	Quaternion result;
	result.X = x * num6 + num3 * w + num7;
	result.Y = y * num6 + num4 * w + num8;
	result.Z = z * num6 + num5 * w + num9;
	result.W = w * num6 - num10;
	return result;
}
Quaternion& Quaternion::operator/=(const Quaternion& rhs)
{
	return *this = *this / rhs;
}

Quaternion Quaternion::CreateFromAxisAngle( const Vector3& axis, float angle )
{
	float num = angle * 0.5f;
	float num2 = sinf(num);
	float w = cosf(num);
	Quaternion result;
	result.X = axis.X * num2;
	result.Y = axis.Y * num2;
	result.Z = axis.Z * num2;
	result.W = w;
	return result;
}

Quaternion Quaternion::CreateFromYawPitchRoll( float yaw, float pitch, float roll )
{
	float num = roll * 0.5f;
	float num2 = sinf(num);
	float num3 = cosf(num);
	float num4 = pitch * 0.5f;
	float num5 = sinf(num4);
	float num6 = cosf(num4);
	float num7 = yaw * 0.5f;
	float num8 = sinf(num7);
	float num9 = cosf(num7);
	Quaternion result;
	result.X = num9 * num5 * num3 + num8 * num6 * num2;
	result.Y = num8 * num6 * num3 - num9 * num5 * num2;
	result.Z = num9 * num6 * num2 - num8 * num5 * num3;
	result.W = num9 * num6 * num3 + num8 * num5 * num2;
	return result;
}
Quaternion Quaternion::CreateFromYawPitchRoll(const Vector3& rotation)
{
	return CreateFromYawPitchRoll(rotation.Y, rotation.X, rotation.Z);
}


#pragma endregion
