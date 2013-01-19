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
		//for(UINT i = 0; i < data.Count(); i++)
		//{
		//	SafeRelease(&data[i]);
		//}

		for(UINT i = 0; i < childs.Count(); i++)
		{
			SafeDelete(&childs[i]);
		}
	}

	bool SceneGraphNode::Add(GameObject* gameObject)
	{
		for(UINT i = 0; i < childs.Count(); i++)
		{
			if(childs[i]->Bounds().Collide(gameObject->GetSceneGraphElement().Bounds) == Contain)
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
				if(childs[i]->Bounds().Collide(gameObject->GetSceneGraphElement().Bounds) == Contain)
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

	void SceneGraphNode::Find(List<GameObject*>& result, RectangleF& rect, Vector3& point, 
		float distance, function<bool(GameObject*)> where)
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			GameObject* go = data[i];

			if(go->GetSceneGraphElement().Bounds.Collide(rect) == Intersect)
			{
				if(Vector3::DistanceSquared(point, go->PRS.GPosition()) < distance * distance)
				{
					if(where == 0)
						result.Add(go);
					else if(where(go))
						result.Add(go);
				}
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

	void SceneGraphNode::Find(List<GameObject*>& result, RectangleF& rect, function<bool(GameObject*)> where)
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			GameObject* go = data[i];

			if(go->GetSceneGraphElement().Bounds.Collide(rect) == Intersect)
			{
				if(where == 0 || where(go))
				{
					result.Add(go);
				}
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

	void SceneGraphNode::Find(List<GameObject*>& result, function<bool(GameObject*)> where)
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			GameObject* go = data[i];

			if(where == 0)
				result.Add(go);
			else if(where(go))
				result.Add(go);
		}

		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
			{
				childs[i]->Find(result, where);
			}
		}
	}

	void SceneGraphNode::Do(function<void(GameObject*)> whatIWant)
	{
		for(UINT i = 0; i < data.Count(); i++)
			whatIWant(data[i]);
		
		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
				childs[i]->Do(whatIWant);
		}
	}

	void SceneGraphNode::DoWithinRange(RectangleF& rect, const Vector3& point, float distance, function<void(GameObject*)> whatIWant)
	{
		for(UINT i = 0; i < data.Count(); i++)
		{
			GameObject* go = data[i];

			if(go->GetSceneGraphElement().Bounds.Collide(rect) == Intersect)
			{
				if(Vector3::DistanceSquared(point, go->PRS.GPosition()) < distance * distance)
				{
					whatIWant(go);
				}
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
					node->DoWithinRange(rect, point, distance, whatIWant);
					break;
				}

				if(rect.Collide(node->Bounds()) == Contain)
				{
					node->Do(whatIWant);
					continue;
				}

				if(node->Bounds().Collide(rect) == Intersect)
				{
					node->DoWithinRange(rect, point, distance, whatIWant);
				}
			}
		}
	}

	void SceneGraphNode::Find(List<GameObject*>& result, Frustum& frustum)
	{
		GetContent(result);

		//for(UINT i = 0; i < data.Count(); i++)
		//{
		//	GameObject* go = data[i];
		//	if(frustum.RectangleInFrustum(go->Bounds(), go->PRS.GPosition().Y))
		//		result.Add(go);
		//}

		if(IsSubdivided())
		{
			for(UINT i = 0;  i < childs.Count(); i++)
			{
				if(frustum.RectangleInFrustum(childs[i]->Bounds(),0) != Frustum::OUTSIDE)
					childs[i]->Find(result, frustum);
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
		for(UInt32 i = 0; i < data.Count(); i++)
		{
			GameObject* go = data[i];

			if(go->PRS.IsSGDirty())
			{
				UpdatePosition(go);
				go->PRS.MarkAsSGClean();
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

	void SceneGraphNode::PerformCulling(Frustum& frustum)
	{
		//for(UINT i = 0; i < data.Count(); i++)
		//	data[i]->GetSceneGraphElement().PerformFrustumCulling(frustum);
		//if(IsSubdivided())
		//{
		//	for(UINT i = 0; i < childs.Count(); i++)
		//		childs[i]->PerformCulling(frustum);
		//}
	}

	void SceneGraphNode::Draw(const DrawArgs& args)
	{
		//for(UINT i = 0; i < data.Count(); i++)
		//	data[i]->Draw(args);

		//if(IsSubdivided())
		//{
		//	for(UINT i = 0; i < childs.Count(); i++)
		//		childs[i]->Draw(args);
		//}
	}

	void SceneGraphNode::DebugDraw(const DrawArgs& args)
	{
#if _DEBUG
		float height = 0;
		args.Graphics->DrawLine(bounds.TopLeft(height), bounds.TopRight(height), Color::Red);
		args.Graphics->DrawLine(bounds.TopRight(height), bounds.BottomRight(height), Color::Red);
		args.Graphics->DrawLine(bounds.BottomRight(height), bounds.BottomLeft(height), Color::Red);
		args.Graphics->DrawLine(bounds.BottomLeft(height), bounds.TopLeft(height), Color::Red);

		for(UINT i = 0; i < data.Count(); i++)
		{
			RectangleF rec = data[i]->GetSceneGraphElement().Bounds;
			float h = 0;//data[i]->PRS.GPosition().Y;

			args.Graphics->DrawLine(rec.TopLeft(h), rec.TopRight(h), Color::Green);
			args.Graphics->DrawLine(rec.TopRight(h), rec.BottomRight(h), Color::Green);
			args.Graphics->DrawLine(rec.BottomRight(h), rec.BottomLeft(h), Color::Green);
			args.Graphics->DrawLine(rec.BottomLeft(h), rec.TopLeft(h), Color::Green);

		}

		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
				childs[i]->DebugDraw(args);
		}
#endif
	}

	bool SceneGraphNode::UpdatePosition(GameObject* go)
	{
		if(this->bounds.Collide(go->GetSceneGraphElement().Bounds) == Contain)
		{
			return this->Add(go);
		}
		else
		{
			this->parent->childDataCount--;
			return this->parent->UpdatePosition(go);
		}
	}

	SceneGraphNode* SceneGraphNode::Find(GameObject* gameObject)
	{
		return 0;
	}

	void SceneGraphNode::GetContent(List<GameObject*>& content, function<bool(GameObject*)> where)
	{
		if(where != 0)
		{
			for(UINT i = 0; i < this->data.Count(); i++)
			{
				GameObject* go = data[i];

				if(where == 0)
					content.Add(go);
				else if(where(go))
					content.Add(go);
			}
		}
		else
		{
			content.AddRange(this->data.GetInternalData(),0, this->data.Count());
		}
	}

	void SceneGraphNode::GetSubContent(List<GameObject*>& content, function<bool(GameObject*)> where)
	{
		GetContent(content, where);

		if(IsSubdivided())
		{
			for(UINT i = 0; i < childs.Count(); i++)
				childs[i]->GetSubContent(content, where);
		}
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
		return this->data.Count() == 0 && !IsSubdivided();
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
