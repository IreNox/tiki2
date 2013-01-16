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
		inline void SetDynamic(){ this->isDynamic = true; }
		inline bool IsDynamic(){ return this->isDynamic; }
		bool IsCulled;

		RectangleF Bounds;

	private:
		GameObject* go;

		float width;
		float height;
		bool isDynamic;
	};
}