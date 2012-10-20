#pragma once

#include "Core/EngineObject.h"

namespace TikiEngine
{
	class GameObject;

	namespace Components
	{
		class Component : public EngineObject
		{
		public:

			Component(Engine* engine, GameObject* gameObject);
			virtual ~Component();

			virtual void Draw(const DrawArgs& args) = 0;
			virtual void Update(const UpdateArgs& args) = 0;

			GameObject* GetGameObject();

			virtual bool GetReady() = 0;

		protected:

			GameObject* gameObject;

		};
	}
}