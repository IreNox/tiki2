#pragma once
#include "Core/List.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawArgs.h"
#include "Core/SceneGraphNode.h"
#include "Core/Vector3.h"

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

		void Find(RectangleF& rect);

	private:
		bool initialized;

		List<GameObject*> selection;

		SceneGraphNode rootNode;
	};
}