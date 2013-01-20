
#include "Core/GameObject.h"
#include "Core/TypeGlobals.h"
#include <typeinfo.h>

namespace TikiEngine
{
	#pragma region Class
	GameObject::GameObject(Engine* engine)
		: EngineObject(engine), PRS(), components(), model(0), parent(0), childs(), userData(0)
	{
		this->PRS = Transform(this);

#if !TIKI_EDITOR
		this->sgElement.SetGameObject(this);
#endif
	}

	GameObject::~GameObject()
	{
		if (userData != 0)
		{
			TikiObject* to1 = (TikiObject*)userData;
			TikiObject* to2 = dynamic_cast<TikiObject*>(to1);

			if (to2 != 0) to2->Release();
		}

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
		SafeChangeRef(&this->model, model);

		if (model)
		{
			Matrix mat;
			Vector3 bound = model->GetBounds();
			//this->PRS.FillWorldMatrix(&mat);
			//mat = mat.RotationKernel();

			mat = Matrix::CreateScaleMatrix(this->PRS.scale);
			bound = Matrix::TransformCoordinate(bound, mat);

			if (bound.X > 50 || bound.Z > 50)
			{
				mat = Matrix::CreateScaleMatrix(Vector3(0.01f));
				bound = Matrix::TransformCoordinate(model->GetBounds(), mat);
			}

			sgElement.SetBounds(
				bound.XZ()
			);
		}
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
		
        if (model) model->Draw(this, args);

		i = 0;
		while (i < components.Count())
		{
			components[i]->Draw(args);
			i++;
		}

		//sgElement.boundingBox->DrawDebug(Color::Red);
	}

	void GameObject::Update(const UpdateArgs& args)
	{
#if !TIKI_EDITOR
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

		this->sgElement.Update(args);
#endif
	}

	void GameObject::LateUpdate(const UpdateArgs& args)
	{
#if !TIKI_EDITOR
		if(!sgElement.IsCulled && model)
		{
			model->LateUpdate(args);
		}
#endif
	}
	#pragma endregion
}
