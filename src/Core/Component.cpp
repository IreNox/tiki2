
#include "Core/Component.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace Components
	{
		Component::Component(Engine* engine, GameObject* gameObject)
			: EngineObject(engine), gameObject(gameObject)
		{
			gameObject->components.Add(this);
			this->AddRef();
		}

		Component::~Component()
		{
		}

		GameObject* Component::GetGameObject()
		{
			return gameObject;
		}
	}
}