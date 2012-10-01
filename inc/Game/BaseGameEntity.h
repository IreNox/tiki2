#pragma once

#include "Core/TypeInc.h"
#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Game/Utils.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Components;

		class BaseGameEntity : public Component
		{

		public:
			enum {default_entity_type = -1};
			BaseGameEntity(Engine* engine, GameObject* gameObject);
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


			Vector3 Pos() { return GetGameObject()->PRS.Position; }
			void SetPos(const Vector3& newPos) { GetGameObject()->PRS.Position = newPos; }

			Double BRadius() const { return boundingRadius; }
			void SetBRadius(Double r) { boundingRadius = r; }

			int ID() const { return id; }

			Boolean isTagged() const { return tag; }
			void Tag() { tag = true; }
			void UnTag() {tag = false; }

			Vector3 Scale() { return GetGameObject()->PRS.Scale; }
			void SetScale(Vector3 val);
			void SetScale(float val);

			int EntityType() const { return type; }
			void SetEntityType(int newType) { type = newType; }

			bool GetReady() { return true; }

		protected:
		    Double boundingRadius;   // the magnitude of this object's bounding radius

		private:
			int id;					  // each entity has a unique ID
			int type;			      // every entity has a type associated with it (health, troll, ammo etc)
			Boolean tag;		      // generic flag. 

			static int nextValidID;	  // this is the next valid ID. Each time a BaseGameEntity is instantiated this value is updated
		};
	}
}