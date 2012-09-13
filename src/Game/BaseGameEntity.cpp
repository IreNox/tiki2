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

	}
}