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
		bool IsInsideFrustum(Frustum& frustum);
		inline bool IsDynamic(){ return this->isDynamic; }

		RectangleF Bounds;

	private:
		GameObject* go;

		float width;
		float height;
		bool isDynamic;

	};
}