#pragma once

#include "Core/IBoundingBox.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Resources;

		class BoxSide
		{
		protected:
			Vector3 GetBoxPt(IBoundingBox* box, int index);

			// Test to see if all the points lie within TestSide
			int CoPlanar(BoxSide testSide);

			// Check to see if all the points lie inside of TestSide
			int	PointsInside(BoxSide testSide);

		public:
			BoxSide();
			~BoxSide();

			// Determine all properties of the box side given a BBox and index (0-5) of the side
			void SetFromBox(IBoundingBox* box, int side);

			// Determine if a plane neighbors this plane
			int Neighbors(BoxSide testSide);

			float GetSize();

		protected:
			Vector3 Normal;
			Vector3 Points[4];
			float D;
			float Size;
			int CurSide;

		};


	}
}