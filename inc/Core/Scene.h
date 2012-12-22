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

		Scene(Engine* engine);
		virtual ~Scene();

		GameObject* AddElement(GameObject* element);
		bool RemoveElement(GameObject* element);
		/*void RemoveElementAt(UInt32 index);*/
		inline const List<GameObject*>& GetElements() const
		{
			return elements;
		}

		bool IsInitialized();
		virtual void Initialize(const InitializationArgs& args);

		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);

		DrawLightArgs& GetLighting();
		List<Camera*>* GetCameras();

	protected:

		bool initialized;

		List<GameObject*> elements;

		List<Camera*> cameras;
		DrawLightArgs lighting;

		SceneGraph sceneGraph;

	};
}