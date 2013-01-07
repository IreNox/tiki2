#include "Core/SceneGraph.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
#if TIKI_USE_SCENEGRAPH
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
		case Default:
			this->defaultGOs.Add(go);
			break;
		case Static:
			this->staticGOs.Add(go);
			break;
		case Dynamic:
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
		case Default:
			return this->defaultGOs.Remove(go);
			break;
		case Dynamic:
			if(IsLocked())
			{
				removeList.Add(go);
				return true;
			}
			return this->dynamicGOs.Remove(go);
			break;
		case Static:
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

		for(UINT i = 0; i < defaultGOs.Count(); i++)
			defaultGOs[i]->GetSceneGraphElement().PerformFrustumCulling(frustum);

		for(UINT i = 0; i < staticGOs.Count(); i++)
			staticGOs[i]->GetSceneGraphElement().PerformFrustumCulling(frustum);

		this->dynamicGOs.PerformCulling(frustum);
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
		//this->dynamicGOs.DebugDraw(args);
	
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
#endif
}