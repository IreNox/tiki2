#pragma once

#include "Vector3.h"

class Matrix3x3
{
public:
	float	M00, M10, M20,
			M01, M11, M21,
			M02, M12, M22;

	Matrix3x3(void);
	Matrix3x3(
		float m00, float m10, float m20,
		float m01, float m11, float m21,
		float m02, float m12, float m22
	);
	Matrix3x3(Vector3 v1, Vector3 v2, Vector3 v3);

	~Matrix3x3(void);

	Matrix3x3 Add(Matrix3x3 matrix);
	Matrix3x3 Substract(Matrix3x3 matrix);
	
	Matrix3x3 Multiply(Matrix3x3 matrix);	
	
	float Determinant();
	Matrix3x3 Adjugate();

	void Print();

	static Matrix3x3 Identity;
};