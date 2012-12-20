#include "Core/SceneGraphNode.h"

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

	}

	void SceneGraphNode::Insert(GameObject* gameObject)
	{
		if(Subdivide())
		{
			for(UINT i = 0; i < 4; i++)
			{
				if(childs[i]->Bounds().Collide(gameObject->Bounds()) == Contain)
				{
					childs[i]->Insert(gameObject);
					return;
				}
			}
		}
		gameObject->AddRef();
		this->data.Add(gameObject);
	}

	void SceneGraphNode::Remove(GameObject* gameObject)
	{

	}

	SceneGraphNode* SceneGraphNode::Find(GameObject* gameObject)
	{

	}

	void SceneGraphNode::GetContent(List<GameObject*> content)
	{

	}

	void SceneGraphNode::GetSubContent(List<GameObject*> content)
	{

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