
#include "Core\Scene.h"

namespace TikiEngine
{
	#pragma region Class
	Scene::Scene(Engine* engine)
		: EngineObject(engine), elements(), mainCamera(0)
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

	#pragma region Member
	Camera* Scene::GetMainCamera()
	{
		return mainCamera;
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

		UInt32 len = 0;
		ILight** comLights = 0;
		Camera** comCameras = 0;

		element->GetComponents<ILight>(&comLights, &len);
		if (comLights) lights.AddRange(comLights, 0, len);
		delete(comLights);

		element->GetComponents<Camera>(&comCameras, &len);
		if (comCameras) cameras.AddRange(comCameras, 0, len);
		delete(comCameras);

		return element;
	}

	bool Scene::RemoveElement(GameObject* element)
	{
		UInt32 i = 0;
		while (i < lights.Count())
		{
			if (lights[i]->GetGameObject() == element) lights.Remove(lights[i]);
			i++;
		}

		i = 0;
		while (i < cameras.Count())
		{
			if (cameras[i]->GetGameObject() == element) cameras.Remove(cameras[i]);
			i++;
		}

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