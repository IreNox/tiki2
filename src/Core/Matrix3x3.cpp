
#include "Core/Matrix2x2.h"
#include "Core/Matrix3x3.h"

#pragma region Vars
Matrix3x3 Matrix3x3::Identity = Matrix3x3(
	1, 0, 0,
	0, 1, 0,
	0, 0, 1
);
#pragma endregion

#pragma region Init
Matrix3x3::Matrix3x3(void)
{
}

Matrix3x3::Matrix3x3(
	float m00, float m10, float m20,
	float m01, float m11, float m21,
	float m02, float m12, float m22
) : M00(m00), M10(m10), M20(m20), 
	M01(m01), M11(m11), M21(m21), 
	M02(m02), M12(m12), M22(m22)
{	
}

Matrix3x3::Matrix3x3(Vector3 v1, Vector3 v2, Vector3 v3)
	: M00(v1.X), M10(v2.X), M20(v3.X),
	  M01(v1.Y), M11(v2.Y), M21(v3.Y), 
	  M02(v1.Z), M12(v2.Z), M22(v3.Z)
{	
}

Matrix3x3::~Matrix3x3(void)
{
}
#pragma endregion

#pragma region Add, Sub
Matrix3x3 Matrix3x3::Add(Matrix3x3 matrix)
{
	return Matrix3x3(
		(this->M00 + matrix.M00), (this->M10 + matrix.M10), (this->M20 + matrix.M20), 
		(this->M01 + matrix.M01), (this->M11 + matrix.M11), (this->M21 + matrix.M21), 
		(this->M02 + matrix.M02), (this->M12 + matrix.M12), (this->M22 + matrix.M22)
	);
}

Matrix3x3 Matrix3x3::Substract(Matrix3x3 matrix)
{
	return Matrix3x3(
		(this->M00 - matrix.M00), (this->M10 - matrix.M10), (this->M20 - matrix.M20),
		(this->M01 - matrix.M01), (this->M11 - matrix.M11), (this->M21 - matrix.M21),
		(this->M02 - matrix.M02), (this->M12 - matrix.M12), (this->M22 - matrix.M22)
	);
}
#pragma endregion

#pragma region Multiply
Matrix3x3 Matrix3x3::Multiply(Matrix3x3 matrix)
{
	Vector3 m1r0 = Vector3(this->M00, this->M10, this->M20);
	Vector3 m1r1 = Vector3(this->M01, this->M11, this->M21);
	Vector3 m1r2 = Vector3(this->M02, this->M12, this->M22);

	Vector3 m2r0 = Vector3(matrix.M00, matrix.M01, matrix.M02);
	Vector3 m2r1 = Vector3(matrix.M10, matrix.M11, matrix.M12);
	Vector3 m2r2 = Vector3(matrix.M20, matrix.M21, matrix.M22);
	
	return Matrix3x3(
		Vector3::Dot(m1r0, m2r0), Vector3::Dot(m1r0, m2r1), Vector3::Dot(m1r0, m2r2),
		Vector3::Dot(m1r1, m2r0), Vector3::Dot(m1r1, m2r1), Vector3::Dot(m1r1, m2r2),
		Vector3::Dot(m1r2, m2r0), Vector3::Dot(m1r2, m2r1), Vector3::Dot(m1r2, m2r2)
	);
}

float Matrix3x3::Determinant()
{
	return	(M00 * M11 * M22) +
			(M10 * M21 * M02) +
			(M20 * M01 * M12) -
			(M02 * M11 * M20) -
			(M12 * M21 * M00) -
			(M22 * M01 * M10);
}

Matrix3x3 Matrix3x3::Adjugate()
{
	return Matrix3x3(
		Matrix2x2(M11, M21, M12, M22).Determinant(), -Matrix2x2(M01, M21, M02, M22).Determinant(), Matrix2x2(M01, M11, M02, M12).Determinant(),
		-Matrix2x2(M10, M20, M12, M22).Determinant(), Matrix2x2(M00, M20, M02, M22).Determinant(), -Matrix2x2(M00, M10, M02, M12).Determinant(),
		Matrix2x2(M10, M20, M11, M21).Determinant(), -Matrix2x2(M00, M20, M01, M21).Determinant(), Matrix2x2(M00, M10, M01, M11).Determinant()
	);
}
#pragma endregion

#pragma region Translate, Rotate, Scale, Transform
Matrix3x3 Matrix3x3::Translate(float x, float y)
{
	return Matrix3x3(1, 0, 0,
					 0, 1, 0,
					 x, y, 1);
}

Matrix3x3 Matrix3x3::Scale(float x, float y)
{
	return Matrix3x3(x, 0, 0,
					 0, y, 0,
					 0, 0, 1);
}

Matrix3x3 Matrix3x3::Rotate(float radians)
{
	float s = sinf(radians);
	float c = cosf(radians);

	return Matrix3x3(c, s, 0,
					-s, c, 0,
					 0, 0, 1);
}

Matrix3x3 Matrix3x3::Rotate(const Vector2 &fwd, const Vector2& side)
{
	return Matrix3x3(fwd.X,  fwd.Y,  0,
					 side.X, side.Y, 0,
					 0,		 0,		 1);
}

void Matrix3x3::TransformVector(Vector2 point)
{
	float tempX = (M00 * point.X) + (M01 * point.Y) + M02;
	float tempY = (M10 * point.X) + (M11 * point.Y) + M12;

	point.X = tempX;
	point.Y = tempY;
}


#pragma endregion

#pragma region Operator overloads
Matrix3x3 Matrix3x3::operator* (const Matrix3x3& matrix)
{
	return this->Multiply(matrix);
}

#pragma endregion