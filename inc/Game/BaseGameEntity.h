#pragma once

#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace AI
	{
		class BaseGameEntity : GameObject
		{

		public:
			enum {default_entity_type = -1};
			BaseGameEntity(Engine* engine, int ID);
			virtual ~BaseGameEntity(){}

			//virtual bool HandleMessage(const Telegram& msg){return false;}
  
		    //entities should be able to read/write their data to a stream
			virtual void Write(std::ostream&  os)const { }
			virtual void Read(std::ifstream& is) { }

			//use this to grab the next valid ID
			static int GetNextValidID() {return nextValidID;}
  
			//this can be used to reset the next ID
			static void ResetNextValidID() {nextValidID = 0;}


		private:
			/* !@brief this must be called within each constructor to make sure the ID is set
		       correctly. It verifies that the value passed to the method is greater
		       or equal to the next valid ID, before setting the ID and incrementing the next valid ID
			*/
			void SetID(int val);

		protected:
			Vector3 position;
			Vector3 scale;
		    double boundingRadius;   //the magnitude of this object's bounding radius

		private:
			int id;					  // each entity has a unique ID
			int type;			      // every entity has a type associated with it (health, troll, ammo etc)
			bool tag;				  // generic flag. 
			static int nextValidID;	  // this is the next valid ID. Each time a BaseGameEntity is instantiated this value is updated

		};
	}
}