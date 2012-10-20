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

	static Quaternion Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2, float amount);
	static Quaternion Lerp(const Quaternion& quaternion1, const Quaternion& quaternion2, float amount);

	static Quaternion CreateFromAxisAngle(const Vector3& axis, float angle);

	/*!
	 * @brief Create Quaternion from Euler angle
	 *
	 * @param yaw Y Axis
	 * @param patch X Axis
	 * @param roll Z Axis
	 *
	 * @return New Quaternion		
	 */
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
