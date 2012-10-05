#pragma once

#include "Core/TypeInc.h"
#include "Core/GameObject.h"
#include "Core/EngineObject.h"

#include "Core/Light.h"
#include "Core/Camera.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"
#include "Core/InitializationArgs.h"

#include <Core/List.h>

namespace TikiEngine
{
	using namespace TikiEngine::Components;

	class Scene : public EngineObject
	{
	public:
		Scene(Engine* engine);
		virtual ~Scene();

		GameObject* AddElement(GameObject* element);
		bool RemoveElement(GameObject* element);

		virtual void Initialize(const InitializationArgs& args);

		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);

		List<Light*>* GetLights();
		List<Camera*>* GetCameras();

	protected:

		List<GameObject*> elements;

		List<Light*> lights;
		List<Camera*> cameras;

#if _DEBUG
		ITexture* mouse;
#endif

	};
}