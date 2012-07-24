#pragma once

#include "Core/EngineObject.h"

#include "Core/ComponentType.h"

namespace TikiEngine
{
	class GameObject;

	namespace Components
	{
		class IComponent : public EngineObject
		{
		public:

			IComponent(Engine* engine, GameObject* gameObject, ComponentType type)
				: EngineObject(engine), gameObject(gameObject), type(type)
			{
			}
			virtual ~IComponent() {}

			GameObject* GetGameObject()
			{
				return gameObject;
			}

			ComponentType GetType()
			{
				return type;
			}

		protected:

			GameObject* gameObject;

			ComponentType type;
		};
	}
}