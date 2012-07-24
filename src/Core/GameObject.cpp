
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
}