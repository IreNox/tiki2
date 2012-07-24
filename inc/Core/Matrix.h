#pragma once

#include "Core/Vector4.h"

class Vector3;

class Matrix
{
public:
	float	M00, M10, M20, M30,
			M01, M11, M21, M31,
			M02, M12, M22, M32,
			M03, M13, M23, M33;

	Matrix(void);
	Matrix(
		float m00, float m10, float m20, float m30,
		float m01, float m11, float m21, float m31,
		float m02, float m12, float m22, float m32,
		float m03, float m13, float m23, float m33
	);
	Matrix(float* data);
	Matrix(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4);

	~Matrix(void);

	Matrix Add(Matrix matrix);
	Matrix Substract(Matrix matrix);
	
	Matrix Multiply(float value);
	Matrix Multiply(Matrix matrix);
	
	float Determinant();
	Matrix Inverse();
	Matrix Adjugate();

	Matrix Transpose();

	Matrix operator* (const Matrix& multi);

	static Matrix Identity;

	//static Matrix CreateRotationX(float x);
	//static Matrix CreateRotationY(float y);
	//static Matrix CreateRotationZ(float z);

	//static Matrix CreateScale(const Vector3& scale);
	//static Matrix CreateTranslate(const Vector3& pos);
	//static Matrix CreateRotation(const Vector3& rotation);

	//static Matrix CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up);
	//static Matrix CreateLookAt(const Vector3& position, const Vector3& lookAt, const Vector3& upVector);
	//static Matrix CreatePerspectiveOffCenter(float left, float right, float bottom, float top, float nearPlaneDistance, float farPlaneDistance);
};

