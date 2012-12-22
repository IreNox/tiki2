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

		void Add(GameObject* gameObject);
		bool Remove(GameObject* gameObject);
		void Intersects(List<GameObject*>& content, RectangleF& rect);

		SceneGraphNode* Find(GameObject* gameObject);

		void Update(const UpdateArgs& args);
		void Draw(const DrawArgs& args);

		void GetContent(List<GameObject*>& content);
		void GetSubContent(List<GameObject*>& content);

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