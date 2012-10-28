
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

Vector3::Vector3(Vector2 v, float z)
	: X(v.X), Y(v.Y), Z(z)
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
#pragma endregion

#pragma region Static Methods
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

Vector3 Vector3::Lerp(const Vector3& value1, const Vector3& value2,const float amount)
{
	return Vector3(
		value1.X + (value2.X - value1.X) * amount,
		value1.Y + (value2.Y - value1.Y) * amount,
		value1.Z + (value2.Z - value1.Z) * amount);
}

Vector3 Vector3::Reflect(const Vector3& vector, const Vector3& normal)
{
	float num = vector.X * normal.X + vector.Y * normal.Y + vector.Z * normal.Z;

	return Vector3(
		vector.X - 2 * num * normal.X,
		vector.Y - 2 * num * normal.Y,
		vector.Z - 2 * num * normal.Z);
}
#pragma endregion

#pragma region Transform, Project, Unproject
Vector3 Vector3::Project(const Vector3& vec, float x, float y, float width, float height, 
						 float minZ, float maxZ, const Matrix& worldViewProjection )
{
	Vector3 vector = TransformCoordinate(vec, worldViewProjection);
	return Vector3(((1.0f + vector.X) * 0.5f * width) + x, 
				   ((1.0f - vector.Y) * 0.5f * height) + y, 
				   (vector.Z * (maxZ - minZ)) + minZ);
}

Vector3 Vector3::Unproject(const Vector3& vector, float x, float y, float width, float height, 
						   float minZ, float maxZ, const Matrix& worldViewProjection)
{
	Vector3 v;
	Matrix matrix =  Matrix::Invert(worldViewProjection);

	v.X = ( ( ( vector.X - x ) / width ) * 2.0f ) - 1.0f;
	v.Y = -( ( ( ( vector.Y - y ) / height ) * 2.0f ) - 1.0f );
	v.Z = ( vector.Z - minZ ) / ( maxZ - minZ );

	v = TransformCoordinate(v, matrix);
	return v;
}

Vector3 Vector3::TransformCoordinate(const Vector3& coord, const Matrix& transform)
{
	float xVal = (((coord.X * transform.M11) + (coord.Y * transform.M21)) + (coord.Z * transform.M31)) + transform.M41;
	float yVal = (((coord.X * transform.M12) + (coord.Y * transform.M22)) + (coord.Z * transform.M32)) + transform.M42;
	float zVal = (((coord.X * transform.M13) + (coord.Y * transform.M23)) + (coord.Z * transform.M33)) + transform.M43;
	float wVal = 1 / ((((coord.X * transform.M14) + (coord.Y * transform.M24)) + (coord.Z * transform.M34)) + transform.M44);

	return Vector3( xVal * wVal, yVal * wVal, zVal * wVal );
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

Vector3 Vector3::Forward = Vector3(0,0,-1);
Vector3 Vector3::Backward = Vector3(0,0,1);
#pragma endregion