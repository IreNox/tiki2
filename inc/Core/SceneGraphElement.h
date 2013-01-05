#pragma once
#include "Core/RectangleF.h"
#include "Core/Frustum.h"

namespace TikiEngine
{
	class GameObject;

	class SceneGraphElement
	{
	public:
		SceneGraphElement();
		SceneGraphElement(GameObject* go);
		~SceneGraphElement();

		void Update();
		void PerformFrustumCulling(Frustum& frustum);

		inline bool IsCulled() { return this->culled; }

		RectangleF Bounds;

	private:
		GameObject* go;

		float width;
		float height;

		bool culled;
	};
}