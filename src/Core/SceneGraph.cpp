#include "Core/SceneGraph.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	SceneGraph::SceneGraph()
		:initialized(false)
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
			return this->dynamicGOs.Remove(go);
			break;
		case Static:
			return this->staticGOs.Remove(go);
			break;
		}
		return false;

	}

	void SceneGraph::Find(List<GameObject*>& result, RectangleF& rect, function<bool(GameObject*)> where)
	{
		this->dynamicGOs.Find(result, rect, where);
	}

	void SceneGraph::Find(List<GameObject*>& result, function<bool(GameObject*)> where)
	{
		this->dynamicGOs.Find(result, where);
	}

	void SceneGraph::Find(List<GameObject*>& result, Frustum& frustum)
	{
		this->dynamicGOs.Find(result, frustum);
	}

	void SceneGraph::Find(List<GameObject*>& result, Vector3& point, float distance, function<bool(GameObject*)> where)
	{
		RectangleF rect = RectangleF::Create(point.X - distance, point.Y - distance, distance * 2, distance * 2);
		return dynamicGOs.Find(result, rect, point, distance, where);
	}

	void SceneGraph::FindInFrustum(List<GameObject*>& result, function<bool(GameObject*)> where)
	{
		this->dynamicGOs.Find(result, where);
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
		this->dynamicGOs.DebugDraw(args);
	
#endif
	}
}