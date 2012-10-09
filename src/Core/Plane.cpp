#include "Core/Plane.h"

namespace TikiEngine
{
	// default ctor
	inline Plane::Plane()
	{
	}

	// default copy ctor
	inline Plane::Plane(const Plane& plane)
	{
		normal = plane.normal;
		point = plane.point;
		distance = plane.distance;
	}

	inline Plane::Plane(const Vector3& point0, const Vector3& point1, const Vector3& point2)
	{
		Set(point0, point1, point2);
	}

	inline Plane::~Plane()
	{
	}

	// operators
	inline Plane& Plane::operator=(const Plane& src)
	{
		normal = src.normal;
		point = src.point;
		distance = src.distance;

		return (*this);
	}

	// Given Z and Y, Solve for X on the plane 
	inline float Plane::SolveForX(float y, float z) const
	{
		//Ax + By + Cz + D = 0
		// Ax = -(By + Cz + D)
		// x = -(By + Cz + D)/A
		if (normal.X)
		{
			return ( -(normal.Y * y + normal.Z * z + distance) / normal.X );
		}

		return (0.0f);
	}


	// Given X and Z, Solve for Y on the plane 
	inline float Plane::SolveForY(float x, float z) const
	{
		// Ax + By + Cz + D = 0
		// By = -(Ax + Cz + D)
		// y = -(Ax + Cz + D)/B
		if (normal.Y)
		{
			return ( -(normal.X * x + normal.Z * z + distance) / normal.Y );
		}

		return (0.0f);
	}

	// Given X and Y, Solve for Z on the plane 
	inline float Plane::SolveForZ(float x, float y) const
	{
		//Ax + By + Cz + D = 0
		// Cz = -(Ax + By + D)
		// z = -(Ax + By + D)/C
		if (normal.Z)
		{
			return ( -(normal.X * x + normal.Y * y + distance) / normal.Z );
		}

		return (0.0f);
	}

	// Setup Plane object given a clockwise ordering of 3D points 
	inline void Plane::Set(const Vector3& point0, const Vector3& point1, const Vector3& point2)
	{
		normal = Vector3::Cross((point1 - point0), (point2 - point0));
		normal.Normalize();
		point = point0;
		distance = -Vector3::Dot(point, normal);
	}

	// accessors
	inline const Vector3& Plane::Normal() const
	{
		return(normal);
	}

	inline const Vector3& Plane::Point() const
	{
		return(point);
	}

	inline const float& Plane::Distance() const
	{
		return(distance);
	}
}