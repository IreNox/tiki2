#pragma once

#include "Core/ICollider.h"

namespace TikiEngine
{
	namespace Components
	{
		class IBoxCollider : public ICollider
		{
		public:
			IBoxCollider(Engine* engine, GameObject* gameObject)
				:ICollider(engine, gameObject) {}
			virtual ~IBoxCollider() {}
			
			virtual Vector3 GetCenter() = 0;
			virtual void SetCenter(const Vector3& center) = 0;

			virtual Vector3 GetSize() = 0;
			virtual void SetSize(const Vector3& size) = 0;


		};

	}
}