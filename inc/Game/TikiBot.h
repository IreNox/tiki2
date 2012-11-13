#pragma once

#include <vector>
#include "Game/MovingEntity.h"
#include "Game/TikiSteering.h"
#include "Game/PathPlanner.h"
#include "Game/TargetingSystem.h"
#include "Game/Regulator.h"

#include "Core/ICharacterController.h"


namespace TikiEngine
{
	namespace AI
	{
		class TikiSteering;
		class GoalThink;
		class SensorMemory;

		class TikiBot : public MovingEntity
		{
		public:

			TikiBot(GameState* gameState, GameObject* gameObject);
			~TikiBot();

			// Navigation
			void CreateNav(NavigationMesh* par, NavigationCell* currCell = 0);

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
			//bool HandleMessage(const Telegram& msg); // TODO
			void Write(std::ostream&  os)const { }
		    void Read(std::ifstream& is) { }



			#pragma region Accessing attribute data
			int Health() const {return health;}
			int MaxHealth() const {return maxHealth;}
			void ReduceHealth(unsigned int val);
			void IncreaseHealth(unsigned int val);
			void RestoreHealthToMaximum() {health = maxHealth;}
				 
			int Score() const {return score;}
			void IncrementScore() {++score;}

			Vector2 Facing() const {return facing;}
			float FieldOfView() const {return fieldOfView;}

			bool IsPossessed() const {return possessed;}
			bool IsDead() const {return status == dead;}
			bool IsAlive() const {return status == alive;}
			bool IsSpawning() const {return status == spawning;}
  
			void SetSpawning() {status = spawning;}
			void SetDead() {status = dead;}
			void SetAlive() {status = alive;}
			#pragma endregion

			// rotates the bot's heading until it is facing directly at the target
			// position. Returns false if not facing at the target.
			bool RotateFacingTowardPosition(Vector2 target);

			// returns true if the bot is close to the given position
			bool IsAtPosition(Vector2 pos);

			// returns true if the bot has line of sight to the given position.
			bool HasLOSTo(Vector3 pos);

			// this is called to allow a human player to control the bot
			void TakePossession();

			// called when a human is exorcised from this bot and the AI takes control
			void Exorcise();

			PathPlanner* GetPathPlanner() { return pathPlanner; }
			ICharacterController* GetController() { return controller; }
			TikiSteering* const GetSteering() { return steering; }
			GoalThink* const GetBrain() { return brain; }
			TargetingSystem* const GetTargetSys(){ return targSys; }
			TikiBot* const GetTargetBot() const { return targSys->GetTarget(); }
			SensorMemory* const GetSensorMem() const {return sensorMem; }

		private:
			// bots shouldn't be copied, only created or respawned
			TikiBot(const TikiBot&);
			TikiBot& operator=(const TikiBot&);

			// this method is called from the update method. It calculates and applies
			// the steering force for this time-step.
			void UpdateMovement(const UpdateArgs& args);

			enum Status {alive, dead, spawning};

			// alive, dead or spawning?
			Status status;

			// PhysX Controller
			ICharacterController* controller;

			// this object handles the arbitration and processing of high level goals
			GoalThink* brain;

			// Whenever this bot sees or hears an opponent, a record of the event is updated in the memory.
			SensorMemory* sensorMem;

			// the bot uses this object to steer
			TikiSteering* steering;
            
            // object for planning paths
            PathPlanner* pathPlanner;

			// this is responsible for choosing the bot's current target
			TargetingSystem* targSys;

			// A regulator object limits the update frequency of a specific AI component
			// In combination with a distance check, this can be used to create LOD for AI
			Regulator* visionUpdateRegulator;
			Regulator* targetSelectionRegulator;


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
			float fieldOfView;
  
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

			Vector3 orig;
			Vector3 dir;
		};

	}
}