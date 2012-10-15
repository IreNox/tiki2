#include "Game/BaseGameEntity.h"

#include <cassert>

namespace TikiEngine
{
	namespace AI
	{
		int BaseGameEntity::nextValidID = 0;

		BaseGameEntity::BaseGameEntity(GameState* gameState, GameObject* gameObject)
			: Component(gameState->GetEngine(), gameObject, CT_AI), gameState(gameState)
		{
			id = nextValidID++;

			boundingRadius = 0.0;
            type = default_entity_type;
            tag = false;
		}

		void BaseGameEntity::SetScale(Vector3 val)
		{
			Vector3 scale = this->GetGameObject()->PRS.Scale();

			boundingRadius *= MaxOf(MaxOf(val.X, val.Y), val.Z) /
				MaxOf(MaxOf(scale.X, 
				scale.Y), 
				scale.Z); 
			GetGameObject()->PRS.Scale() = val;
		}

		void BaseGameEntity::SetScale(float val)
		{
			Vector3 scale = this->GetGameObject()->PRS.Scale();

			boundingRadius *= (val / MaxOf(MaxOf(scale.X, 
												 scale.Y),
												 scale.Z)); 
			GetGameObject()->PRS.Scale() = val;
		}

	}
}