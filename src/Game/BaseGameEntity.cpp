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
			boundingRadius *= MaxOf(MaxOf(val.X, val.Y), val.Z) /
							  MaxOf(MaxOf(GetGameObject()->PRS.Scale.X, 
										  GetGameObject()->PRS.Scale.Y), 
										  GetGameObject()->PRS.Scale.Z); 
			GetGameObject()->PRS.Scale = val;
		}

		void BaseGameEntity::SetScale(float val)
		{
			boundingRadius *= (val / MaxOf(MaxOf(GetGameObject()->PRS.Scale.X, 
												 GetGameObject()->PRS.Scale.Y),
												 GetGameObject()->PRS.Scale.Z)); 
			GetGameObject()->PRS.Scale = Vector3(val);
		}

	}
}