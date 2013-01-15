#include "Core/SceneGraph.h"
#include "Core/IGraphics.h"

#if TIKI_USE_SCENEGRAPH
namespace TikiEngine
{
	SceneGraph::SceneGraph()
		:initialized(false), locked(false)
	{

	}

	SceneGraph::~SceneGraph()
	{
		for(UINT i = 0; i < defaultGOs.Count(); i++)
			SafeRelease(&defaultGOs[i]);
		for(UINT i = 0; i < staticGOs.Count(); i++)
			SafeRelease(&staticGOs[i]);
	}

	void SceneGraph::Initialize(RectangleF& rect , int layerDepth)
	{
		if(this->initialized)
			return;

		this->dynamicGOs.Initialize(rect, layerDepth);

		this->initialized = true;
	}

	void SceneGraph::Add(GameObject* go)
	{
		if(!this->initialized)
			return;

		switch(go->GetGameObjectType())
		{
		case GOT_Default:
			this->defaultGOs.Add(go);
			break;
		case GOT_Static:
			this->staticGOs.Add(go);
			break;
		case GOT_Dynamic:
			this->dynamicGOs.Add(go);
			break;
		}
		go->AddRef();

	}

	bool SceneGraph::Remove(GameObject* go)
	{
		if(!this->initialized)
			return false;

		switch(go->GetGameObjectType())
		{
		case GOT_Default:
			return this->defaultGOs.Remove(go);
			break;
		case GOT_Dynamic:
			if(IsLocked())
			{
				removeList.Add(go);
				return true;
			}
			return this->dynamicGOs.Remove(go);
			break;
		case GOT_Static:
			return this->staticGOs.Remove(go);
			break;
		}
		return false;

	}

	void SceneGraph::Do(function<void(GameObject*)> whatIWant)
	{
		if(!this->initialized)
			return;

		this->Lock();
		this->dynamicGOs.Do(whatIWant);
		this->Unlock();
	}

	void SceneGraph::DoWithinRange(Vector3& point, float distance, function<void(GameObject*)> whatIWant)
	{
		if(!initialized)
			return;

		Lock();
		RectangleF rect = RectangleF::Create(point.X - distance, point.Y - distance, distance * 2, distance * 2);
		dynamicGOs.DoWithinRange(rect, point, distance, whatIWant);
		Unlock();
	}

	void SceneGraph::Find(List<GameObject*>& result, RectangleF& rect, function<bool(GameObject*)> where)
	{
		if(!this->initialized)
			return;

		this->Lock();
		this->dynamicGOs.Find(result, rect, where);
		this->Unlock();
	}

	void SceneGraph::Find(List<GameObject*>& result, function<bool(GameObject*)> where)
	{
		if(!this->initialized)
			return;

		this->Lock();
		this->dynamicGOs.Find(result, where);
		this->Unlock();
	}

	void SceneGraph::Find(List<GameObject*>& result, Frustum& frustum)
	{
		if(!this->initialized)
			return;

		this->dynamicGOs.Find(result, frustum);
	}

	void SceneGraph::Find(List<GameObject*>& result, Vector3& point, float distance, function<bool(GameObject*)> where)
	{
		if(!this->initialized)
			return;

		this->Lock();
		RectangleF rect = RectangleF::Create(point.X - distance, point.Y - distance, distance * 2, distance * 2);
		return dynamicGOs.Find(result, rect, point, distance, where);
		this->Unlock();
	}

	void SceneGraph::FindInFrustum(List<GameObject*>& result, function<bool(GameObject*)> where)
	{
		this->Lock();
		this->dynamicGOs.Find(result, where);
		this->Unlock();
	}

	List<GameObject*>& SceneGraph::GetDefaultGOs()
	{
		return this->defaultGOs;
	}

	List<GameObject*>& SceneGraph::GetStaticGOs()
	{
		return this->staticGOs;
	}
	
	void SceneGraph::Update(const UpdateArgs& args)
	{
		if(!this->initialized)
			return;

		for(UINT i = 0; i < defaultGOs.Count(); i++)
			defaultGOs[i]->Update(args);
		for(UINT i = 0; i < staticGOs.Count(); i++)
			staticGOs[i]->Update(args);

		this->dynamicGOs.Update(args);
		this->dynamicGOs.LateUpdate(args);
	}

	void SceneGraph::PerformCulling(Frustum& frustum)
	{
		if(!this->initialized)
			return;

		//for(UINT i = 0; i < defaultGOs.Count(); i++)
		//	defaultGOs[i]->GetSceneGraphElement().PerformFrustumCulling(frustum);

		for(UINT i = 0; i < staticGOs.Count(); i++)
			staticGOs[i]->GetSceneGraphElement().PerformFrustumCulling(frustum);

		//this->dynamicGOs.PerformCulling(frustum);
	}

	void SceneGraph::Draw(const DrawArgs& args)
	{
		if(!this->initialized)
			return;

#if _DEBUG
		//quadtree.Draw(args);

		for(UINT i = 0; i < defaultGOs.Count(); i++)
			defaultGOs[i]->Draw(args);
		for(UINT i = 0; i < staticGOs.Count(); i++)
			staticGOs[i]->Draw(args);

		this->dynamicGOs.Draw(args);
		this->dynamicGOs.DebugDraw(args);
	
#endif
	}

	void SceneGraph::Unlock()
	{
		this->locked = false;
		if(removeList.Count() != 0)
		{
			for(UINT i = 0; i < removeList.Count(); i++)
				this->dynamicGOs.Remove(removeList[i]);
			removeList.Clear();
		}
	}
}
#else

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
		if(go->GetSceneGraphElement().IsDynamic())
			dynamicObjects.Remove(go);

		go->Release();
		return gameObjects.Remove(go);
	}

	void SceneGraph::Draw(const DrawArgs& args)
	{
		FOREACH_PTR_CALL(gameObjects, Draw(args))
	}

	void SceneGraph::Update(const UpdateArgs& args)
	{
		FOREACH_PTR_CALL(gameObjects, Update(args))

		dynamicObjects.LateUpdate(args);

	}
#pragma endregion

#pragma region DO
	void SceneGraph::Do(function<void(GameObject*)> whatIWant)
	{
		FOREACH(gameObjects, whatIWant(gameObjects[i]))
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
		UInt32 i = 0;
		while (i < gameObjects.Count())
		{
			if (Vector3::Distance(point, gameObjects[i]->PRS.GPosition()))
				whatIWant(gameObjects[i]);

			i++;
		}
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
		result.AddRange(gameObjects);
	}

	void SceneGraph::Find(List<GameObject*>& result, Vector3& point, float distance, function<bool(GameObject*)> where)
	{
		UInt32 i = 0;
		while (i < gameObjects.Count())
		{
			if (Vector3::Distance(point, gameObjects[i]->PRS.GPosition()))
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

}


//bool SceneGraphEmpty = true;
#endif