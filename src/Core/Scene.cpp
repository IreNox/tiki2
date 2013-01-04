

#include "Core\Scene.h"

#include "Core\IGraphics.h"
#include "Core\ISpriteBatch.h"



namespace TikiEngine
{
	#pragma region Class
	Scene::Scene(Engine* engine)
		: EngineObject(engine), elements(), lighting(true, new List<Light*>(), -1, LightProperties()), cameras(), initialized(false)
	{
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
	DrawLightArgs& Scene::GetLighting()
	{
		UInt32 i = 0;
		bool dirty = false;
		while (i < lighting.SceneLights->Count())
		{
			if (lighting.SceneLights->Get(i)->GetGameObject()->PRS.IsDirty())
			{
				lighting.SceneLights->Get(i)->GetGameObject()->PRS.MarkAsClean();
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
	bool Scene::IsInitialized()
	{
		return initialized;
	}

	void Scene::Initialize(const InitializationArgs& args)
	{
		#if _DEBUG
		if (initialized) throw "Scene already initialized.";
		#endif

		initialized = true;
	}
	#pragma endregion

	#pragma region Member - Elements
	 GameObject* Scene::AddElement(GameObject* element)
	{
#if TIKI_USE_SCENEGRAPH
		SceneGraph.Add(element);
#endif

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

		if (lighting.SceneLights->Count())
		{
			lighting.MainLightIndex = 0;
		}

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
		
#if TIKI_USE_SCENEGRAPH
		SceneGraph.Remove(element);
#endif

		return elements.Remove(element);
	}
	#pragma endregion

	#pragma region Member - Draw/Update
	void Scene::Draw(const DrawArgs& args)
	{
#if TIKI_USE_SCENEGRAPH

		//drawContent.Clear();
		//SceneGraph.Find(drawContent, GetCameras()->Get(0)->GetFrustum());
		//for(UINT i = 0; i < drawContent.Count(); i++)
		//	drawContent[i]->Draw(args);

		//engine->HLog.Write("" + drawContent.Count());

		SceneGraph.Draw(args);

#else
		for (UInt32 i = 0; i < elements.Count(); i++)
		{
			elements[i]->Draw(args);
		}
#endif
	}

	void Scene::Update(const UpdateArgs& args)
	{
#if TIKI_USE_SCENEGRAPH
			SceneGraph.Update(args);
#else
		for (UInt32 i = 0; i < elements.Count(); i++)
		{
			elements[i]->Update(args);
		}
#endif
	}
	#pragma endregion
}