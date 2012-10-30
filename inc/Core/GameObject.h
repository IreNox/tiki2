#pragma once

#include "Core/Engine.h"
#include "Core/EngineObject.h"
#include "Core/Transform.h"
#include "Core/Component.h"
#include "Core/Material.h"
#include "Core/IModel.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"

namespace TikiEngine
{
	using namespace TikiEngine::Resources;
	using namespace TikiEngine::Components;

	class GameObject : public EngineObject
	{
		friend class Component;

	public:

		Transform PRS;

		GameObject(Engine* engine);
		virtual ~GameObject();
		
		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);

		Component* GetComponent(PInt hash);

		#pragma region Member - Get
		template <class T>
		T* GetComponent()
		{
			return (T*)this->GetComponent(
				typeid(T).hash_code()
			);
		}

		template <class T>
		void GetComponents(T*** dest, UInt32* length)
		{
			List<T*> coms = List<T*>();

			UInt32 i = 0;
			PInt hash = typeid(T).hash_code();
			while (i < components.Count())
			{
				PInt objHash = typeid(*components[i]).hash_code();

				if (objHash == hash)
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

		IModel* GModel() const;
		void SModel(IModel* model);

	protected:

		IModel* model;

		List<Component*> components;

	};
}

