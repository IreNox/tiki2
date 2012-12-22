#include "Core/SceneGraphNode.h"
#include "Core/IGraphics.h"

namespace TikiEngine
{
	SceneGraphNode::SceneGraphNode()
	{

	}

	SceneGraphNode::SceneGraphNode(RectangleF bounds, int layerDepth, SceneGraphNode* parent)
		: parent(parent), childs(), bounds(bounds), layerDepth(layerDepth), subdivided(false)
	{

	}

	SceneGraphNode::~SceneGraphNode()
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			SafeRelease(&data[i]);
		}

		for(UINT i = 0; i < childs.Count(); i++)
			SafeDelete(&childs[i]);
	}

	void SceneGraphNode::Add(GameObject* gameObject)
	{

		for(UINT i = 0; i < childs.Count(); i++)
		{
			if(childs[i]->Bounds().Collide(gameObject->Bounds()) == Contain)
			{
				childs[i]->Add(gameObject);
				return;
			}
		}
		
		gameObject->AddRef();
		this->data.Add(gameObject);
	}

	bool SceneGraphNode::Remove(GameObject* gameObject)
	{
		return true;
	}

	void SceneGraphNode::Intersects(List<GameObject*>& content, RectangleF& rect)
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			if(data[i]->Bounds().Collide(rect) == Intersect)
				content.Add(data[i]);
		}

		for(UINT i = 0; i < childs.Count(); i++)
		{
			SceneGraphNode* node = childs[i];

			if(node->IsEmpty())
				continue;

			if(node->Bounds().Collide(rect) == Contain)
			{
				node->Intersects(content, rect);
				break;
			}

			if(rect.Collide(node->Bounds()) == Contain)
			{
				node->GetSubContent(content);
				continue;
			}

			if(node->Bounds().Collide(rect) == Intersect)
			{
				node->Intersects(content, rect);
			}
		}
		
	}


	void SceneGraphNode::Update(const UpdateArgs& args)
	{
		for(UINT i = 0; i < data.Count(); i++)
			data[i]->Update(args);


		for(UINT i = 0; i < childs.Count(); i++)
			childs[i]->Update(args);
	}

	void SceneGraphNode::Draw(const DrawArgs& args)
	{
		for(UINT i = 0; i < data.Count(); i++)
			data[i]->Draw(args);


		for(UINT i = 0; i < childs.Count(); i++)
			childs[i]->Draw(args);


#if _DEBUG
		//args.Graphics->DrawLine(bounds.TopLeft(), bounds.TopRight(), Color::Red);
		//args.Graphics->DrawLine(bounds.TopRight(), bounds.BottomRight(), Color::Red);
		//args.Graphics->DrawLine(bounds.BottomRight(), bounds.BottomLeft(), Color::Red);
		//args.Graphics->DrawLine(bounds.BottomLeft(), bounds.TopLeft(), Color::Red);

		//for(UINT i = 0; i < data.Count(); i++)
		//{
		//	Vector3 pos = data[i]->PRS.GPosition();

		//	args.Graphics->DrawLine(pos - Vector3::UnitX, pos + Vector3::UnitX, Color::Green);
		//	args.Graphics->DrawLine(pos - Vector3::UnitY, pos + Vector3::UnitY, Color::Green);
		//	args.Graphics->DrawLine(pos - Vector3::UnitZ, pos + Vector3::UnitZ, Color::Green);
		//}
#endif
	}

	SceneGraphNode* SceneGraphNode::Find(GameObject* gameObject)
	{
		return 0;
	}

	void SceneGraphNode::GetContent(List<GameObject*>& content)
	{
		content.AddRange(this->data.GetInternalData(),0, this->data.Count());
	}

	void SceneGraphNode::GetSubContent(List<GameObject*>& content)
	{
		content.AddRange(this->data.GetInternalData(), 0, this->data.Count());

		if(subdivided)
		{
			for(UINT i = 0; i < 4; i++)
				childs[i]->GetSubContent(content);
		}
	}

	bool SceneGraphNode::Subdivide()
	{
		if(subdivided)
			return true;

		if(!layerDepth)
			return false;
		
		float x = this->Bounds().X;
		float y = this->Bounds().Y;
		float width = this->bounds.Width * 0.5f;
		float height = this->bounds.Height * 0.5f;

		childs[0] = new SceneGraphNode(RectangleF::Create(x ,y , width, height), layerDepth -1, this);
		childs[1] = new SceneGraphNode(RectangleF::Create(x + width,y , width, height), layerDepth -1, this);
		childs[2] = new SceneGraphNode(RectangleF::Create(x ,y + height, width, height), layerDepth -1, this);
		childs[3] = new SceneGraphNode(RectangleF::Create(x + width ,y + height, width, height), layerDepth -1, this);

		return this->subdivided = true;
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