#pragma once
#include "Core/List.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawArgs.h"
#include "Core/SceneGraphNode.h"
#include "Core/Vector3.h"
#include "Core/Frustum.h"
#include <functional>

namespace TikiEngine
{
	enum GameObjectType
	{
		Default,
		Static,
		Dynamic
	};

	class SceneGraph
	{
	public:
		SceneGraph();
		~SceneGraph();

		void Initialize(RectangleF& rect, int layerDepth);
		
		void Add(GameObject* go, GameObjectType gt = Default);
		bool Remove(GameObject* go);

		void Update(const UpdateArgs& args);

		void Draw(const DrawArgs& args);

		void Find(List<GameObject*>& result, RectangleF& rect , function<bool(GameObject*)> where = 0);
		void Find(List<GameObject*>& result, function<bool(GameObject*)> where = 0);
		void Find(List<GameObject*>& result, Frustum& frustum);
		void Find(List<GameObject*>& result, Vector3& point, float distance, function<bool(GameObject*)> where = 0);

	private:
		bool initialized;

		List<GameObject*> selection;

		SceneGraphNode rootNode;

		List<GameObject*> defaultGOs;
		List<GameObject*> staticGOs;
		SceneGraphNode dynamicGOs;
	};
}