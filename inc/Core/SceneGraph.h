#pragma once

#include "Core/TypeInc.h"

#if !TIKI_USE_SCENEGRAPH
#include "Core/FakeSceneGraph.h"
#else
#include "Core/UpdateArgs.h"
#include "Core/DrawArgs.h"
#include "Core/SceneGraphNode.h"
#include "Core/Vector3.h"
#include "Core/Frustum.h"
#include <functional>

namespace TikiEngine
{
	class SceneGraph
	{
	public:

#pragma region Class
		SceneGraph();
		~SceneGraph();

		void Initialize(RectangleF& bounds, int layerDepth);

#pragma endregion

#pragma region Member - Add/Remove/Draw/Update
		void Add(GameObject* go);
		void Remove(GameObject* go);

		void Draw(const DrawArgs& args);
		void Update(const UpdateArgs& args);
		void LateUpdate(const UpdateArgs& args);

#pragma endregion

#pragma region Member - Do
		void Do(function<void(GameObject*)> whatIWant);
		void DoInFrustum(function<void(GameObject*)> whatIWant);
		void DoWithinRange(const Vector3& point, float distance, function<void(GameObject*)> whatIWant);
#pragma endregion

#pragma region Member - Find
		void Find(List<GameObject*>& result, RectangleF& rect , function<bool(GameObject*)> where = 0);
		void Find(List<GameObject*>& result, function<bool(GameObject*)> where = 0);
		void Find(List<GameObject*>& result, Frustum& frustum);
		void Find(List<GameObject*>& result, Vector3& point, float distance, function<bool(GameObject*)> where = 0);
		void FindInFrustum(List<GameObject*>& result, function<bool(GameObject*)> where = 0);

#pragma endregion

		inline List<GameObject*>& GetAllGameObjects() { return gameObjects; }

	private:

		void RemoveGameObjects();

		bool initialized;

		List<GameObject*> removeList;
		List<GameObject*> gameObjects;
		SceneGraphNode dynamicObjects;
	};
}
#endif