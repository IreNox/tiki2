
#include "Core\Scene.h"

namespace TikiEngine
{
	#pragma region Init
	Scene::Scene(Engine* engine)
		: EngineObject(engine), elements()
	{
	}

	Scene::~Scene()
	{
		for (int i = 0; i< elements.Count(); i++)
		{
			delete(elements[i]);
		}
	}
	#pragma endregion

	#pragma region Member - Init
	void Scene::Initialize(const InitializationArgs& args)
	{
	}
	#pragma endregion

	#pragma region Member - Elements
	GameObject* Scene::AddElement(GameObject* element)
	{
		elements.Add(element);

		return element;
	}

	bool Scene::RemoveElement(GameObject* element)
	{
		return elements.Remove(element);
	}
	#pragma endregion

	#pragma region Member - Draw/Update
	void Scene::Draw(const DrawArgs& args)
	{
		for (int i = 0; i < elements.Count(); i++)
		{
			elements[i]->Draw(args);
		}
	}

	void Scene::Update(const UpdateArgs& args)
	{
		for (int i = 0; i < elements.Count(); i++)
		{
			elements[i]->Update(args);
		}

	}
	#pragma endregion
}