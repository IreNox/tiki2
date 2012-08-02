#pragma once

#include "Core/TypeInc.h"
#include "Core/GameObject.h"
#include "Core/EngineObject.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"
#include "Core/InitializationArgs.h"

#include <Core/List.h>

namespace TikiEngine
{
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

		Camera* GetMainCamera();

	protected:

		Camera* mainCamera;
		List<GameObject*> elements;
	};
}