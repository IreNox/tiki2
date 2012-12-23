
#include "Core/GameObject.h"
#include "Core/TypeGlobals.h"
#include <typeinfo.h>

namespace TikiEngine
{
	#pragma region Class
	GameObject::GameObject(Engine* engine)
		: EngineObject(engine), PRS(), components(), model(0), parent(0), childs()
	{
		this->PRS = Transform(this);
		this->bounding.X = PRS.GPosition().X;
		this->bounding.Y = PRS.GPosition().Z;
		this->bounding.Width = 1;
		this->bounding.Height = 1;
	}

	GameObject::~GameObject()
	{
		SafeRelease(&model);

		for (UInt32 i = 0; i < components.Count(); i++)
		{
			components[i]->Release();
		}
	}
	#pragma endregion

	#pragma region Member - Model
	IModel* GameObject::GModel() const
	{
		return model;
	}

	void GameObject::SModel(IModel* model)
	{
		SafeRelease(&this->model);
		SafeAddRef(model, &this->model);
	}
	#pragma endregion

	#pragma region Member - Childs
	GameObject* GameObject::GParent()
	{
		return parent;
	}

	void GameObject::AddChild(GameObject* gameObject)
	{
		gameObject->parent = this;
		gameObject->AddRef();

		childs.Add(gameObject);
	}

	bool GameObject::RemoveChild(GameObject* gameObject)
	{
		if (childs.Remove(gameObject))
		{
			gameObject->Release();
			return true;
		}

		return false;
	}

	const List<GameObject*>& GameObject::Childs()
	{
		return childs;
	}
	#pragma endregion

	#pragma region Member - Component
	Component* GameObject::GetComponent(PInt hash)
	{
		UInt32 i = 0;
		UInt32 c = components.Count();
		while (i < c)
		{
			PInt curHash = typeid(*components[i]).hash_code();

			if (curHash == hash) return components[i];

			i++;
		}

		return 0;
	}

	bool GameObject::RemoveComponent(Component* comp)
	{
		return components.Remove(comp);
	}
	#pragma endregion

	#pragma region Member - Draw/Update
	void GameObject::Draw(const DrawArgs& args)
	{
		UInt32 i = 0;
		while (i < childs.Count())
		{
			childs[i]->Draw(args);
			i++;
		}

		i = 0;
		while (i < components.Count())
		{
			components[i]->Draw(args);
			i++;
		}

		if (model) model->Draw(this, args);
	}

	void GameObject::Update(const UpdateArgs& args)
	{
		UInt32 i = 0;
		while (i < childs.Count())
		{
			childs[i]->Update(args);
			i++;
		}

		i = 0;
		while (i < components.Count())
		{
			components[i]->Update(args);
			i++;
		}

		if (model) model->Update(args);

		//TODO anständige bounds

		this->bounding.X = PRS.GPosition().X - bounding.Width * 0.5f;
		this->bounding.Y = PRS.GPosition().Z - bounding.Height * 0.5f;
	}
	#pragma endregion

	#pragma region SceneGraph
	RectangleF& GameObject::Bounds()
	{
		return this->bounding;
	}
	#pragma endregion
	
}
