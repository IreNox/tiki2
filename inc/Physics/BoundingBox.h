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

			Vector3 GetVertexP(const Vector3& normal);
			Vector3 GetVertexN(const Vector3& normal);

			void Set(const Vector3& min, const Vector3& max);
			bool Intersects(IBoundingBox* b);
		    bool Contains(const Vector3& p);

#if _DEBUG
			void DrawDebug(Color color);
#endif

			#pragma region IResource Members
			void* GetNativeResource() { return (void*)&bounds; }
			bool GetReady() { return true; }

		protected:
			void loadFromStream(wcstring fileName, Stream* stream) {}
			void saveToStream(wcstring fileName, Stream* stream)  {}
			#pragma endregion

		private:
			Engine* engine;
			NxBounds3 bounds;
			Vector3 minimum;
			Vector3 maximum;
		};
	}
}
