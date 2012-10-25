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


		int TriBoxIntersect(IBoundingBox* BBox, TRI Tri);

	}
}