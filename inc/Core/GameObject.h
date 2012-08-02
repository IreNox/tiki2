#pragma once

#include "Core/Engine.h"
#include "Core/EngineObject.h"
#include "Core/Transform.h"
#include "Core/Component.h"
#include "Core/Material.h"

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
		
		virtual bool Initialize(const InitializationArgs& args);
		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);

		void AddComponent(Component* comp);
		Component* GetComponent(IntPtr hash);
		bool RemoveComponent(Component* comp);

	protected:

		List<Component*> components;
	};
}

