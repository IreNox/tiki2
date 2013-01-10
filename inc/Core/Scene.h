#pragma once



#include "Core/TypeInc.h"
#include "Core/GameObject.h"
#include "Core/EngineObject.h"

#include "Core/Light.h"
#include "Core/Camera.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"
#include "Core/DrawLightArgs.h"
#include "Core/InitializationArgs.h"
#include "Core/SceneGraph.h"

#include <Core/List.h>

namespace TikiEngine
{
	using namespace TikiEngine::Components;

	class Scene : public EngineObject
	{
	public:

		TikiEngine::SceneGraph SceneGraph;

		Scene(Engine* engine);
		~Scene();

		GameObject* AddElement(GameObject* element);
		GameObject* RemoveElement(GameObject* element);

		bool IsInitialized();
		virtual void Initialize(const InitializationArgs& args);

		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);

		DrawLightArgs& GetLighting();
		List<Camera*>* GetCameras();
		inline Camera* GetMainCamera() { return mainCamera; }

	protected:
		
		bool initialized;

		List<Camera*> cameras;
		Camera* mainCamera;

		DrawLightArgs lighting;
		List<GameObject*> drawContent;
	};
}
