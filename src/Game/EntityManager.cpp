#include "Game/EntityManager.h"
#include <cassert>

#include "Game/MovingEntity.h"

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

		GameObject* EntityManager::GetEntityFromID(int id) const
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

		void EntityManager::RegisterMovingEntity(GameObject* gameObject)
		{
			MovingEntity* comp = new MovingEntity(0, gameObject);
			comp->Init();
			comp->Release();

		    entityMap.insert(std::make_pair(comp->ID(), gameObject));
		}

		//void EntityManager::RegisterBot(GameObject* gameObject)
		//{
		//	TikiBot* comp = new TikiBot(engine, gameObject);
		//	comp->Init();

		//	entityMap.insert(std::make_pair(comp->ID(), gameObject));
		//}

	}
}