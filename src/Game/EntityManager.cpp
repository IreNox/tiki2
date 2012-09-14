#include "Game/EntityManager.h"
#include <cassert>

namespace TikiEngine
{
	namespace AI
	{
		//   this class is a singleton
		EntityManager* EntityManager::Instance()
		{
		    static EntityManager instance;
		    return &instance;
		}

		BaseGameEntity* EntityManager::GetEntityFromID(int id) const
		{
			//find the entity
		    EntityMap::const_iterator ent = entityMap.find(id);

		    //assert that the entity is a member of the map
		    assert ( (ent !=  entityMap.end()) && "<EntityManager::GetEntityFromID>: invalid ID");
		    
		    return ent->second;
		}

		void EntityManager::RemoveEntity(BaseGameEntity* entity)
		{    
		    entityMap.erase(entityMap.find(entity->ID()));
		} 

		void EntityManager::RegisterEntity(BaseGameEntity* newEntity)
		{
		    entityMap.insert(std::make_pair(newEntity->ID(), newEntity));
		}
	}
}