#pragma once

#include "Core/IBoundingBox.h"
#include "PhysX/Foundation/NxBounds3.h"

namespace TikiEngine
{
	namespace Physics
	{
		using namespace TikiEngine::Resources;


		class BoundingBox : public IBoundingBox
		{

		public:
			/*! @brief Creates a new BoundingBox. */
			BoundingBox(Engine* engine);
			~BoundingBox();

			Vector3 GetMin() const;
			Vector3 GetMax() const;

			void Set(const Vector3& min, const Vector3& max);
			bool Intersects(const IBoundingBox& b) const;

			void DrawDeug(const DrawArgs& args);

			#pragma region IResource Members
			void* GetNativeResource() { return (void*)&bounds; }
			bool GetReady() { return true; }

		protected:
			void loadFromStream(wcstring fileName, Stream* stream) {}
			void saveToStream(wcstring fileName, Stream* stream)  {}
			#pragma endregion

		private:
			NxBounds3 bounds;
			Vector3 minimum;
			Vector3 maximum;
		};
	}
}
