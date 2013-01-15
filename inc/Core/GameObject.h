#pragma once

#include "Core/Engine.h"
#include "Core/EngineObject.h"
#include "Core/Transform.h"
#include "Core/Component.h"
#include "Core/Material.h"
#include "Core/IModel.h"

#include "Core/DrawArgs.h"
#include "Core/UpdateArgs.h"
#include "Core/RectangleF.h"
#include "Core/SceneGraphElement.h"

namespace TikiEngine
{

	using namespace TikiEngine::Resources;
	using namespace TikiEngine::Components;

	class GameObject : public EngineObject
	{
		friend class Transform;
		friend class Component;
		
	public:

		Transform PRS;

		GameObject(Engine* engine);
		virtual ~GameObject();
		
		virtual void Draw(const DrawArgs& args);
		virtual void Update(const UpdateArgs& args);
		virtual void LateUpdate(const UpdateArgs& args);

		Component* GetComponent(PInt hash);

		#pragma region Member - Get
		template <class T>
		T* GetComponent()
		{
			UInt32 i = 0;
			while(i < components.Count())
			{
				T* comp = dynamic_cast<T*>(components[i]);

				if (comp != 0) return comp;

				i++;
			}

			return 0;
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

		GameObject* GParent();
		
		void AddChild(GameObject* gameObject);
		bool RemoveChild(GameObject* gameObject);
		const List<GameObject*>& Childs();

		inline void* GetUserData() { return userData; }
		inline void SetUserData(void* ud) { userData = ud; }

#if !TIKI_EDITOR
		inline SceneGraphElement& GetSceneGraphElement() { return this->sgElement; }
#endif

#if TIKI_USE_SCENEGRAPH
		
		inline GameObjectType& GetGameObjectType() { return this->objectType; }
#endif

	protected:

		GameObject* parent;

		IModel* model;
		List<Component*> components;

		void* userData;

	private:
		
		List<GameObject*> childs;

#if !TIKI_EDITOR
		SceneGraphElement sgElement;
#endif
#if TIKI_USE_SCENEGRAPH
		GameObjectType objectType;
#endif

	};
}

