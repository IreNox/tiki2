#include "Core/SceneGraphNode.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	SceneGraphNode::SceneGraphNode()
		:bounds(), subdivided(false), layerDepth(0), parent(0), childDataCount(0)
	{

	}

	void SceneGraphNode::Initialize(RectangleF bounds, int layerDepth, SceneGraphNode* parent)
	{
		this->bounds = bounds;
		this->layerDepth = layerDepth;
		this->parent = parent;
		this->subdivide();
	}


	SceneGraphNode::~SceneGraphNode()
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			SafeRelease(&data[i]);
		}

		for(UINT i = 0; i < childs.Count(); i++)
		{
			SafeDelete(&childs[i]);
		}
	}

	bool SceneGraphNode::Add(GameObject* gameObject)
	{
		for(UINT i = 0; i < childs.Count(); i++)
		{
			if(childs[i]->Bounds().Collide(gameObject->Bounds()) == Contain)
			{
				childDataCount++;
				return childs[i]->Add(gameObject);
			}
		}

		this->data.Add(gameObject);
		return true;
	}

	bool SceneGraphNode::Remove(GameObject* gameObject)
	{
		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
			{
				if(childs[i]->Bounds().Collide(gameObject->Bounds()) == Contain)
				{
					this->childDataCount--;
					return childs[i]->Remove(gameObject);
				}
			}
		}

		if(data.Contains(gameObject))
		{
			data.Remove(gameObject);
			return true;
		}
		return false;
	}

	void SceneGraphNode::Find(List<GameObject*>& result, RectangleF& rect)
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			if(data[i]->Bounds().Collide(rect) == Intersect)
				result.Add(data[i]);
		}

		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
			{
				SceneGraphNode* node = childs[i];

				if(node->IsEmpty())
					continue;

				if(node->Bounds().Collide(rect) == Contain)
				{
					node->Find(result, rect);
					break;
				}

				if(rect.Collide(node->Bounds()) == Contain)
				{
					node->GetSubContent(result);
					continue;
				}

				if(node->Bounds().Collide(rect) == Intersect)
				{
					node->Find(result, rect);
				}
			}
		}
	}

	void SceneGraphNode::Find(List<GameObject*>& result, RectangleF& rect, bool(where)(GameObject*))
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			GameObject* go = data[i];

			if(go->Bounds().Collide(rect) == Intersect)
			{
				if(where(go))
					result.Add(go);
			}
		}

		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
			{
				SceneGraphNode* node = childs[i];

				if(node->IsEmpty())
					continue;

				if(node->Bounds().Collide(rect) == Contain)
				{
					node->Find(result, rect, where);
					break;
				}

				if(rect.Collide(node->Bounds()) == Contain)
				{
					node->GetSubContent(result, where);
					continue;
				}

				if(node->Bounds().Collide(rect) == Intersect)
				{
					node->Find(result, rect, where);
				}
			}
		}
	}


	void SceneGraphNode::Update(const UpdateArgs& args)
	{
		for(UINT i = 0; i < data.Count(); i++)
			data[i]->Update(args);

		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
				childs[i]->Update(args);
		}
	}

	void SceneGraphNode::LateUpdate(const UpdateArgs& args)
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			GameObject* go = data[i];
			if(UpdatePosition(go))
			{
				this->data.Remove(go);
				i--;
			}
		}

		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
				childs[i]->LateUpdate(args);
		}
	}

	void SceneGraphNode::Draw(const DrawArgs& args)
	{

		for(UINT i = 0; i < data.Count(); i++)
			data[i]->Draw(args);

		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
				childs[i]->Draw(args);
		}

#if _DEBUG
		args.Graphics->DrawLine(bounds.TopLeft(), bounds.TopRight(), Color::Red);
		args.Graphics->DrawLine(bounds.TopRight(), bounds.BottomRight(), Color::Red);
		args.Graphics->DrawLine(bounds.BottomRight(), bounds.BottomLeft(), Color::Red);
		args.Graphics->DrawLine(bounds.BottomLeft(), bounds.TopLeft(), Color::Red);

		for(UINT i = 0; i < data.Count(); i++)
		{
			RectangleF rec = data[i]->Bounds();

			args.Graphics->DrawLine(rec.TopLeft(), rec.TopRight(), Color::Green);
			args.Graphics->DrawLine(rec.TopRight(), rec.BottomRight(), Color::Green);
			args.Graphics->DrawLine(rec.BottomRight(), rec.BottomLeft(), Color::Green);
			args.Graphics->DrawLine(rec.BottomLeft(), rec.TopLeft(), Color::Green);

		}
#endif
	}

	bool SceneGraphNode::UpdatePosition(GameObject* go)
	{
		if(!this->bounds.Collide(go->Bounds()) == Contain)
		{
			return parent->UpdatePosition(go);
		}
		else
		{
			for(UINT i = 0; i < childs.Count(); i++)
			{
				SceneGraphNode* node = childs[i];
				if(node->Bounds().Collide(go->Bounds()) == Contain)
				{
					return node->Add(go);
				}
			}
		}
		return false;
	}

	SceneGraphNode* SceneGraphNode::Find(GameObject* gameObject)
	{
		return 0;
	}

	void SceneGraphNode::GetContent(List<GameObject*>& content, bool (where)(GameObject*))
	{
		if(where != 0)
		{
			for(UINT i = 0; i < this->data.Count(); i++)
			{
				
				GameObject* go = data[i];
				if(where(go))
					content.Add(go);
			}
		}
		else
		{
			content.AddRange(this->data.GetInternalData(),0, this->data.Count());
		}
	}

	void SceneGraphNode::GetSubContent(List<GameObject*>& content, bool (where)(GameObject*))
	{
		GetContent(content, where);

		for(UINT i = 0; i < childs.Count(); i++)
			childs[i]->GetSubContent(content, where);
	}

	bool SceneGraphNode::Subdivide()
	{
		if(subdivided)
			return true;

		if(!layerDepth)
			return false;

		return this->subdivided = true;
	}

	void SceneGraphNode::subdivide()
	{
		if(!this->layerDepth)
			return;

		float x = this->Bounds().X;
		float y = this->Bounds().Y;
		float width = this->bounds.Width * 0.5f;
		float height = this->bounds.Height * 0.5f;

		SceneGraphNode* node = new SceneGraphNode();
		node->Initialize(RectangleF::Create(x ,y , width, height), this->layerDepth -1, this);
		childs.Add(node);

		node = new SceneGraphNode();
		node->Initialize(RectangleF::Create(x + width,y , width, height), layerDepth -1, this);
		childs.Add(node);

		node = new SceneGraphNode();
		node->Initialize(RectangleF::Create(x ,y + height, width, height), layerDepth -1, this);
		childs.Add(node);

		node = new SceneGraphNode();
		node->Initialize(RectangleF::Create(x + width ,y + height, width, height), layerDepth -1, this);
		childs.Add(node);
	}

	bool SceneGraphNode::IsEmpty()
	{
		return this->data.Count() == 0 && !subdivided;
	}

	RectangleF& SceneGraphNode::Bounds()
	{
		return this->bounds;
	}

	int SceneGraphNode::Count()
	{
		int count = this->data.Count();

		if(subdivided)
		{
			for(UINT i = 0; i < 4; i++)
				count += childs[i]->Count();
		}

		return count + this->data.Count();	
	}
}