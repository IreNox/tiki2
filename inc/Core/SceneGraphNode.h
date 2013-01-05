#pragma once

#include "Core/RectangleF.h"
#include "Core/List.h"
#include "Core/GameObject.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawArgs.h"
#include "Core/Frustum.h"

namespace TikiEngine
{
	class SceneGraphNode
	{
	public:

		SceneGraphNode();
		~SceneGraphNode();

		void Initialize(RectangleF bounds, int layerDepth, SceneGraphNode* parent = NULL);

		bool Add(GameObject* gameObject);
		bool Remove(GameObject* gameObject);

		void Find(List<GameObject*>& result, RectangleF& rect, function<bool(GameObject*)> where = 0);
		void Find(List<GameObject*>& result, RectangleF& rect, Vector3& point, float distance, function<bool(GameObject*)> where = 0);
		void Find(List<GameObject*>& result, function<bool(GameObject*)> where = 0);
		void Find(List<GameObject*>& result, Frustum& frustum);
		

		SceneGraphNode* Find(GameObject* gameObject);

		void Update(const UpdateArgs& args);
		void LateUpdate(const UpdateArgs& args);
		void PerformCulling(Frustum& frustum);

		bool UpdatePosition(GameObject* go);
		void Draw(const DrawArgs& args);
		void DebugDraw(const DrawArgs& args);

		void Clean();

		void GetContent(List<GameObject*>& content, function<bool(GameObject*)> where = 0);
		void GetSubContent(List<GameObject*>& content, function<bool(GameObject*)> where = 0);

		bool IsEmpty();

		RectangleF& Bounds();
		int Count();

		void subdivide();

	private:

		inline bool IsSubdivided()
		{
			return childDataCount != 0;
		}
		
		int childDataCount;
		int layerDepth;
		bool subdivided;
		RectangleF bounds;
		
		List<GameObject*> data;

		SceneGraphNode* parent;
		List<SceneGraphNode*> childs;
	};
}