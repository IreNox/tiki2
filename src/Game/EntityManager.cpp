
#include <cassert>
#include "Game/EntityManager.h"

namespace TikiEngine
{
	namespace AI
	{
		EntityManager* EntityManager::instance = 0;

		//   this class is a singleton
		EntityManager* EntityManager::Instance()
		{
			if (instance == 0)
				instance = new EntityManager;

		    return instance;
		}

		void EntityManager::Dispose()
		{
			Reset();
			delete instance;
			instance = 0;
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

		void EntityManager::RegisterEntity(BaseGameEntity* newEntity)
		{
			entityMap.insert(std::make_pair(newEntity->ID(), newEntity));
		}


		void EntityManager::RegisterTikiBot(GameObject* gameObject)
		{
			//TikiBot* comp = new TikiBot(0, gameObject);
			//comp->Init();
			//comp->Release();

		    //entityMap.insert(std::make_pair(comp->ID(), gameObject));
		}

	}
}