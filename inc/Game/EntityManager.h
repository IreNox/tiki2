#pragma once

#include "Game/BaseGameEntity.h"
#include <map>

namespace TikiEngine
{
	namespace AI
	{

		class EntityManager
		{
		public:
			EntityManager(){}
			~EntityManager();

			/* !@brief this method stores a pointer to the entity in the std::vector
				 entities at the index position indicated by the entity's ID (made for faster access) */
			void RegisterEntity(BaseGameEntity* TIKI_NEWEntity);

			/* !@brief returns a pointer to the entity with the ID given as a parameter */
			BaseGameEntity* GetEntityFromID(int id) const;
			
			/* !@brief this method removes the entity from the list */
			void RemoveEntity(BaseGameEntity* entity);
			
			/* !@brief clears all entities from the entity map */
			void Reset() { entityMap.clear(); }

		private:
			typedef std::map<int, BaseGameEntity*> EntityMap;

			// for a quick lookup the entities are stored in a std::map, in which
			// pointers to entities are cross referenced by their identifying number
			EntityMap entityMap;

		};
	}
}