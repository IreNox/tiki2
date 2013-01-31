#pragma once

#include "Core/TypeDef.h"
#include "Core/Vector3.h"

class Quaternion
{
public:

	union
	{
		struct  
		{
			float X;
			float Y;
			float Z;
			float W;
		};
		float arr[4];
	};
	Quaternion(void);
	Quaternion(float x, float y, float z, float w);
	~Quaternion();

	float LengthSquared();
	float Length();

	void Normalize();
	static Quaternion Normalize(const Quaternion& quat);

	void Conjugate();
	static Quaternion Conjugate(const Quaternion& quat);

	void Inverse();
	static Quaternion Inverse(const Quaternion& quat);

	void Negate();
	static Quaternion Negate(const Quaternion& quat);

	static float Dot(const Quaternion& quaternion1, const Quaternion& quaternion2);
	static Quaternion Concatenate(const Quaternion& quaternion1, const Quaternion& quaternion2);

	static Quaternion Slerp(const Quaternion& from, const Quaternion& to, float amount);
	static Quaternion Lerp(const Quaternion& quaternion1, const Quaternion& quaternion2, float amount);

	static Quaternion CreateFromAxisAngle(const Vector3& axis, float angle);

	inline static Quaternion CreateFromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
	{
		Quaternion quaternion;

		//fromRotationMatrix(
		//	xAxis.X, yAxis.X, zAxis.X,
		//	xAxis.Y, yAxis.Y, zAxis.Y,
		//	xAxis.Z, yAxis.Z, zAxis.Z
		//);

		float num8 = (xAxis.X + yAxis.Y) + zAxis.Z;
		if (num8 > 0.0f)
		{
			float num = sqrtf(num8 + 1.0f);
			quaternion.W = num * 0.5f;
			num = 0.5f / num;
			quaternion.X = (zAxis.Y - yAxis.Z) * num;
			quaternion.Y = (xAxis.Z - zAxis.X) * num;
			quaternion.Z = (yAxis.X - xAxis.Y) * num;

			return quaternion;
		}

		if (xAxis.X >= yAxis.Y && xAxis.X >= zAxis.Z)
		{
			float num7 = sqrtf(((1.0f + xAxis.X) - yAxis.Y) - zAxis.Z);
			float num4 = 0.5f / num7;
			quaternion.X = 0.5f * num7;
			quaternion.Y = (yAxis.X + xAxis.Y) * num4;
			quaternion.Z = (zAxis.X + xAxis.Z) * num4;
			quaternion.W = (zAxis.Y - yAxis.Z) * num4;
			return quaternion;
		}

		if (yAxis.Y > zAxis.Z)
		{
			float num6 = sqrtf(((1.0f + yAxis.Y) - xAxis.X) - zAxis.Z);
			float num3 = 0.5f / num6;
			quaternion.X = (xAxis.Y + yAxis.X) * num3;
			quaternion.Y = 0.5f * num6;
			quaternion.Z = (yAxis.Z + zAxis.Y) * num3;
			quaternion.W = (xAxis.Z - zAxis.X) * num3;
			return quaternion;
		}

		float num5 = sqrtf(((1.0f + zAxis.Z) - xAxis.X) - yAxis.Y);
		float num2 = 0.5f / num5;
		quaternion.X = (xAxis.Z + zAxis.X) * num2;
		quaternion.Y = (yAxis.Z + zAxis.Y) * num2;
		quaternion.Z = 0.5f * num5;
		quaternion.W = (yAxis.X - xAxis.Y) * num2;

		return quaternion;
	}

	inline static Quaternion CreateLookAt(const Vector3& dir, const Vector3& up)
	{
		Vector3 zAxis = Vector3::Normalize(dir);
		Vector3 xAxis = Vector3::Normalize(Vector3::Cross(up, dir));
		Vector3 yAxis = Vector3::Normalize(Vector3::Cross(dir, xAxis));

		return CreateFromAxes(xAxis, yAxis, zAxis);
		//tmpZaxis.set( direction ).normalizeLocal();
		//tmpXaxis.set( up ).crossLocal( direction ).normalizeLocal();
		//tmpYaxis.set( direction ).crossLocal( tmpXaxis ).normalizeLocal();
		//fromAxes( tmpXaxis, tmpYaxis, tmpZaxis );

	}

	/*!
	 * @brief Create Quaternion from Euler angle
	 *
	 * @param yaw Y Axis
	 * @param patch X Axis
	 * @param roll Z Axis
	 *
	 * @return TIKI_NEW Quaternion		
	 */
	static Quaternion CreateFromYawPitchRoll(const Vector3& rotation);
	static Quaternion CreateFromYawPitchRoll(float yaw, float pitch, float roll);
	
	//static Quaternion CreateFromRotationMatrix(Matrix matrix)

	bool operator == (const Quaternion& rhs);
	bool operator != (const Quaternion& rhs);

	Quaternion  operator +	(const Quaternion& rhs) const;
	Quaternion& operator +=	(const Quaternion& rhs);
	Quaternion  operator -	(const Quaternion& rhs) const;
	Quaternion& operator -=	(const Quaternion& rhs);

	Quaternion  operator *	(const Quaternion& rhs) const;
	Vector3     operator *  (const Vector3& rhs) const;
	Quaternion& operator *=	(const Quaternion& rhs);
	Quaternion  operator /	(const Quaternion& rhs) const;
	Quaternion& operator /=	(const Quaternion& rhs);

	static Quaternion Identity;

private:

};
