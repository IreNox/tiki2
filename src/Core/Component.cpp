
#include "Core/Component.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace Components
	{
		Component::Component(Engine* engine, GameObject* gameObject, ComponentType type)
			: EngineObject(engine), gameObject(gameObject), type(type)
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

		ComponentType Component::GetType()
		{
			return type;
		}
	}
}