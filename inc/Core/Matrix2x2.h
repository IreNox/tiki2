#pragma once

#include "Vector2.h"

class Matrix2x2
{
public:
	float	M00, M10,
			M01, M11;

	Matrix2x2(void);
	Matrix2x2(
		float m00, float m10,
		float m01, float m11
	);
	Matrix2x2(Vector2 v1, Vector2 v2);

	~Matrix2x2(void);

	Matrix2x2 Add(Matrix2x2 matrix);
	Matrix2x2 Substract(Matrix2x2 matrix);
	
	Matrix2x2 Multiply(Matrix2x2 matrix);	
	
	float Determinant();
	Matrix2x2 Adjugate();

	void Print();

	static Matrix2x2 Identity;
};