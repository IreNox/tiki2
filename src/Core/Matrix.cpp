
#pragma comment(lib, "d3dx10.lib")

#include <math.h>

#include "Core/Matrix3x3.h"
#include "Core/Matrix.h"

#include "Core/Vector3.h"

#pragma region Vars
Matrix Matrix::Identity = Matrix(
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
);
#pragma endregion

#pragma region Init
Matrix::Matrix(void)
{
}

Matrix::Matrix(
	float m00, float m10, float m20, float m30,
	float m01, float m11, float m21, float m31,
	float m02, float m12, float m22, float m32,
	float m03, float m13, float m23, float m33
) : M00(m00), M10(m10), M20(m20), M30(m30), 
	M01(m01), M11(m11), M21(m21), M31(m31), 
	M02(m02), M12(m12), M22(m22), M32(m32), 
	M03(m03), M13(m13), M23(m23), M33(m33)
{	
}

Matrix::Matrix(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4)
	: M00(v1.X), M10(v2.X), M20(v3.X), M30(v4.X),
	  M01(v1.Y), M11(v2.Y), M21(v3.Y), M31(v4.Y),
	  M02(v1.Z), M12(v2.Z), M22(v3.Z), M32(v4.Z),
	  M03(v1.W), M13(v2.W), M23(v3.W), M33(v4.W)
{	
}

Matrix::Matrix(float* arr) 
  : M00(arr[0]),  M10(arr[1]),  M20(arr[2]),  M30(arr[3]), 
	M01(arr[4]),  M11(arr[5]),  M21(arr[6]),  M31(arr[7]), 
	M02(arr[8]),  M12(arr[9]),  M22(arr[10]), M32(arr[11]), 
	M03(arr[12]), M13(arr[13]), M23(arr[14]), M33(arr[15])
{	
}

Matrix::~Matrix(void)
{
}
#pragma endregion

#pragma region Add, Sub
Matrix Matrix::Add(Matrix matrix)
{
	return Matrix(
		(this->M00 + matrix.M00), (this->M10 + matrix.M10), (this->M20 + matrix.M20), (this->M30 + matrix.M30), 
		(this->M01 + matrix.M01), (this->M11 + matrix.M11), (this->M21 + matrix.M21), (this->M31 + matrix.M31), 
		(this->M02 + matrix.M02), (this->M12 + matrix.M12), (this->M22 + matrix.M22), (this->M32 + matrix.M32), 
		(this->M03 + matrix.M03), (this->M13 + matrix.M13), (this->M23 + matrix.M23), (this->M33 + matrix.M33)
	);
}

Matrix Matrix::Substract(Matrix matrix)
{
	return Matrix(
		(this->M00 - matrix.M00), (this->M10 - matrix.M10), (this->M20 - matrix.M20), (this->M30 - matrix.M30), 
		(this->M01 - matrix.M01), (this->M11 - matrix.M11), (this->M21 - matrix.M21), (this->M31 - matrix.M31), 
		(this->M02 - matrix.M02), (this->M12 - matrix.M12), (this->M22 - matrix.M22), (this->M32 - matrix.M32), 
		(this->M03 - matrix.M03), (this->M13 - matrix.M13), (this->M23 - matrix.M23), (this->M33 - matrix.M33)
	);
}
#pragma endregion

#pragma region Multiply
Matrix Matrix::Multiply(float v)
{
	return Matrix(
		M00 * v, M10 * v, M20 * v, M30 * v, 
		M01 * v, M11 * v, M21 * v, M31 * v, 
		M02 * v, M12 * v, M22 * v, M32 * v, 
		M03 * v, M13 * v, M23 * v, M33 * v
	);
}

Matrix Matrix::Multiply(Matrix matrix)
{
	Vector4 m1r0 = Vector4(this->M00, this->M10, this->M20, this->M30);
	Vector4 m1r1 = Vector4(this->M01, this->M11, this->M21, this->M31);
	Vector4 m1r2 = Vector4(this->M02, this->M12, this->M22, this->M32);
	Vector4 m1r3 = Vector4(this->M03, this->M13, this->M23, this->M33);

	Vector4 m2r0 = Vector4(matrix.M00, matrix.M01, matrix.M02, matrix.M03);
	Vector4 m2r1 = Vector4(matrix.M10, matrix.M11, matrix.M12, matrix.M13);
	Vector4 m2r2 = Vector4(matrix.M20, matrix.M21, matrix.M22, matrix.M23);
	Vector4 m2r3 = Vector4(matrix.M30, matrix.M31, matrix.M32, matrix.M33);
	
	return Matrix(
		m1r0.Dot(m2r0), m1r0.Dot(m2r1), m1r0.Dot(m2r2), m1r0.Dot(m2r3), 
		m1r1.Dot(m2r0), m1r1.Dot(m2r1), m1r1.Dot(m2r2), m1r1.Dot(m2r3), 
		m1r2.Dot(m2r0), m1r2.Dot(m2r1), m1r2.Dot(m2r2), m1r2.Dot(m2r3), 
		m1r3.Dot(m2r0), m1r3.Dot(m2r1), m1r3.Dot(m2r2), m1r3.Dot(m2r3)
	);
}
#pragma endregion

#pragma region Determinant, Inverse, Adjugate
float Matrix::Determinant()
{
	Vector3 r1c0 = Vector3(this->M01, this->M02, this->M03);
	Vector3 r1c1 = Vector3(this->M11, this->M12, this->M13);
	Vector3 r1c2 = Vector3(this->M21, this->M22, this->M23);
	Vector3 r1c3 = Vector3(this->M31, this->M32, this->M33);

	return	M00 * Matrix3x3(r1c1, r1c2, r1c3).Determinant() +
			M10 * Matrix3x3(r1c0, r1c2, r1c3).Determinant() -
			M20 * Matrix3x3(r1c0, r1c1, r1c3).Determinant() +
			M30 * Matrix3x3(r1c0, r1c1, r1c2).Determinant();
}

Matrix Matrix::Inverse()
{
	float det = this->Determinant();
	if (det == 0)
		throw "Fail";

	float reciDet = 1 / det;
	return this->Adjugate().Multiply(
		reciDet
	);
}

Matrix Matrix::Adjugate()
{
	return Matrix(
		Matrix3x3(M11, M12, M13, M21, M22, M23, M31, M32, M33).Determinant(),	//M00
		-Matrix3x3(M10, M12, M13, M20, M22, M23, M30, M32, M33).Determinant(),	//M10
		Matrix3x3(M10, M11, M13, M20, M21, M23, M30, M31, M33).Determinant(),	//M20
		-Matrix3x3(M10, M11, M12, M20, M21, M22, M30, M31, M32).Determinant(),	//M30
		-Matrix3x3(M01, M02, M03, M21, M22, M23, M31, M32, M33).Determinant(),	//M01
		Matrix3x3(M00, M02, M03, M20, M22, M23, M30, M32, M33).Determinant(),	//M11
		-Matrix3x3(M00, M01, M03, M20, M21, M23, M30, M31, M33).Determinant(),	//M21
		Matrix3x3(M00, M01, M02, M20, M21, M22, M30, M31, M32).Determinant(),	//M31
		Matrix3x3(M01, M02, M03, M11, M12, M13, M31, M32, M33).Determinant(),	//M02
		-Matrix3x3(M00, M02, M03, M10, M12, M13, M30, M32, M33).Determinant(),	//M12
		Matrix3x3(M00, M01, M03, M10, M11, M13, M30, M31, M33).Determinant(),	//M22
		-Matrix3x3(M00, M01, M02, M10, M11, M12, M30, M31, M32).Determinant(),	//M32
		-Matrix3x3(M01, M02, M03, M11, M12, M13, M21, M22, M23).Determinant(),	//M03
		Matrix3x3(M00, M02, M03, M10, M12, M13, M20, M22, M23).Determinant(),	//M13
		-Matrix3x3(M00, M01, M03, M10, M11, M13, M20, M21, M23).Determinant(),	//M23
		Matrix3x3(M00, M01, M02, M10, M11, M12, M20, M21, M22).Determinant()	//M33
	);
}
#pragma endregion

#pragma region Member - Transpose
Matrix Matrix::Transpose()
{
	return Matrix(
		M00, M01, M02, M03, 
		M10, M11, M12, M13, 
		M20, M21, M22, M23, 
		M30, M31, M32, M33
	);
}
#pragma endregion

#pragma region Operators
Matrix Matrix::operator*(const Matrix& multi)
{
	return this->Multiply(multi);
}
#pragma endregion

//#pragma region Static
//Matrix Matrix::CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up)
//{
//	Matrix matrix;
//
//	Vector3 vector = -forward.Normalize();
//	Vector3 vector2 = Vector3::Cross(up, vector).Normalize();
//	Vector3 vector3 = Vector3::Cross(vector, vector2);
//
//	matrix.M00 = vector2.X;
//	matrix.M01 = vector2.Y;
//	matrix.M02 = vector2.Z;
//	matrix.M03 = 0.0f;
//	matrix.M10 = vector3.X;
//	matrix.M11 = vector3.Y;
//	matrix.M12 = vector3.Z;
//	matrix.M13 = 0.0f;
//	matrix.M20 = vector.X;
//	matrix.M21 = vector.Y;
//	matrix.M22 = vector.Z;
//	matrix.M23 = 0.0f;
//	matrix.M30 = position.X;
//	matrix.M31 = position.Y;
//	matrix.M32 = position.Z;
//	matrix.M33 = 1.0f;
//
//	return matrix;
//}
//
//Matrix Matrix::CreateLookAt(const Vector3& pos, const Vector3& lookAt, const Vector3& up)
//{
//	Matrix matrix;
//
//	Vector3 vector = (pos - lookAt).Normalize();
//	Vector3 vector2 = Vector3::Cross(up, vector).Normalize();
//	Vector3 vector3 = Vector3::Cross(vector, vector2);
//
//	matrix.M00 = vector2.X;
//	matrix.M01 = vector3.X;
//	matrix.M02 = vector.X;
//	matrix.M03 = 0.0f;
//	matrix.M10 = vector2.Y;
//	matrix.M11 = vector3.Y;
//	matrix.M12 = vector.Y;
//	matrix.M13 = 0.0f;
//	matrix.M20 = vector2.Z;
//	matrix.M23 = vector3.Z;
//	matrix.M22 = vector.Z;
//	matrix.M23 = 0.0f;
//	matrix.M30 = -Vector3::Dot(vector2, pos);
//	matrix.M31 = -Vector3::Dot(vector3, pos);
//	matrix.M32 = -Vector3::Dot(vector, pos);
//	matrix.M33 = 1.0f;
//
//	return matrix;
//}
//
//Matrix Matrix::CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance)
//{
//	Matrix matrix;
//	
//	matrix.M00 = (2.0f * nearPlaneDistance) / (right - left);
//	matrix.M01 = matrix.M02 = matrix.M03 = 0.0f;
//	matrix.M11 = (2.0f * nearPlaneDistance) / (top - bottom);
//	matrix.M10 = matrix.M12 = matrix.M13 = 0.0f;
//	matrix.M20 = (left + right) / (right - left);
//	matrix.M21 = (top + bottom) / (top - bottom);
//	matrix.M22 = farPlaneDistance / (nearPlaneDistance - farPlaneDistance);
//	matrix.M23 = -1.0f;
//	matrix.M32 = (nearPlaneDistance * farPlaneDistance) / (nearPlaneDistance - farPlaneDistance);
//	matrix.M30 = matrix.M31 = matrix.M33 = 0.0f;
//
//	return matrix;
//}
//
//Matrix Matrix::CreateTranslate(const Vector3& pos)
//{
//	return Matrix(
//		1, 0, 0, pos.X,
//		0, 1, 0, pos.Y,
//		0, 0, 1, pos.Z,
//		0, 0, 0, 1
//	);
//}
//
//Matrix Matrix::CreateScale(const Vector3& s)
//{
//	return Matrix(
//		s.X, 0, 0, 0,
//		0, s.Y, 0, 0,
//		0, 0, s.Z, 0,
//		0, 0, 0, 1
//	);
//}
//
//Matrix Matrix::CreateRotationX(float x)
//{
//	float s = sinf(x);
//	float c = cosf(x);
//
//	return Matrix(
//		1, 0, 0, 0,
//		0, c, -s, 0,
//		0, s, c, 0,
//		0, 0, 0, 1
//	);
//}
//
//Matrix Matrix::CreateRotationY(float y)
//{
//	float s = sinf(y);
//	float c = cosf(y);
//
//	return Matrix(
//		c, 0, s, 0,
//		0, 1, 0, 0,
//		-s, 0, c, 0,
//		0, 0, 0, 1
//	);
//}
//
//Matrix Matrix::CreateRotationZ(float z)
//{
//	float s = sinf(z);
//	float c = cosf(z);
//
//	return Matrix(
//		c, s, 0, 0,
//		-s, c, 0, 0,
//		0, 0, 1, 0,
//		0, 0, 0, 1
//	);
//}
//
//Matrix Matrix::CreateRotation(const Vector3& rot)
//{
//	return CreateRotationX(rot.X) *
//		   CreateRotationY(rot.Y) *
//		   CreateRotationZ(rot.Z);
//}
//#pragma endregion