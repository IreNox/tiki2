
#include <cassert>
#include "Game/EntityManager.h"

namespace TikiEngine
{
	namespace AI
	{
		EntityManager::~EntityManager()
		{
			Reset();
		}

		BaseGameEntity* EntityManager::GetEntityFromID(int id) const
		{
			//find the entity
		    EntityMap::const_iterator ent = entityMap.find(id);

		    //assert that the entity is a member of the map
		    assert((ent !=  entityMap.end()) && "<EntityManager::GetEntityFromID>: invalid ID");
		    
		    return ent->second;
		}

		void EntityManager::RemoveEntity(BaseGameEntity* entity)
		{    
		    entityMap.erase(entityMap.find(entity->ID()));
		} 

		void EntityManager::RegisterEntity(BaseGameEntity* TIKI_NEWEntity)
		{
			entityMap.insert(std::make_pair(TIKI_NEWEntity->ID(), TIKI_NEWEntity));
		}

	}
}