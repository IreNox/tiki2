#include "Core/Quadtree.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
#pragma region Quadtree
	Quadtree::Quadtree()
		:node(0), created(false)
	{

	}

	Quadtree::Quadtree(const RectangleF& rect, int layerDepth)
	:bounds(rect), layerDepth(layerDepth)
	{

	}

	Quadtree::~Quadtree()
	{

	}

	void Quadtree::Create()
	{
		if(!IsReady())
			return;

		this->node = new QuadtreeNode(this->bounds, this->layerDepth);
		this->created = true;
	}

	bool Quadtree::IsReady()
	{
		RectangleF rec = {0,0,0,0};
		return this->created && this->bounds != rec;
	}

	void Quadtree::SetBound(RectangleF& rect)
	{
		if(!IsReady())
			return;

		this->bounds = rect;
	}

	void Quadtree::Insert(GameObject* go)
	{
		if(!IsReady())
			return;

		node->Insert(go);
	}

	void Quadtree::Intersects(List<GameObject*>& result, RectangleF& rect)
	{
		this->node->Intersects(result, rect);
	}

	void Quadtree::Draw(const DrawArgs& args)
	{
		if(!IsReady())
			return;

		this->node->Draw(args);
	}

#pragma endregion

#pragma region QuadtreeNode
	QuadtreeNode::QuadtreeNode(RectangleF& rect, int layerDepth)
		:bounds(rect), layerDepth(layerDepth)
	{

	}

	QuadtreeNode::~QuadtreeNode()
	{

	}

	void QuadtreeNode::Insert(GameObject* go)
	{
		if(childs.Count() == 0)
			CreateSubdivision();

		for(UINT i = 0; i < childs.Count(); i++)
		{
			if(childs[i]->Bounds().Collide(go->Bounds()) == Contain)
			{
				childs[i]->Insert(go);
				return;
			}
		}

		this->content.Add(go);
	}

	void QuadtreeNode::Draw(const DrawArgs& args)
	{
#if _DEBUG
		args.Graphics->DrawLine(bounds.TopLeft(), bounds.TopRight(), Color::Red);
		args.Graphics->DrawLine(bounds.TopRight(), bounds.BottomRight(), Color::Red);
		args.Graphics->DrawLine(bounds.BottomRight(), bounds.BottomLeft(), Color::Red);
		args.Graphics->DrawLine(bounds.BottomLeft(), bounds.TopLeft(), Color::Red);

		for(UINT i = 0; i < content.Count(); i++)
		{
			Vector3 pos = content[i]->PRS.GPosition();

			args.Graphics->DrawLine(pos - Vector3::UnitX, pos + Vector3::UnitX, Color::Green);
			args.Graphics->DrawLine(pos - Vector3::UnitY, pos + Vector3::UnitY, Color::Green);
			args.Graphics->DrawLine(pos - Vector3::UnitZ, pos + Vector3::UnitZ, Color::Green);
		}

		for(UINT i = 0; i < childs.Count(); i++)
			childs[i]->Draw(args);
#endif
	}

	bool QuadtreeNode::CreateSubdivision()
	{
		if(layerDepth == 0)
			return false;

		float x = this->bounds.X;
		float y = this->bounds.Y;
		float halfWidth = this->bounds.Width / 2;
		float halfHeight = this->bounds.Height / 2;

		childs.Add(new QuadtreeNode(RectangleF::Create(x, y, halfWidth, halfHeight), layerDepth - 1));
		childs.Add(new QuadtreeNode(RectangleF::Create(x + halfWidth, y, halfWidth, halfHeight), layerDepth - 1));
		childs.Add(new QuadtreeNode(RectangleF::Create(x , y + halfHeight, halfWidth, halfHeight), layerDepth - 1));
		childs.Add(new QuadtreeNode(RectangleF::Create(x + halfWidth, y + halfHeight, halfWidth, halfHeight), layerDepth - 1));

		return true;
	}

	RectangleF& QuadtreeNode::Bounds()
	{
		return this->bounds;
	}

	List<GameObject*>& QuadtreeNode::Content()
	{
		return this->content;
	}

	void QuadtreeNode::SubContent(List<GameObject*>& result)
	{
		for(UINT i = 0; i < childs.Count(); i++)
			childs[i]->SubContent(result);

		result.AddRange(this->content.GetInternalData(), 0, this->content.Count());
	}

	void QuadtreeNode::Intersects(List<GameObject*>& result, RectangleF& rect)
	{
		for(UINT i = 0; i < content.Count(); i++)
		{
			if(content[i]->Bounds().Collide(rect) == Intersect)
				result.Add(content[i]);
		}
		
		for(UINT i = 0; i < childs.Count(); i++)
		{
			QuadtreeNode* node = childs[i];

			if(node->IsEmpty())
				continue;

			//rect inside one child

			if(node->Bounds().Collide(rect) == Contain)
			{
				node->Intersects(result, rect);
				break;
			}

			//rect contains child - add child subcontent
			if(rect.Collide(node->Bounds()) == Contain)
			{
				node->SubContent(result);
				continue;
			}

			if(node->Bounds().Collide(rect) == Intersect)
			{
				node->Intersects(result, rect);
			}
		}
	}

	bool QuadtreeNode::IsEmpty()
	{
		return this->content.Count() == 0 && this->childs.Count() == 0;
	}

#pragma endregion
}