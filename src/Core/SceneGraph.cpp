
#include "Core/SceneGraph.h"

#if TIKI_USE_SCENEGRAPH
#include "Core/IGraphics.h"

namespace TikiEngine
{
#pragma region class
	SceneGraph::SceneGraph()
		:initialized(false)
	{

	}

	SceneGraph::~SceneGraph()
	{
		FOREACH_PTR_CALL(gameObjects, Release());
	}

	void SceneGraph::Initialize(RectangleF& bounds, int layerDepth)
	{
		if(initialized)
			return;

		this->dynamicObjects.Initialize(bounds, layerDepth);

		this->initialized = true;
	}
#pragma endregion

	#pragma region Add/Remove/Draw/Update
	void SceneGraph::Add(GameObject* go)
	{
		if(go->GetSceneGraphElement().IsDynamic())
			dynamicObjects.Add(go);

		gameObjects.Add(go);
		go->AddRef();
	}

	bool SceneGraph::Remove(GameObject* go)
	{
		if(gameObjects.Contains(go))
		{
			removeList.Add(go);
			return true;
		}

		return false;
	}

	void SceneGraph::Draw(const DrawArgs& args)
	{
		FOREACH_PTR_CALL(gameObjects, Draw(args))
#if _DEBUG
		//dynamicObjects.DebugDraw(args);
#endif
	}

	void SceneGraph::Update(const UpdateArgs& args)
	{
		this->RemoveGameObjects();

		FOREACH_PTR_CALL(gameObjects, Update(args))

		dynamicObjects.LateUpdate(args);

	}

	void SceneGraph::LateUpdate(const UpdateArgs& args)
	{
		FOREACH_PTR_CALL(gameObjects, LateUpdate(args))
	}
	#pragma endregion

	#pragma region DO
	void SceneGraph::Do(function<void(GameObject*)> whatIWant)
	{
		FOREACH_CODE(gameObjects, whatIWant(gameObjects[i]))
	}

	void SceneGraph::DoInFrustum(function<void(GameObject*)> whatIWant)
	{
		UInt32 i = 0;
		while (i < gameObjects.Count())
		{
			whatIWant(gameObjects[i]);

			i++;
		}
	}

	void SceneGraph::DoWithinRange(const Vector3& point, float distance, function<void(GameObject*)> whatIWant)
	{
		Vector2 tmp = Vector2(distance) ;
		RectangleF rect = RectangleF::Create(point.XZ() - tmp , tmp * 2);

		this->dynamicObjects.DoWithinRange( rect, point, distance, whatIWant);

		//UInt32 i = 0;
		//while (i < gameObjects.Count())
		//{
		//	if (Vector3::DistanceSquared(point, gameObjects[i]->PRS.GPosition()) < distance * distance)
		//	{
		//		whatIWant(gameObjects[i]);
		//	}
		//	i++;
		//}
	}
#pragma endregion

#pragma region find
	void SceneGraph::Find(List<GameObject*>& result, RectangleF& rect , function<bool(GameObject*)> where)
	{
		UInt32 i = 0;
		while (i < gameObjects.Count())
		{
			if (rect.Contains(gameObjects[i]->PRS.GPosition().XZ()))
			{
				if (where == 0 || where(gameObjects[i]))
					result.Add(gameObjects[i]);
			}

			i++;
		}
	}

	void SceneGraph::Find(List<GameObject*>& result, function<bool(GameObject*)> where)
	{
		UInt32 i = 0;
		while (i < gameObjects.Count())
		{
			if (where == 0 || where(gameObjects[i]))
				result.Add(gameObjects[i]);

			i++;
		}
	}

	void SceneGraph::Find(List<GameObject*>& result, Frustum& frustum)
	{
		for(UINT i = 0; i < gameObjects.Count(); i++)
		{
			GameObject* go = gameObjects[i];
			if(go->GetSceneGraphElement().IsInsideFrustum(frustum))
			{
				result.Add(go);
			}
		}
	}

	void SceneGraph::Find(List<GameObject*>& result, Vector3& point, float distance, function<bool(GameObject*)> where)
	{
		UInt32 i = 0;
		while (i < gameObjects.Count())
		{
			if (Vector3::Distance(point, gameObjects[i]->PRS.GPosition()) < distance)
			{
				if (where == 0 || where(gameObjects[i]))
					result.Add(gameObjects[i]);
			}

			i++;
		}
	}

	void SceneGraph::FindInFrustum(List<GameObject*>& result, function<bool(GameObject*)> where)
	{
		UInt32 i = 0;
		while (i < gameObjects.Count())
		{
			if (where == 0 || where(gameObjects[i]))
				result.Add(gameObjects[i]);

			i++;
		}
	}

#pragma endregion

#pragma region private methods
	void SceneGraph::RemoveGameObjects()
	{
		for(UINT i = 0; i < removeList.Count(); i++)
		{
			GameObject* go = removeList[i];
			if(go->GetSceneGraphElement().IsDynamic())
				dynamicObjects.Remove(go);

			go->Release();
			gameObjects.Remove(go);
		}
		removeList.Clear();
	}
#pragma endregion

}
#else
bool emptySceneGraph = true;
#endif