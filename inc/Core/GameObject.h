#pragma once

#include "Core/Engine.h"
#include "Core/EngineObject.h"
#include "Core/Transform.h"
#include "Core/IComponent.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"
#include "Core/InitializationArgs.h"

namespace TikiEngine
{
	using namespace TikiEngine::Components;

	class GameObject : public EngineObject
	{
	public:

		Transform PRS;

		GameObject(Engine* engine)
			: EngineObject(engine)
		{
		}
		virtual ~GameObject() {}

		virtual void Initialize(const InitializationArgs& args) = 0;

		virtual void Draw(const DrawArgs& args) = 0;
		virtual void Update(const UpdateArgs& args) = 0;

	protected:

		List<IComponent*> components;
	};
}

