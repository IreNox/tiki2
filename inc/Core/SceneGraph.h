#pragma once
#include "Core/Quadtree.h"
#include "Core/List.h"
#include "Core/DrawArgs.h"

namespace TikiEngine
{
	class SceneGraph
	{
	public:
		SceneGraph();
		~SceneGraph();

		void Initialize(RectangleF& rect, int layerDepth);
		
		void Insert(GameObject* go);

		void Draw(const DrawArgs& args);

		void Intersect(RectangleF& rect);

	private:
		Quadtree quadtree;

		bool initialized;

		List<GameObject*> queryContent;
	};
}