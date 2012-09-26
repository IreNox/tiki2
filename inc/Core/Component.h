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

			Component(Engine* engine, GameObject* gameObject, ComponentType type);
			virtual ~Component();

			virtual void Draw(const DrawArgs& args) = 0;
			virtual void Update(const UpdateArgs& args) = 0;

			GameObject* GetGameObject();
			ComponentType GetType();

			virtual bool GetReady() = 0;

		protected:

			ComponentType type;
			GameObject* gameObject;

		};
	}
}