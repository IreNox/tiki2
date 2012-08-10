
#include "Core/GameObject.h"

namespace TikiEngine
{
	GameObject::GameObject(Engine* engine)
		: EngineObject(engine), components()
	{
	}

	GameObject::~GameObject()
	{
		for (UInt32 i = 0; i < components.Count(); i++)
		{
			components[i]->Release();
		}
	}

	void GameObject::Draw(const DrawArgs& args)
	{
		for (UInt32 i = 0; i < components.Count(); i++)
		{
			components[i]->Draw(args);
		}
	}

	void GameObject::Update(const UpdateArgs& args)
	{
		for (UInt32 i = 0; i < components.Count(); i++)
		{
			components[i]->Update(args);
		}
	}

	void GameObject::AddComponent(Component* comp)
	{
		components.Add(comp);
		comp->AddRef();
	}

	Component* GameObject::GetComponent(IntPtr hash)
	{
		UInt32 i = 0;
		UInt32 c = components.Count();
		while (i < c)
		{
			if ( typeid(components[i]).hash_code() == hash) return components[i];

			i++;
		}

		return 0;
	}

	bool GameObject::RemoveComponent(Component* comp)
	{
		return components.Remove(comp);
	}
}