#pragma once

#include "Core/IBoundingBox.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Resources;

		struct TRI
		{
			Vector3 Pt[3];
			void* UserData;	// Navigation Cell
		};


		const int INSIDE = 0;
		const int OUTSIDE = 1;

		// Determine if a bounding box and triangle intersect
		// return 1 = OUTSIDE, 0 = INSIDE
		int TriBoxIntersect(IBoundingBox* box, TRI Tri);
	}
}