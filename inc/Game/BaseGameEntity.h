#pragma once

#include "Core/TypeInc.h"
#include "Core/Component.h"
#include "Core/GameObject.h"

#include "Game/Utils.h"
#include "Game/GameState.h"

namespace TikiEngine
{
	namespace AI
	{
		using namespace TikiEngine::Game;
		using namespace TikiEngine::Components;

		enum EntityTypes
		{
			ET_Default	= -1,
			ET_Bot		= 0,
			ET_Tower	= 1,
			ET_Building	= 2,
			ET_Hero		= 3
		};

		class BaseGameEntity : public Component
		{
		public:

			BaseGameEntity(GameState* gameState, GameObject* gameObject);
			virtual ~BaseGameEntity() { }

			//use this to grab the next valid ID
			static int GetNextValidID() {return nextValidID;}
  
			//this can be used to reset the next ID
			static void ResetNextValidID() {nextValidID = 0;}

			Vector2 Pos() { return gameObject->PRS.GPosition().XZ(); }
			Vector3 Pos3D() { return GetGameObject()->PRS.GPosition(); }

			Double BRadius() const { return boundingRadius; }
			void SetBRadius(Double r) { boundingRadius = r; }

			int ID() const { return id; }

			bool isTagged() const { return tag; }
			void Tag() { tag = true; }
			void UnTag() {tag = false; }

			Vector3 Scale() { return GetGameObject()->PRS.GScale(); }
			void SetScale(Vector3 val) { gameObject->PRS.SScale() = val; }
			void SetScale(float val) { gameObject->PRS.SScale() = Vector3(val); }

			EntityTypes EntityType() const { return type; }
			//void SetEntityType(int newType) { type = newType; }

			bool GetReady() { return true; }

			GameState* GetGameState() { return gameState; }

		protected:

			GameState* gameState;

		    Double boundingRadius;    // the magnitude of this object's bounding radius

		protected:
			
			EntityTypes type;			      // every entity has a type associated with it (health, troll, ammo etc)
			bool tag;				  // generic flag. 

		private:
			int id;					  // each entity has a unique ID
			static int nextValidID;	  // this is the next valid ID. Each time a BaseGameEntity is instantiated this value is updated
		};
	}
}
