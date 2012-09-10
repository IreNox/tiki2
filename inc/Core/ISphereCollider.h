#pragma once

#include "Core/ICollider.h"

namespace TikiEngine
{
	namespace Components
	{
		class ISphereCollider : public ICollider
		{
		public:
			ISphereCollider(Engine* engine, GameObject* gameObject)
				:ICollider(engine, gameObject) {}
			virtual ~ISphereCollider() {}

			/* !@brief The radius of the sphere, measured in the object's local space. */
			virtual Single GetRadius() = 0;
			virtual void SetRadius(Single radius) = 0;
		};

	}
}