#include "Game/BaseGameEntity.h"

#include <cassert>

namespace TikiEngine
{
	namespace AI
	{
		int BaseGameEntity::nextValidID = 0;

		BaseGameEntity::BaseGameEntity(Engine* engine, int ID) : GameObject(engine)
		{
			boundingRadius = 0.0;
			scale = Vector3::One;
            type = default_entity_type;
            tag = false;

			SetID(ID);
		}

		void BaseGameEntity::SetID(int val)
		{
		  //make sure the val is equal to or greater than the next available ID
		  assert ( (val >= nextValidID) && "<BaseGameEntity::SetID>: invalid ID");
		  id = val;
		  nextValidID = id + 1;
		}

		void BaseGameEntity::SetScale(Vector3 val)
		{
			boundingRadius *= MaxOf(MaxOf(val.X, val.Y), val.Z) /
							  MaxOf(MaxOf(scale.X, scale.Y), scale.Z); 
			scale = val;
		}

		void BaseGameEntity::SetScale(Double val)
		{
			boundingRadius *= (val / MaxOf(MaxOf(scale.X, scale.Y), scale.Z)); 
			scale = Vector3((float)val);
		}

	}
}