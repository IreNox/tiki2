#pragma once

#include <vector>
#include "Game/MovingEntity.h"
#include "Game/TikiSteering.h"
#include "Core/ICharacterController.h"

// NavMesh includes
#include "Game/NavigationCell.h"
#include "Game/NavigationPath.h"
#include "Game/NavigationMesh.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiSteering;
		class GoalThink;
		//class ICharacterController;

		class TikiBot : public MovingEntity
		{
		public:

			TikiBot(GameState* gameState, GameObject* gameObject);
			~TikiBot();

			// Navigation
			void CreateNav(NavigationMesh* par, NavigationCell* currCell = 0);
			void GotoLocation(const Vector3& p, NavigationCell* cell);
			void GotoLocation(const Vector3& p);
			//void GotoRandomLocation();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
			//bool HandleMessage(const Telegram& msg); // TODO
			void Write(std::ostream&  os)const{ }
		    void Read (std::ifstream& is){ }



			#pragma region Accessing attribute data
			int Health() const {return health;}
			int MaxHealth() const {return maxHealth;}
			//void ReduceHealth(unsigned int val);
			//void IncreaseHealth(unsigned int val);
			//void RestoreHealthToMaximum();
				 
			int Score() const {return score;}
			void IncrementScore() {++score;}

			Vector2 Facing() const {return facing;}
			double FieldOfView() const {return fieldOfView;}

			bool IsPossessed() const {return possessed;}
			bool IsDead() const {return status == dead;}
			bool IsAlive() const {return status == alive;}
			bool IsSpawning() const {return status == spawning;}
  
			void SetSpawning() {status = spawning;}
			void SetDead() {status = dead;}
			void SetAlive() {status = alive;}
			#pragma endregion

			//returns true if the bot is close to the given position
			bool IsAtPosition(Vector2 pos);



			ICharacterController* GetController() { return controller; }
			TikiSteering* const GetSteering() { return steering; }
			GoalThink*	  const GetBrain() { return brain; }


		private:
			// bots shouldn't be copied, only created or respawned
			TikiBot(const TikiBot&);
			TikiBot& operator=(const TikiBot&);

			// this method is called from the update method. It calculates and applies
			// the steering force for this time-step.
			void UpdateMovement(const UpdateArgs& args);

			void UpdateNavigation(const UpdateArgs& args);

			enum Status {alive, dead, spawning};

			// alive, dead or spawning?
			Status status;

			// PhysX Controller
			ICharacterController* controller;

			// this object handles the arbitration and processing of high level goals
			GoalThink* brain;

			// the bot uses this object to steer
			TikiSteering* steering;

			// the bot's health. Every time the bot is shot this value is decreased. If
			// it reaches zero then the bot dies (and respawns)
			int health;
  
			// the bot's maximum health value. It starts its life with health at this value
			int maxHealth;

			// each time this bot kills another this value is incremented
			int score;
  
			// the direction the bot is facing (and therefore the direction of aim). 
			// Note that this may not be the same as the bot's heading, which always
			// points in the direction of the bot's movement
			Vector2 facing;

			// a bot only perceives other bots within this field of view
			double fieldOfView;
  
			// to show that a player has been hit it is surrounded by a thick 
			// red circle for a fraction of a second. This variable represents
			// the number of update-steps the circle gets drawn
			int numUpdatesHitPersistant;

			// set to true when the bot is hit, and remains true until 
			// m_iNumUpdatesHitPersistant becomes zero. (used by the render method to
			// draw a thick red circle around a bot to indicate it's been hit)
			bool hit;

			// set to true when a human player takes over control of the bot
			bool possessed;

			// Navigation
			NavigationMesh* parent;			// the mesh we are sitting on
			NavigationCell* currentCell;	// our current cell on the mesh

			// TODO: PathPlanner
			public:
			bool pathActive;				// true when we are using a path to navigate
			NavigationPath path;			// our path object
			NavigationPath::WayPointID nextWaypoint; // ID of the next waypoint we will move to
			NavigationPath::WayPointID lastWaypoint; // ID of the last waypoint we moved to
			
			Vector3 pathMovement;
			Vector3 pathPos;

		};

	}
}