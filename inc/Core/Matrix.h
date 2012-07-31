#pragma once

#include "Core/Vector4.h"


class Vector3;
class Quaternion;

class Matrix
{
public:

	#pragma region struct
	union 
	{
		struct
		{
			/// <summary>Value at row 1 column 1 of the matrix.</summary>
			float M11;
			/// <summary>Value at row 1 column 2 of the matrix.</summary>
			float M12;
			/// <summary>Value at row 1 column 3 of the matrix.</summary>
			float M13;
			/// <summary>Value at row 1 column 4 of the matrix.</summary>
			float M14;
			/// <summary>Value at row 2 column 1 of the matrix.</summary>
			float M21;
			/// <summary>Value at row 2 column 2 of the matrix.</summary>
			float M22;
			/// <summary>Value at row 2 column 3 of the matrix.</summary>
			float M23;
			/// <summary>Value at row 2 column 4 of the matrix.</summary>
			float M24;
			/// <summary>Value at row 3 column 1 of the matrix.</summary>
			float M31;
			/// <summary>Value at row 3 column 2 of the matrix.</summary>
			float M32;
			/// <summary>Value at row 3 column 3 of the matrix.</summary>
			float M33;
			/// <summary>Value at row 3 column 4 of the matrix.</summary>
			float M34;
			/// <summary>Value at row 4 column 1 of the matrix.</summary>
			float M41;
			/// <summary>Value at row 4 column 2 of the matrix.</summary>
			float M42;
			/// <summary>Value at row 4 column 3 of the matrix.</summary>
			float M43;
			/// <summary>Value at row 4 column 4 of the matrix.</summary>
			float M44;
		};
		float m[4][4];
		float n[16];
	};
	#pragma endregion struct
	

	Matrix(void);
	Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	);
	Matrix(float* data);
	Matrix(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4);

	~Matrix(void);

	static Matrix Add(const Matrix& left, const Matrix& right);
	static Matrix Subtract(const Matrix& left, const Matrix& right);

	static Matrix Invert(const Matrix& matrix);
	static Matrix Transpose(const Matrix& matrix);

	static Matrix Multiply(const Matrix& matrix1, const Matrix& matrix2 );
	static Matrix Multiply(const Matrix& matrix1, float scaleFactor);

	static Matrix Divide(const Matrix& matrix1, const Matrix& matrix2);
	static Matrix Divide(const Matrix& matrix1, float divider);

	float Determinant();

	static Matrix CreateTranslation(const Vector3& vector);
	static Matrix CreateTranslation(float x, float y, float z);
	static Matrix CreateScaleMatrix(const Vector3& vector);
	static Matrix CreateScaleMatrix(float x, float y, float z);
	static Matrix CreateRotationX(float radians);
	static Matrix CreateRotationY(float radians);
	static Matrix CreateRotationZ(float radians);
	static Matrix CreateFromAxisAngle(Vector3 axis, float angle);
	static Matrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
	static Matrix CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
	static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
	static Matrix CreateLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& cameraUpVector);
	static Matrix CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up);
	static Matrix CreateFromQuaternion(const Quaternion& quaternion);
	static Matrix CreateFromYawPitchRoll(float yaw, float pitch, float roll);


	bool operator== (const Matrix& matrix);
	bool operator!= (const Matrix& matrix);

	Matrix operator+ (const Matrix& matrix);
	Matrix operator- (const Matrix& matrix);

	Matrix operator* (const Matrix& matrix);
	Matrix operator* (float scaleFactor);

	Matrix operator/ (const Matrix& matrix);
	Matrix operator/ (float scaleFactor);

	Matrix& operator+= (const Matrix& matrix);
	Matrix& operator-= (const Matrix& matrix);
	Matrix& operator*= (const Matrix& matrix);
	Matrix& operator/= (const Matrix& matrix);

	static Matrix Identity;
};

