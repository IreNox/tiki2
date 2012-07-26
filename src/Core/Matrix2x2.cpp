
#include "Core/Matrix2x2.h"

#pragma region Vars
Matrix2x2 Matrix2x2::Identity = Matrix2x2(
	1, 0,
	0, 1
);
#pragma endregion

#pragma region Init
Matrix2x2::Matrix2x2(void)
{
}

Matrix2x2::Matrix2x2(
	float m00, float m10,
	float m01, float m11
) : M00(m00), M10(m10),
	M01(m01), M11(m11)
{	
}

Matrix2x2::Matrix2x2(Vector2 v1, Vector2 v2)
	: M00(v1.X), M10(v2.X),
	  M01(v1.Y), M11(v2.Y)
{	
}

Matrix2x2::~Matrix2x2(void)
{
}
#pragma endregion

#pragma region Add, Sub
Matrix2x2 Matrix2x2::Add(Matrix2x2 matrix)
{
	return Matrix2x2(
		(this->M00 + matrix.M00), (this->M10 + matrix.M10),
		(this->M01 + matrix.M01), (this->M11 + matrix.M11)
	);
}

Matrix2x2 Matrix2x2::Substract(Matrix2x2 matrix)
{
	return Matrix2x2(
		(this->M00 - matrix.M00), (this->M10 - matrix.M10),
		(this->M01 - matrix.M01), (this->M11 - matrix.M11)
	);
}
#pragma endregion

#pragma region Multiply
Matrix2x2 Matrix2x2::Multiply(Matrix2x2 matrix)
{
	Vector2 m1r0 = Vector2(this->M00, this->M10);
	Vector2 m1r1 = Vector2(this->M01, this->M11);

	Vector2 m2r0 = Vector2(matrix.M00, matrix.M01);
	Vector2 m2r1 = Vector2(matrix.M10, matrix.M11);
	
	return Matrix2x2(
		Vector2::Dot(m1r0,m2r0), Vector2::Dot(m1r0,m2r1),
		Vector2::Dot(m1r1,m1r1), Vector2::Dot(m1r1,m2r1)
	);
}

float Matrix2x2::Determinant()
{
	return	(M00 * M11) -
			(M01 * M10);
}

Matrix2x2 Matrix2x2::Adjugate()
{
	return Matrix2x2(
		M11, -M10,
		-M01, M00
	);
}

#pragma endregion