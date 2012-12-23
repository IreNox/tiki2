#pragma once

#include "Core/RectangleF.h"
#include "Core/List.h"
#include "Core/GameObject.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawArgs.h"

namespace TikiEngine
{
	class SceneGraphNode
	{
	public:

		SceneGraphNode();
		SceneGraphNode(RectangleF bounds, int layerDepth, SceneGraphNode* parent = NULL);
		~SceneGraphNode();

		bool Add(GameObject* gameObject);
		bool Remove(GameObject* gameObject);
		void Find(List<GameObject*>& result, RectangleF& rect);
		void Find(List<GameObject*>& result, RectangleF& rect, bool(where)(GameObject*));

		SceneGraphNode* Find(GameObject* gameObject);

		void Update(const UpdateArgs& args);
		bool UpdatePosition(GameObject* go);
		void Draw(const DrawArgs& args);

		void Clean();

		void GetContent(List<GameObject*>& content, bool (where)(GameObject*) = 0);
		void GetSubContent(List<GameObject*>& content, bool (where)(GameObject*) = 0);

		bool Subdivide();

		bool IsEmpty();

		RectangleF& Bounds();
		int Count();

	private:
		

		int layerDepth;
		bool subdivided;
		RectangleF bounds;
		
		List<GameObject*> data;

		SceneGraphNode* parent;
		List<SceneGraphNode*> childs;
	};
}