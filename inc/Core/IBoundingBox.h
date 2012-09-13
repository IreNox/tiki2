#pragma once

#include "Core/IResource.h"

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

			/* !@brief Set Bounding box via min max vectors
				@param min - Minimum point of bounds.
				@param max - Maximum point of bounds. */
			virtual void Set(const Vector3& min, const Vector3& max) = 0;

			
			/* !@brief indicates whether the intersection of this and b is empty or not.
				@param b - Bounds to test for intersection. */
			virtual bool Intersects(const IBoundingBox& b) const = 0;

			virtual void DrawDeug(const DrawArgs& args) = 0;

		};
	}
}