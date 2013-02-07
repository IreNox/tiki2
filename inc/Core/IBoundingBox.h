#pragma once

#include "Core/IResource.h"
#include "Core/Vector3.h"
#include "Core/Color.h"

namespace TikiEngine
{
	namespace Resources
	{
		/*! @brief Class representing 3D range or axis aligned bounding box. */
		class IBoundingBox : public IResource
		{
		public:
			IBoundingBox(Engine* engine) 
				: IResource(engine) {}

			virtual ~IBoundingBox() {}

			virtual Vector3 GetMin() const = 0;
			virtual Vector3 GetMax() const = 0;

			virtual Vector3 GetVertexP(const Vector3& normal) = 0;
			virtual Vector3 GetVertexN(const Vector3& normal) = 0;


			/* !@brief Set Bounding box via min max vectors
				@param min - Minimum point of bounds.
				@param max - Maximum point of bounds. */
			virtual void Set(const Vector3& min, const Vector3& max) = 0;
			virtual void SetOffset(const Vector3& offset) = 0;

			
			/* !@brief indicates whether the intersection of this and b is empty or not.
				@param b - Bounds to test for intersection. */
			virtual bool Intersects(IBoundingBox* b) = 0;

			virtual bool Contains(const Vector3& p) = 0;

#if _DEBUG
			virtual void DrawDebug(Color color) = 0;
#endif

		};
	}
}