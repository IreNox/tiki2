#include "Game/BaseGameEntity.h"

#include <cassert>

namespace TikiEngine
{
	namespace AI
	{
		int BaseGameEntity::nextValidID = 0;

		BaseGameEntity::BaseGameEntity(Engine* engine, GameObject* gameObject)
			: Component(engine, gameObject, ComponentType::CT_AI)
		{
			id = nextValidID++;

			boundingRadius = 0.0;
            type = default_entity_type;
            tag = false;
		}

		void BaseGameEntity::SetScale(Vector3 val)
		{
			Vector3 scale = this->GetGameObject()->PRS.GetScale();

			boundingRadius *= MaxOf(MaxOf(val.X, val.Y), val.Z) /
				MaxOf(MaxOf(scale.X, 
				scale.Y), 
				scale.Z); 
			GetGameObject()->PRS.SetScale(val);
		}

		void BaseGameEntity::SetScale(float val)
		{
			Vector3 scale = this->GetGameObject()->PRS.GetScale();

			boundingRadius *= (val / MaxOf(MaxOf(scale.X, 
												 scale.Y),
												 scale.Z)); 
			GetGameObject()->PRS.SetScale(Vector3(val));
		}

	}
}