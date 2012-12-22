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

		//this->quadtree = Quadtree(rect, layerDepth);
		//this->quadtree.Create();

		this->rootNode = SceneGraphNode(rect, layerDepth);

		this->initialized = true;
	}

	void SceneGraph::Add(GameObject* go)
	{
		if(!this->initialized)
			return;

		//quadtree.Insert(go);
		rootNode.Add(go);
	}

	bool SceneGraph::Remove(GameObject* go)
	{
		if(!this->initialized)
			return false;

		return rootNode.Remove(go);
	}

	void SceneGraph::Intersect(RectangleF& rect)
	{
		this->selection.Clear();

		//this->quadtree.Intersects(this->selection, rect);
		this->rootNode.Intersects(this->selection, rect);
	}

	void SceneGraph::Update(const UpdateArgs& args)
	{
		if(!this->initialized)
			return;

		this->rootNode.Update(args);
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