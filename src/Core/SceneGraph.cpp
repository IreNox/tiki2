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
		
	}

	void SceneGraph::Initialize(RectangleF& rect , int layerDepth)
	{
		if(this->initialized)
			return;

		this->rootNode.Initialize(rect, layerDepth);

		this->initialized = true;
	}

	void SceneGraph::Add(GameObject* go, GameObjectType gt)
	{
		if(!this->initialized)
			return;

		//switch(gt)
		//{
		//case Default:
		//	this->defaultGOs.Add(go);
		//	break;
		//case Static:
		//	this->staticGOs.Add(go);
		//	break;
		//case Dynamic:
		//	this->dynamicGOs.Add(go);
		//	break;
		//}

		//quadtree.Insert(go);
		if(rootNode.Add(go))
			go->AddRef();
	}

	bool SceneGraph::Remove(GameObject* go)
	{
		if(!this->initialized)
			return false;

		return rootNode.Remove(go);
	}

	void SceneGraph::Find(List<GameObject*>& result, RectangleF& rect, function<bool(GameObject*)> where)
	{
		this->rootNode.Find(result, rect, where);
	}

	void SceneGraph::Find(List<GameObject*>& result, function<bool(GameObject*)> where)
	{
		this->rootNode.Find(result, where);
	}

	void SceneGraph::Find(List<GameObject*>& result, Frustum& frustum)
	{
		this->rootNode.Find(result, frustum);
	}

	void SceneGraph::Find(List<GameObject*>& result, Vector3& point, float distance, function<bool(GameObject*)> where)
	{
		RectangleF rect = RectangleF::Create(point.X - distance, point.Y - distance, distance * 2, distance * 2);
		return rootNode.Find(result, rect, point, distance, where);
	}
	
	void SceneGraph::Update(const UpdateArgs& args)
	{
		if(!this->initialized)
			return;

		this->rootNode.Update(args);
		this->rootNode.LateUpdate(args);
	}

	void SceneGraph::Draw(const DrawArgs& args)
	{
		if(!this->initialized)
			return;

#if _DEBUG
		//quadtree.Draw(args);
		rootNode.Draw(args);
		

		for(UINT i = 0; i < selection.Count(); i++)
		{
			Vector3 pos = selection[i]->PRS.GPosition();

			args.Graphics->DrawLine(pos - Vector3::UnitX, pos + Vector3::UnitX, Color::Blue);
			args.Graphics->DrawLine(pos - Vector3::UnitY, pos + Vector3::UnitY, Color::Blue);
			args.Graphics->DrawLine(pos - Vector3::UnitZ, pos + Vector3::UnitZ, Color::Blue);
		}
#endif
	}
}