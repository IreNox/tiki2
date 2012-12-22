#pragma once
#include "Core/Quadtree.h"
#include "Core/List.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawArgs.h"
#include "Core/SceneGraphNode.h"

namespace TikiEngine
{
	class SceneGraph
	{
	public:
		SceneGraph();
		~SceneGraph();

		void Initialize(RectangleF& rect, int layerDepth);
		
		void Add(GameObject* go);
		bool Remove(GameObject* go);

		void Update(const UpdateArgs& args);

		void Draw(const DrawArgs& args);

		void Intersect(RectangleF& rect);

	private:
		bool initialized;

		List<GameObject*> selection;

		SceneGraphNode rootNode;
	};
}