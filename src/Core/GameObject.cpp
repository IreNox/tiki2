
#include "Core/GameObject.h"

namespace TikiEngine
{
	GameObject::GameObject(Engine* engine)
		: EngineObject(engine), components()
	{
	}

	GameObject::~GameObject()
	{
		for (int i = 0; i < components.Count(); i++)
		{
			delete(components[i]);
		}
	}

	bool GameObject::Initialize(const InitializationArgs& args)
	{
		return true;
	}

	void GameObject::Draw(const DrawArgs& args)
	{
		for (int i = 0; i < components.Count(); i++)
		{
			components[i]->Draw(args);
		}
	}

	void GameObject::Update(const UpdateArgs& args)
	{
		for (int i = 0; i < components.Count(); i++)
		{
			components[i]->Update(args);
		}
	}

	void GameObject::AddComponent(Component* comp)
	{
		components.Add(comp);
	}

	Component* GameObject::GetComponent(IntPtr hash)
	{
		int i = 0;
		int c = components.Count();
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