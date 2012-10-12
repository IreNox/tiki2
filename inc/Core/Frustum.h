#pragma once

#include "Core/Plane.h"
#include "Core/IBoundingBox.h"

namespace TikiEngine
{
	using namespace TikiEngine::Resources;

	class Frustum
	{

	private:
		enum 
		{
			TOP = 0,
			BOTTOM,
			LEFT,
			RIGHT,
			NEARP,
			FARP
		};

	public:
		static enum {OUTSIDE, INTERSECT, INSIDE};

		// The planes
		Plane pl[6];

		Frustum();
		~Frustum();

		// performs the plane extraction assuming that the matriz m = View * Projection 
		void Set(const Matrix& m);
		int PointInFrustum(const Vector3& p);
		int SphereInFrustum(const Vector3& p, float radius);
		int BoxInFrustum(IBoundingBox* b);
	};




}

