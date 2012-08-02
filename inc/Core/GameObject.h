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

		#pragma region Member - GetElement
		template <class T>
		Component* GetComponent()
		{
			return this->GetComponent(
				typeid(T).hash_code()
			);
		}

		template <class T>
		void GetComponents(T*** dest, UInt32* length)
		{
			List<T*> coms = List<T*>();

			int i = 0;
			PInt hash = typeid(T).hash_code();
			while (i < components.Count())
			{
				if (typeid(components[i]).hash_code() == hash)
				{
					coms.Add((T*)components[i]);
				}
				i++;
			}

			*length = coms.Count();
			*dest = (*length != 0 ? coms.ToArray() : 0);
		}
		#pragma endregion

		bool RemoveComponent(Component* comp);

	protected:

		List<Component*> components;
	};
}

