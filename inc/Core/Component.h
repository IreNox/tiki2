#pragma once

#include "Core/EngineObject.h"

#include "Core/ComponentType.h"

namespace TikiEngine
{
	class GameObject;

	namespace Components
	{
		class Component : public EngineObject
		{
		public:

			Component(Engine* engine, GameObject* gameObject, ComponentType type)
				: EngineObject(engine), gameObject(gameObject), type(type)
			{
			}
			virtual ~Component() {}

			virtual void Draw(const DrawArgs& args) = 0;
			virtual void Update(const UpdateArgs& args) = 0;

			GameObject* GetGameObject()
			{
				return gameObject;
			}

			ComponentType GetType()
			{
				return type;
			}

			virtual bool GetReady() = 0;

		protected:

			GameObject* gameObject;

			ComponentType type;
		};
	}
}