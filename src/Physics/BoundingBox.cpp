#include "Physics/BoundingBox.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	namespace Physics
	{

		BoundingBox::BoundingBox(Engine* engine) : IBoundingBox(engine)
		{
			this->engine = engine;
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

		void BoundingBox::DrawDebug(Color color)
		{
			engine->graphics->DrawLine(Vector3(minimum.X, minimum.Y, minimum.Z), Vector3(maximum.X, minimum.Y, minimum.Z), color);
			engine->graphics->DrawLine(Vector3(minimum.X, minimum.Y, maximum.Z), Vector3(maximum.X, minimum.Y, maximum.Z), color);
			engine->graphics->DrawLine(Vector3(minimum.X, minimum.Y, minimum.Z), Vector3(minimum.X, minimum.Y, maximum.Z), color);
			engine->graphics->DrawLine(Vector3(maximum.X, minimum.Y, minimum.Z), Vector3(maximum.X, minimum.Y, maximum.Z), color);
																				 										 
			engine->graphics->DrawLine(Vector3(minimum.X, maximum.Y, minimum.Z), Vector3(maximum.X, maximum.Y, minimum.Z), color);
			engine->graphics->DrawLine(Vector3(minimum.X, maximum.Y, maximum.Z), Vector3(maximum.X, maximum.Y, maximum.Z), color);
			engine->graphics->DrawLine(Vector3(minimum.X, maximum.Y, minimum.Z), Vector3(minimum.X, maximum.Y, maximum.Z), color);
			engine->graphics->DrawLine(Vector3(maximum.X, maximum.Y, minimum.Z), Vector3(maximum.X, maximum.Y, maximum.Z), color);
																				 										
			engine->graphics->DrawLine(Vector3(minimum.X, minimum.Y, minimum.Z), Vector3(minimum.X, maximum.Y, minimum.Z), color);
			engine->graphics->DrawLine(Vector3(maximum.X, minimum.Y, minimum.Z), Vector3(maximum.X, maximum.Y, minimum.Z), color);
			engine->graphics->DrawLine(Vector3(minimum.X, minimum.Y, maximum.Z), Vector3(minimum.X, maximum.Y, maximum.Z), color);
			engine->graphics->DrawLine(Vector3(maximum.X, minimum.Y, maximum.Z), Vector3(maximum.X, maximum.Y, maximum.Z), color);
		}

	}
}