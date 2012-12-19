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

		this->quadtree = Quadtree(rect, layerDepth);
		this->quadtree.Create();

		this->initialized = true;
	}

	void SceneGraph::Insert(GameObject* go)
	{
		if(!this->initialized)
			return;

		quadtree.Insert(go);
	}

	void SceneGraph::Intersect(RectangleF& rect)
	{
		this->queryContent.Clear();

		this->quadtree.Intersects(this->queryContent, rect);
	}

	void SceneGraph::Draw(const DrawArgs& args)
	{
		if(!this->initialized)
			return;

#if _DEBUG
		quadtree.Draw(args);

		for(UINT i = 0; i < queryContent.Count(); i++)
		{
			Vector3 pos = queryContent[i]->PRS.GPosition();

			args.Graphics->DrawLine(pos - Vector3::UnitX, pos + Vector3::UnitX, Color::Blue);
			args.Graphics->DrawLine(pos - Vector3::UnitY, pos + Vector3::UnitY, Color::Blue);
			args.Graphics->DrawLine(pos - Vector3::UnitZ, pos + Vector3::UnitZ, Color::Blue);
		}
#endif
	}
}