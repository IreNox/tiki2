#pragma once

#include "Core/Vector4.h"

class Vector3;
class Quaternion;

class Matrix
{
public:

	#pragma region Vars
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
	#pragma endregion	

	inline Matrix(void):
		M11(0.0f), M12(0.0f), M13(0.0f), M14(0.0f), 
		M21(0.0f), M22(0.0f), M23(0.0f), M24(0.0f), 
		M31(0.0f), M32(0.0f), M33(0.0f), M34(0.0f), 
		M41(0.0f), M42(0.0f), M43(0.0f), M44(0.0f)
	{
	}

	inline Matrix(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	): 
		M11(m11), M12(m12), M13(m13), M14(m14), 
		M21(m21), M22(m22), M23(m23), M24(m24), 
		M31(m31), M32(m32), M33(m33), M34(m34), 
		M41(m41), M42(m42), M43(m43), M44(m44)
	{	
	}

	inline Matrix(float* arr)
		: 
		M11(arr[0]), M12(arr[1]), M13(arr[2]), M14(arr[3]),
		M21(arr[4]), M22(arr[5]), M23(arr[6]), M24(arr[7]),
		M31(arr[8]), M32(arr[9]), M33(arr[10]), M34(arr[11]),
		M41(arr[12]), M42(arr[13]), M43(arr[14]), M44(arr[15])
	{

	}
	Matrix(Vector4 v1, Vector4 v2, Vector4 v3, Vector4 v4);

	inline ~Matrix(void) {}


	static inline Matrix Add(const Matrix& left, const Matrix& right)
	{
		return Matrix(
			left.M11 + right.M11,
			left.M12 + right.M12,
			left.M13 + right.M13,
			left.M14 + right.M14,
			left.M21 + right.M21,
			left.M22 + right.M22,
			left.M23 + right.M23,
			left.M24 + right.M24,
			left.M31 + right.M31,
			left.M32 + right.M32,
			left.M33 + right.M33,
			left.M34 + right.M34,
			left.M41 + right.M41,
			left.M42 + right.M42,
			left.M43 + right.M43,
			left.M44 + right.M44);
	}
	static inline Matrix Subtract(const Matrix& left, const Matrix& right)
	{
		return Matrix(
			left.M11 - right.M11,
			left.M12 - right.M12,
			left.M13 - right.M13,
			left.M14 - right.M14,
			left.M21 - right.M21,
			left.M22 - right.M22,
			left.M23 - right.M23,
			left.M24 - right.M24,
			left.M31 - right.M31,
			left.M32 - right.M32,
			left.M33 - right.M33,
			left.M34 - right.M34,
			left.M41 - right.M41,
			left.M42 - right.M42,
			left.M43 - right.M43,
			left.M44 - right.M44);
	}

	static inline Matrix Invert(const Matrix& matrix)
	{
		float m = matrix.M11;
		float m2 = matrix.M12;
		float m3 = matrix.M13;
		float m4 = matrix.M14;
		float m5 = matrix.M21;
		float m6 = matrix.M22;
		float m7 = matrix.M23;
		float m8 = matrix.M24;
		float m9 = matrix.M31;
		float m10 = matrix.M32;
		float m11 = matrix.M33;
		float m12 = matrix.M34;
		float m13 = matrix.M41;
		float m14 = matrix.M42;
		float m15 = matrix.M43;
		float m16 = matrix.M44;

		float num = m11 * m16 - m12 * m15;
		float num2 = m10 * m16 - m12 * m14;
		float num3 = m10 * m15 - m11 * m14;
		float num4 = m9 * m16 - m12 * m13;
		float num5 = m9 * m15 - m11 * m13;
		float num6 = m9 * m14 - m10 * m13;
		float num7 = m6 * num - m7 * num2 + m8 * num3;
		float num8 = -(m5 * num - m7 * num4 + m8 * num5);
		float num9 = m5 * num2 - m6 * num4 + m8 * num6;
		float num10 = -(m5 * num3 - m6 * num5 + m7 * num6);
		float num11 = 1 / (m * num7 + m2 * num8 + m3 * num9 + m4 * num10);

		Matrix result;
		result.M11 = num7 * num11;
		result.M21 = num8 * num11;
		result.M31 = num9 * num11;
		result.M41 = num10 * num11;
		result.M12 = -(m2 * num - m3 * num2 + m4 * num3) * num11;
		result.M22 = (m * num - m3 * num4 + m4 * num5) * num11;
		result.M32 = -(m * num2 - m2 * num4 + m4 * num6) * num11;
		result.M42 = (m * num3 - m2 * num5 + m3 * num6) * num11;

		float num12 = m7 * m16 - m8 * m15;
		float num13 = m6 * m16 - m8 * m14;
		float num14 = m6 * m15 - m7 * m14;
		float num15 = m5 * m16 - m8 * m13;
		float num16 = m5 * m15 - m7 * m13;
		float num17 = m5 * m14 - m6 * m13;

		result.M13 = (m2 * num12 - m3 * num13 + m4 * num14) * num11;
		result.M23 = -(m * num12 - m3 * num15 + m4 * num16) * num11;
		result.M33 = (m * num13 - m2 * num15 + m4 * num17) * num11;
		result.M43 = -(m * num14 - m2 * num16 + m3 * num17) * num11;

		float num18 = m7 * m12 - m8 * m11;
		float num19 = m6 * m12 - m8 * m10;
		float num20 = m6 * m11 - m7 * m10;
		float num21 = m5 * m12 - m8 * m9;
		float num22 = m5 * m11 - m7 * m9;
		float num23 = m5 * m10 - m6 * m9;

		result.M14 = -(m2 * num18 - m3 * num19 + m4 * num20) * num11;
		result.M24 = (m * num18 - m3 * num21 + m4 * num22) * num11;
		result.M34 = -(m * num19 - m2 * num21 + m4 * num23) * num11;
		result.M44 = (m * num20 - m2 * num22 + m3 * num23) * num11;

		return result;
	}
	inline Matrix Invert()
	{
		return Invert(*this);
	}

	static inline Matrix Transpose(const Matrix& matrix)
	{
		return Matrix(
			matrix.M11,
			matrix.M21,
			matrix.M31,
			matrix.M41,
			matrix.M12,
			matrix.M22,
			matrix.M32,
			matrix.M42,
			matrix.M13,
			matrix.M23,
			matrix.M33,
			matrix.M43,
			matrix.M14,
			matrix.M24,
			matrix.M34,
			matrix.M44);
	}
	inline Matrix Transpose()
	{
		return Matrix(		
			M11,
			M21,
			M31,
			M41,
			M12,
			M22,
			M32,
			M42,
			M13,
			M23,
			M33,
			M43,
			M14,
			M24,
			M34,
			M44);
	}

	static inline Matrix Multiply(const Matrix& matrix1, const Matrix& matrix2 )
	{
		return Matrix(
			matrix1.M11 * matrix2.M11 + matrix1.M12 * matrix2.M21 + matrix1.M13 * matrix2.M31 + matrix1.M14 * matrix2.M41,
			matrix1.M11 * matrix2.M12 + matrix1.M12 * matrix2.M22 + matrix1.M13 * matrix2.M32 + matrix1.M14 * matrix2.M42,
			matrix1.M11 * matrix2.M13 + matrix1.M12 * matrix2.M23 + matrix1.M13 * matrix2.M33 + matrix1.M14 * matrix2.M43,
			matrix1.M11 * matrix2.M14 + matrix1.M12 * matrix2.M24 + matrix1.M13 * matrix2.M34 + matrix1.M14 * matrix2.M44,
			matrix1.M21 * matrix2.M11 + matrix1.M22 * matrix2.M21 + matrix1.M23 * matrix2.M31 + matrix1.M24 * matrix2.M41,
			matrix1.M21 * matrix2.M12 + matrix1.M22 * matrix2.M22 + matrix1.M23 * matrix2.M32 + matrix1.M24 * matrix2.M42,
			matrix1.M21 * matrix2.M13 + matrix1.M22 * matrix2.M23 + matrix1.M23 * matrix2.M33 + matrix1.M24 * matrix2.M43,
			matrix1.M21 * matrix2.M14 + matrix1.M22 * matrix2.M24 + matrix1.M23 * matrix2.M34 + matrix1.M24 * matrix2.M44,
			matrix1.M31 * matrix2.M11 + matrix1.M32 * matrix2.M21 + matrix1.M33 * matrix2.M31 + matrix1.M34 * matrix2.M41,
			matrix1.M31 * matrix2.M12 + matrix1.M32 * matrix2.M22 + matrix1.M33 * matrix2.M32 + matrix1.M34 * matrix2.M42,
			matrix1.M31 * matrix2.M13 + matrix1.M32 * matrix2.M23 + matrix1.M33 * matrix2.M33 + matrix1.M34 * matrix2.M43,
			matrix1.M31 * matrix2.M14 + matrix1.M32 * matrix2.M24 + matrix1.M33 * matrix2.M34 + matrix1.M34 * matrix2.M44,
			matrix1.M41 * matrix2.M11 + matrix1.M42 * matrix2.M21 + matrix1.M43 * matrix2.M31 + matrix1.M44 * matrix2.M41,
			matrix1.M41 * matrix2.M12 + matrix1.M42 * matrix2.M22 + matrix1.M43 * matrix2.M32 + matrix1.M44 * matrix2.M42,
			matrix1.M41 * matrix2.M13 + matrix1.M42 * matrix2.M23 + matrix1.M43 * matrix2.M33 + matrix1.M44 * matrix2.M43,
			matrix1.M41 * matrix2.M14 + matrix1.M42 * matrix2.M24 + matrix1.M43 * matrix2.M34 + matrix1.M44 * matrix2.M44);
	}
	static inline Matrix Multiply(const Matrix& matrix1, float scaleFactor)
	{
		return Matrix(
			matrix1.M11 * scaleFactor,
			matrix1.M12 * scaleFactor,
			matrix1.M13 * scaleFactor,
			matrix1.M14 * scaleFactor,
			matrix1.M21 * scaleFactor,
			matrix1.M22 * scaleFactor,
			matrix1.M23 * scaleFactor,
			matrix1.M24 * scaleFactor,
			matrix1.M31 * scaleFactor,
			matrix1.M32 * scaleFactor,
			matrix1.M33 * scaleFactor,
			matrix1.M34 * scaleFactor,
			matrix1.M41 * scaleFactor,
			matrix1.M42 * scaleFactor,
			matrix1.M43 * scaleFactor,
			matrix1.M44 * scaleFactor);
	}

	static inline Matrix Divide(const Matrix& matrix1, const Matrix& matrix2)
	{
		return Matrix(
			matrix1.M11 / matrix2.M11,
			matrix1.M12 / matrix2.M12,
			matrix1.M13 / matrix2.M13,
			matrix1.M14 / matrix2.M14,
			matrix1.M21 / matrix2.M21,
			matrix1.M22 / matrix2.M22,
			matrix1.M23 / matrix2.M23,
			matrix1.M24 / matrix2.M24,
			matrix1.M31 / matrix2.M31,
			matrix1.M32 / matrix2.M32,
			matrix1.M33 / matrix2.M33,
			matrix1.M34 / matrix2.M34,
			matrix1.M41 / matrix2.M41,
			matrix1.M42 / matrix2.M42,
			matrix1.M43 / matrix2.M43,
			matrix1.M44 / matrix2.M44);
	}
	static inline Matrix Divide(const Matrix& matrix1, float divider)
	{
		float num = 1 / divider;
		return Matrix(
			matrix1.M11 * num,
			matrix1.M12 * num,
			matrix1.M13 * num,
			matrix1.M14 * num,
			matrix1.M21 * num,
			matrix1.M22 * num,
			matrix1.M23 * num,
			matrix1.M24 * num,
			matrix1.M31 * num,
			matrix1.M32 * num,
			matrix1.M33 * num,
			matrix1.M34 * num,
			matrix1.M41 * num,
			matrix1.M42 * num,
			matrix1.M43 * num,
			matrix1.M44 * num);
	}

	float inline Determinant()
	{
		float temp1 = (M33 * M44) - (M34 * M43);
		float temp2 = (M32 * M44) - (M34 * M42);
		float temp3 = (M32 * M43) - (M33 * M42);
		float temp4 = (M31 * M44) - (M34 * M41);
		float temp5 = (M31 * M43) - (M33 * M41);
		float temp6 = (M31 * M42) - (M32 * M41);

		return ((((M11 * (((M22 * temp1) - (M23 * temp2)) + (M24 * temp3))) - (M12 * (((M21 * temp1) - 
			(M23 * temp4)) + (M24 * temp5)))) + (M13 * (((M21 * temp2) - (M22 * temp4)) + (M24 * temp6)))) - 
			(M14 * (((M21 * temp3) - (M22 * temp5)) + (M23 * temp6))));
	}

	static Matrix CreateTranslation(const Vector3& vector);

	static Matrix CreateTranslation(float x, float y, float z);
	static Matrix CreateScaleMatrix(float a);
	static Matrix CreateScaleMatrix(const Vector3& vector);
	static Matrix CreateScaleMatrix(float x, float y, float z);
	static Matrix CreateRotationX(float radians);
	static Matrix CreateRotationY(float radians);
	static Matrix CreateRotationZ(float radians);
	static Matrix CreateFromAxisAngle(Vector3 axis, float angle);
	static Matrix CreatePerspectiveFieldOfView(float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
	static Matrix CreatePerspective(float width, float height, float nearPlaneDistance, float farPlaneDistance);
	static Matrix CreateOrthographic(float width, float height, float zNearPlane, float zFarPlane);
	static Matrix CreateOrthographicOffCenter(float width, float height, float zNearPlane, float zFarPlane);
	static Matrix CreateLookAt(const Vector3& cameraPosition, const Vector3& cameraTarget, const Vector3& cameraUpVector);
	static Matrix CreateWorld(const Vector3& position, const Vector3& forward, const Vector3& up);
	static Matrix CreateFromQuaternion(const Quaternion& quaternion);



	/// <summary>Creates a new rotation matrix from a specified yaw, pitch, and roll.</summary>
	/// <param name="yaw">Angle of rotation, in radians, around the y-axis.</param>
	/// <param name="pitch">Angle of rotation, in radians, around the x-axis.</param>
	/// <param name="roll">Angle of rotation, in radians, around the z-axis.</param>
	static Matrix CreateFromYawPitchRollRadians(float yaw, float pitch, float roll);
	static Matrix CreateFromYawPitchRollRadians(const Vector3& rot);
	//static Matrix CreateFromYawPitchRollDegrees(float yaw, float pitch, float roll);
	//static Matrix CreateFromYawPitchRollDegrees(const Vector3& rot);
	//static Matrix CreateFromXYZDegrees(const Vector3& rot);


	inline bool operator== (const Matrix& value)
	{
		return ( M11 == value.M11 && M12 == value.M12 && M13 == value.M13 && M14 == value.M14 &&
			M21 == value.M21 && M22 == value.M22 && M23 == value.M23 && M24 == value.M24 &&
			M31 == value.M31 && M32 == value.M32 && M33 == value.M33 && M34 == value.M34 &&
			M41 == value.M41 && M42 == value.M42 && M43 == value.M43 && M44 == value.M44 );
	}
	bool operator!= (const Matrix& matrix)
	{
		return	!(*this == matrix);
	}

	inline Matrix operator+ (const Matrix& matrix)
	{
		return Matrix(
			this->M11 + matrix.M11,
			this->M12 + matrix.M12,
			this->M13 + matrix.M13,
			this->M14 + matrix.M14,
			this->M21 + matrix.M21,
			this->M22 + matrix.M22,
			this->M23 + matrix.M23,
			this->M24 + matrix.M24,
			this->M31 + matrix.M31,
			this->M32 + matrix.M32,
			this->M33 + matrix.M33,
			this->M34 + matrix.M34,
			this->M41 + matrix.M41,
			this->M42 + matrix.M42,
			this->M43 + matrix.M43,
			this->M44 + matrix.M44);
	}
	inline Matrix operator- (const Matrix& matrix)
	{
		return Matrix(
			this->M11 - matrix.M11,
			this->M12 - matrix.M12,
			this->M13 - matrix.M13,
			this->M14 - matrix.M14,
			this->M21 - matrix.M21,
			this->M22 - matrix.M22,
			this->M23 - matrix.M23,
			this->M24 - matrix.M24,
			this->M31 - matrix.M31,
			this->M32 - matrix.M32,
			this->M33 - matrix.M33,
			this->M34 - matrix.M34,
			this->M41 - matrix.M41,
			this->M42 - matrix.M42,
			this->M43 - matrix.M43,
			this->M44 - matrix.M44);
	}

	inline Matrix operator* (const Matrix& matrix) const
	{
		return Matrix(
			this->M11 * matrix.M11 + this->M12 * matrix.M21 + this->M13 * matrix.M31 + this->M14 * matrix.M41,
			this->M11 * matrix.M12 + this->M12 * matrix.M22 + this->M13 * matrix.M32 + this->M14 * matrix.M42,
			this->M11 * matrix.M13 + this->M12 * matrix.M23 + this->M13 * matrix.M33 + this->M14 * matrix.M43,
			this->M11 * matrix.M14 + this->M12 * matrix.M24 + this->M13 * matrix.M34 + this->M14 * matrix.M44,
			this->M21 * matrix.M11 + this->M22 * matrix.M21 + this->M23 * matrix.M31 + this->M24 * matrix.M41,
			this->M21 * matrix.M12 + this->M22 * matrix.M22 + this->M23 * matrix.M32 + this->M24 * matrix.M42,
			this->M21 * matrix.M13 + this->M22 * matrix.M23 + this->M23 * matrix.M33 + this->M24 * matrix.M43,
			this->M21 * matrix.M14 + this->M22 * matrix.M24 + this->M23 * matrix.M34 + this->M24 * matrix.M44,
			this->M31 * matrix.M11 + this->M32 * matrix.M21 + this->M33 * matrix.M31 + this->M34 * matrix.M41,
			this->M31 * matrix.M12 + this->M32 * matrix.M22 + this->M33 * matrix.M32 + this->M34 * matrix.M42,
			this->M31 * matrix.M13 + this->M32 * matrix.M23 + this->M33 * matrix.M33 + this->M34 * matrix.M43,
			this->M31 * matrix.M14 + this->M32 * matrix.M24 + this->M33 * matrix.M34 + this->M34 * matrix.M44,
			this->M41 * matrix.M11 + this->M42 * matrix.M21 + this->M43 * matrix.M31 + this->M44 * matrix.M41,
			this->M41 * matrix.M12 + this->M42 * matrix.M22 + this->M43 * matrix.M32 + this->M44 * matrix.M42,
			this->M41 * matrix.M13 + this->M42 * matrix.M23 + this->M43 * matrix.M33 + this->M44 * matrix.M43,
			this->M41 * matrix.M14 + this->M42 * matrix.M24 + this->M43 * matrix.M34 + this->M44 * matrix.M44);
	}
	inline Matrix operator* (float scaleFactor)
	{
		return Matrix(
			this->M11 * scaleFactor,
			this->M12 * scaleFactor,
			this->M13 * scaleFactor,
			this->M14 * scaleFactor,
			this->M21 * scaleFactor,
			this->M22 * scaleFactor,
			this->M23 * scaleFactor,
			this->M24 * scaleFactor,
			this->M31 * scaleFactor,
			this->M32 * scaleFactor,
			this->M33 * scaleFactor,
			this->M34 * scaleFactor,
			this->M41 * scaleFactor,
			this->M42 * scaleFactor,
			this->M43 * scaleFactor,
			this->M44 * scaleFactor);
	}

	inline Matrix operator/ (const Matrix& matrix)
	{
		return Matrix(
			this->M11 / matrix.M11,
			this->M12 / matrix.M12,
			this->M13 / matrix.M13,
			this->M14 / matrix.M14,
			this->M21 / matrix.M21,
			this->M22 / matrix.M22,
			this->M23 / matrix.M23,
			this->M24 / matrix.M24,
			this->M31 / matrix.M31,
			this->M32 / matrix.M32,
			this->M33 / matrix.M33,
			this->M34 / matrix.M34,
			this->M41 / matrix.M41,
			this->M42 / matrix.M42,
			this->M43 / matrix.M43,
			this->M44 / matrix.M44);
	}
	inline Matrix operator/ (float scaleFactor)
	{
		float num = 1 / scaleFactor;
		return Matrix(
			this->M11 * num,
			this->M12 * num,
			this->M13 * num,
			this->M14 * num,
			this->M21 * num,
			this->M22 * num,
			this->M23 * num,
			this->M24 * num,
			this->M31 * num,
			this->M32 * num,
			this->M33 * num,
			this->M34 * num,
			this->M41 * num,
			this->M42 * num,
			this->M43 * num,
			this->M44 * num);
	}

	inline Matrix& operator+= (const Matrix& matrix)
	{
		return *this = *this + matrix;
	}

	inline Matrix& operator-= (const Matrix& matrix)
	{
		return *this = *this - matrix;
	}

	inline Matrix& operator*= (const Matrix& matrix)
	{
		return *this = *this * matrix;
	}

	inline Matrix& operator/= (const Matrix& matrix)
	{
		return *this = *this / matrix;
	}

	static Matrix Identity;
};

