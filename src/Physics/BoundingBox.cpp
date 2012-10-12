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

		Vector3 BoundingBox::GetVertexP(const Vector3& normal)
		{
			Vector3 p = minimum;
			if (normal.X >= 0) p.X = maximum.X;
			if (normal.Y >= 0) p.Y = maximum.Y;
			if (normal.Z >= 0) p.Z = maximum.Z;
			return p;
		}

		Vector3 BoundingBox::GetVertexN(const Vector3& normal)
		{
			Vector3 n = maximum; 
			if (normal.X >= 0) n.X = minimum.X;
			if (normal.Y >= 0) n.Y = minimum.Y;
			if (normal.Z >= 0) n.Z = minimum.Z;
			return n;
		}

		void BoundingBox::Set(const Vector3& min, const Vector3& max)
		{
			minimum = min;
			maximum = max;
			bounds.set(min.arr, max.arr);
		}

		bool BoundingBox::Intersects(IBoundingBox* b) 
		{
			NxBounds3* bb = (NxBounds3*)(b->GetNativeResource()); 
			return bounds.intersects(*bb);
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