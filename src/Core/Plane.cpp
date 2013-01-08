#include "Core/Plane.h"

namespace TikiEngine
{
	// default ctor
	Plane::Plane()
	{
	}

	// default copy ctor
	Plane::Plane(const Plane& plane)
	{
		normal = plane.normal;
		point = plane.point;
		distance = plane.distance;
	}

	Plane::Plane(const Vector3& point0, const Vector3& point1, const Vector3& point2)
	{
		Set(point0, point1, point2);
	}

	Plane::~Plane()
	{
	}

	// operators
	Plane& Plane::operator=(const Plane& src)
	{
		normal = src.normal;
		point = src.point;
		distance = src.distance;

		return (*this);
	}

	// Given Z and Y, Solve for X on the plane 
	float Plane::SolveForX(float y, float z) const
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
	float Plane::SolveForY(float x, float z) const
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
	float Plane::SolveForZ(float x, float y) const
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
	void Plane::Set(const Vector3& point0, const Vector3& point1, const Vector3& point2)
	{
		normal = Vector3::Cross((point1 - point0), (point2 - point0));
		normal = Vector3::Normalize(normal);
		point = point0;
		distance = -Vector3::Dot(point, normal);
	}

	void Plane::SetCoeff(float a, float b, float c, float d)
	{
		// set the normal vector
		normal = Vector3(a,b,c);
		//compute the length of the vector
		float l = 1 / normal.Length();
		// normalize the vector
		normal = Vector3(a * l, b * l, c * l);
		// and divide d by th length as well
		distance = d/l;
	}

	void Plane::SetParameter(float a, float b, float c, float d)
	{
		this->normal = Vector3(a,b,c);
		distance = d;
		float factor = 1.0f / normal.Length();
		normal *= factor;
		distance *= factor;
	}

	float Plane::Distance(const Vector3& point)
	{
		return(distance + Vector3::Dot(point, normal));
	}

	// accessors
	const Vector3& Plane::Normal() const
	{
		return(normal);
	}

	const Vector3& Plane::Point() const
	{
		return(point);
	}

	float Plane::Distance() const
	{
		return distance;
	}
}