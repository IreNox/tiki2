#pragma once

#include "Core/Engine.h"
#include "Core/EngineObject.h"
#include "Core/Transform.h"
#include "Core/Component.h"

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

		GameObject(Engine* engine);
		virtual ~GameObject();

		virtual bool Initialize(const InitializationArgs& args) = 0;

		virtual void Draw(const DrawArgs& args) = 0;
		virtual void Update(const UpdateArgs& args) = 0;

	protected:

		List<Component*> components;
	};
}

