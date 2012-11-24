
#include "Core/GameObject.h"
#include "Core/TypeGlobals.h"
#include <typeinfo.h>

namespace TikiEngine
{
	#pragma region Class
	GameObject::GameObject(Engine* engine)
		: EngineObject(engine), PRS(), components(), model(0)
	{
		this->PRS = Transform(this);
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
		if (model && model->GetReady()) model->Draw(this, args);

		for (UInt32 i = 0; i < components.Count(); i++)
		{
			components[i]->Draw(args);
		}
	}

	void GameObject::Update(const UpdateArgs& args)
	{
		if (model && model->GetReady()) model->Update(args);

		for (UInt32 i = 0; i < components.Count(); i++)
		{
			components[i]->Update(args);
		}
	}
	#pragma endregion
	
}
