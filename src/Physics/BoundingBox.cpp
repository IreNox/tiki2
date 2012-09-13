#include "Physics/BoundingBox.h"

namespace TikiEngine
{
	namespace Physics
	{

		BoundingBox::BoundingBox(Engine* engine) : IBoundingBox(engine)
		{
		}

		BoundingBox::~BoundingBox()
		{
		}

		Vector3 BoundingBox::GetMin() const
		{
			return minimum;
		}

		Vector3 BoundingBox::GetMax() const
		{
			return maximum;
		}

		void BoundingBox::Set(const Vector3& min, const Vector3& max)
		{
			minimum = min;
			maximum = max;
			bounds.set(min.arr, max.arr);
		}

		bool BoundingBox::Intersects(const IBoundingBox& b) const
		{
			NxBounds3 bb;
			bb.set(b.GetMin().arr, b.GetMax().arr);
			return bounds.intersects(bb);
		}

		void BoundingBox::DrawDeug(const DrawArgs& args)
		{
			// TODO
		}

	}
}