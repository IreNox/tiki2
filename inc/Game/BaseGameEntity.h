#pragma once

#include "Core/TypeInc.h"
#include "Core/GameObject.h"
#include "Utils.h"

namespace TikiEngine
{
	namespace AI
	{
		class BaseGameEntity : public GameObject
		{

		public:
			enum {default_entity_type = -1};
			BaseGameEntity(Engine* engine, int ID);
			virtual ~BaseGameEntity() { }

			// TODO:
			//virtual bool HandleMessage(const Telegram& msg){return false;}
  
		    //entities should be able to read/write their data to a stream
			virtual void Write(std::ostream& os) const { }
			virtual void Read(std::ifstream& is) { }

			//use this to grab the next valid ID
			static int GetNextValidID() {return nextValidID;}
  
			//this can be used to reset the next ID
			static void ResetNextValidID() {nextValidID = 0;}


			Vector3 Pos() const { return position; }
			void SetPos(const Vector3& newPos) { position = newPos; }

			Double BRadius() const { return boundingRadius; }
			void SetBRadius(Double r) { boundingRadius = r; }

			int ID() const { return id; }

			Boolean isTagged() const { return tag; }
			void Tag() { tag = true; }
			void UnTag() {tag = false; }

			Vector3 Scale() const { return scale; }
			void SetScale(Vector3 val);
			void SetScale(Double val);

			int EntityType() const { return type; }
			void SetEntityType(int newType) { type = newType; }

		private:
			/* !@brief this must be called within each constructor to make sure the ID is set
		        correctly. It verifies that the value passed to the method is greater
		        or equal to the next valid ID, before setting the ID and incrementing the next valid ID */
			void SetID(int val);

		protected:
			Vector3 position;
			Vector3 scale;
		    Double boundingRadius;   // the magnitude of this object's bounding radius

		private:
			int id;					  // each entity has a unique ID
			int type;			      // every entity has a type associated with it (health, troll, ammo etc)
			Boolean tag;		      // generic flag. 
			static int nextValidID;	  // this is the next valid ID. Each time a BaseGameEntity is instantiated this value is updated

		};
	}
}