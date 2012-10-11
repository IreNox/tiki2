
#include "Core\Scene.h"

#include "Core\IGraphics.h"
#include "Core\ISpriteBatch.h"

#include <ppl.h>

namespace TikiEngine
{
	using namespace Concurrency;

	#pragma region Class
	Scene::Scene(Engine* engine)
		: EngineObject(engine), elements(), lighting(true, new List<Light*>(), -1, LightProperties()), cameras()
	{
#if _DEBUG
		mouse = engine->content->LoadTexture(L"Data/Textures/mouse.png");
#endif
	}

	Scene::~Scene()
	{
		for (UInt32 i = 0; i< elements.Count(); i++)
		{
			elements[i]->Release();
		}

		SafeDelete(&lighting.SceneLights);
	}
	#pragma endregion

	#pragma region Member
	const DrawLightArgs& Scene::GetLighting()
	{
		UInt32 i = 0;
		Boolean dirty = false;
		while (i < lighting.SceneLights->Count())
		{
			if (lighting.SceneLights->Get(i)->GetGameObject()->PRS.IsDirty())
			{
				dirty = true;
				break;
			}

			i++;
		}

		lighting.IsDirty = dirty;		

		return lighting;
	}

	List<Camera*>* Scene::GetCameras()
	{
		return &cameras;
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
		element->AddRef();

		UInt32 len = 0;
		Light** comLights = 0;
		Camera** comCameras = 0;

		element->GetComponents<Light>(&comLights, &len);
		if (comLights) lighting.SceneLights->AddRange(comLights, 0, len);
		delete(comLights);

		element->GetComponents<Camera>(&comCameras, &len);
		if (comCameras) cameras.AddRange(comCameras, 0, len);
		delete(comCameras);

		return element;
	}

	bool Scene::RemoveElement(GameObject* element)
	{
		UInt32 i = 0;
		while (i < lighting.SceneLights->Count())
		{
			if (lighting.SceneLights->Get(i)->GetGameObject() == element) 
			{
				lighting.SceneLights->Remove(lighting.SceneLights->Get(i));
			}
			else
			{
				i++;
			}
		}

		i = 0;
		while (i < cameras.Count())
		{
			if (cameras[i]->GetGameObject() == element) 
			{
				cameras.Remove(cameras[i]);
			}
			else
			{
				i++;
			}
		}

		return elements.Remove(element);
	}
	#pragma endregion

	#pragma region Member - Draw/Update
	void Scene::Draw(const DrawArgs& args)
	{
		for (UInt32 i = 0; i < elements.Count(); i++)
		{
			elements[i]->Draw(args);
		}

#if _DEBUG
		Vector2 mouse2 = args.Update.Input.MousePosition;
		Vector2 viewPort = engine->graphics->GetViewPort()->GetSize();

		engine->sprites->Draw(
			mouse, 
			Vector2(
				mouse2.X * viewPort.X,
				mouse2.Y * viewPort.Y
			)			
		);
#endif
	}

	void Scene::Update(const UpdateArgs& args)
	{
		parallel_for(
			elements.FirstIndex(), elements.Count(),
			[=](UInt32 i){ elements[i]->Update(args); }
		);

		//for (UInt32 i = 0; i < elements.Count(); i++)
		//{
		//	elements[i]->Update(args);
		//}

	}
	#pragma endregion
}