#pragma once

#include "Core/Vector3.h"

namespace TikiEngine
{
	/* A Plane in 3D Space represented in point-normal form (Ax + By + Cz + D = 0).
	 *The convention for the distance constant D is: D = -(A, B, C) dot (X, Y, Z) */
	class Plane
	{
	public:
		// ctor / dtor
		Plane();
		Plane(const Plane& plane);
		// Setup Plane object given a clockwise ordering of 3D points 
		Plane(const Vector3& point0, const Vector3& point1, const Vector3& point2);
		~Plane();

		// operators
		Plane& operator=(const Plane& src);

		friend bool operator==(const Plane& a, const Plane& b)
		{
			return (a.normal == b.normal && a.point == b.point);
		}

		// setters
		void Set(const Vector3& point0, const Vector3& point1, const Vector3& point2); 
		void SetCoeff(float a, float b, float c, float d);
		void SetParameter(float a, float b, float c, float d);


		float SolveForX(float y, float t) const;
		float SolveForY(float x, float z) const;
		float SolveForZ(float x, float y) const;


		// accessors
		const Vector3& Normal() const;
		const Vector3& Point() const;
		float Distance() const;

		float Distance(const Vector3& point);
		//float SignedDistance(const Vector3& point) const;

	private:
		Vector3 normal;
		Vector3 point;
		float distance;


	};
}

