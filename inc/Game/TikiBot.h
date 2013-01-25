#pragma once

#include "Game/MovingEntity.h"
#include "Game/Regulator.h"

#include "Game/PathPlanner.h"
#include "Game/TikiSteering.h"
#include "Game/AttributeSystem.h"
#include "Game/TargetingSystem.h"

#include "Core/ICharacterController.h"

#include "Game/EventBotDead.h"

namespace TikiEngine
{
	namespace AI
	{
		class GoalThink;
		class SensorMemory;
		class Weapon;
        class WeaponSystem;
		class SkillSystem;

		#pragma region TikiBotDescription
		struct TikiBotDescription
		{
			/*! @brief 0 = Player, 1 = Enemy */
			int Faction;
			/*! @brief The maximum amount of health */
			float MaxHealth;

			/*! @brief The Bots field of view in degrees */
			float FoV;
			/*! @brief The Bots reaction time (in seconds) */
			float ReactionTime;
			/*! @brief How long (in seconds) the bot will keep pointing its weapon at its target after the target goes out of view */
			float AimPresistance;
			/*! @brief How accurate the bots are at aiming. 0 is very accurate, (the value represents the max deviation in range (in radians)) */
			float AimAccuracy;
			/*! @brief How long (in seconds) a bots sensory memory persists */
			float MemorySpan;

			// Brain
			float ExploreBias;
			float AttackBias;
			float PatrolBias;

			// Controller
			/*! @brief Capsule height */
			float Height;
			/*! @brief Limits the collider to only climb slopes that are equal to or less than the indicated value in degrees */
			float SlopeLimit;
			/*! @brief The bot will step up a stair only if it is closer to the ground than the indicated value */
			float StepOffset;

			// MovingEntity
			Vector2 Heading;
			float MaxSpeed; 
			float MaxTurnRate;
			float MaxForce;
			float Radius;

			int Loot;
			/*! @brief 1 Armor blocks 1 Damage */
			int Armor;

			// TIKI_NEW fields Added: Loot, Armor, SightRadius, EntityType
			Weapon* StartWeapon;
			double StartMGDamage;
			double StartMGFireRate;

			EntityTypes EntityType;
			float SightRadius;

			TikiBotDescription()
			{
				MaxHealth = 100;

				FoV = 180.0f;
				ReactionTime = 0.001f;
				AimPresistance = 1.0f;
				AimAccuracy = 0.0f;
				MemorySpan = 0.5f; //0.5f;

				// brain
				ExploreBias = 0.05f;
				AttackBias = 1.0f;
				PatrolBias = 0.9f;

				// Controller
				Height = 10.0f;
				SlopeLimit = 45.0f;
				StepOffset = 0.5f;

				// MovingEntity
				Heading = Vector2(0.0001f);
				MaxSpeed = 5.0f;
				MaxTurnRate = 0.5f;
				MaxForce = 1.0f;
				Radius = 2.0f;

				SightRadius = 30;
				Loot = 0;
				Armor = 0;

				StartMGDamage = 5;
				StartMGFireRate = 5;

				// Darf NICHT Bearbeitet werden!
				EntityType = ET_Bot;
				StartWeapon = 0;
				Faction = 0;
			}

		};
		#pragma endregion

		class TikiBot : public MovingEntity
		{
		public:
			
			//Events
			BotDeadEvent OnDeath;

			TikiBot(GameState* gameState, GameObject* gameObject, const TikiBotDescription& desc);
			~TikiBot();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);
			
			#pragma region Accessing attribute data
			inline double Health() const { return health; }
			inline double MaxHealth() const { return attSys[TA_MaxHealth]; }
			inline void RestoreHealthToMaximum() { health = attSys[TA_MaxHealth]; }
			void ReduceHealth(double val, bool useArmor);
			void IncreaseHealth(double val);

			void SetTimeSinceDead(double deathTime) { timeSinceDeath = deathTime; }
			void IncreaseTimeSInceDead(double timeInc) { timeSinceDeath += timeInc; }
			double GetTimeSinceDead() { return timeSinceDeath; }
				 
			//Vector2 Facing() const {return facing;}
			inline float FieldOfView() const { return fieldOfView; }

            // 0 = Player, 1 = Enemy
            inline int GetFaction() const { return faction; }
			inline float GetSightRadius() const { return sightRadius; }

			//bool IsPossessed() const {return possessed;}
			inline bool IsDead() const { return status == dead; }
			inline bool IsAlive() const { return status == alive; }
			inline bool IsSpawning() const { return status == spawning; }

			inline void SetDead() { status = dead; }
			inline void SetAlive() { status = alive; }
			inline void SetSpawning() { status = spawning; }
			#pragma endregion

			// Called if this Bot has killed
			void KilledBot(TikiBot* deadBot);

			// rotates the bot's heading until it is facing directly at the target
			// position. Returns false if not facing at the target.
			bool RotateFacingTowardPosition(Vector2 target);

			// returns true if the bot is close to the given position
			bool IsAtPosition(Vector2 pos);

			// returns true if the bot has line of sight to the given position.
			bool HasLOSTo(Vector3 pos, float dist, float eps);

			// this is called to allow a human player to control the bot
			//void TakePossession();

			// called when a human is exorcised from this bot and the AI takes control
			//void Exorcise();

			void Teleport(const Vector3& pos);

			inline TikiBot* const GetTargetBot() const { return targSys->GetTarget(); }
			inline ICharacterController* GetController() { return controller; }

			/*! @brief Manage all Attributes */
			inline AttributeSystem& GetAttSys() { return attSys; }
			/*! @brief this object handles the arbitration and processing of high level goals */
			inline GoalThink* const GetBrain() { return brain; }
			/*! @brief Object for planning paths */
			inline PathPlanner* GetPathPlanner() { return pathPlanner; }
			/*! @brief The bot uses this object to steer */
			inline TikiSteering* const GetSteering() { return steering; }
			/*! @brief This is responsible for choosing the bots current target */
			inline TargetingSystem* const GetTargetSys(){ return targSys; }
			/*! @brief Whenever this bot sees or hears an opponent, a record of the event is updated in the memory. */
			inline SensorMemory* const GetSensorMem() const {return sensorMem; }
			/*! @brief Handles all the weapons and aims */
            inline WeaponSystem* const GetWeaponSys() const {return weaponSys; }
			/*! @brief Skillsystem used by hero type */
			inline SkillSystem* const GetSkillSys() const { return skillSys; }

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

			// Systems
			AttributeSystem attSys;
			GoalThink* brain;
			SensorMemory* sensorMem;
			TikiSteering* steering;
            PathPlanner* pathPlanner;
			TargetingSystem* targSys;
            WeaponSystem* weaponSys;
			SkillSystem* skillSys;

			// A regulator object limits the update frequency of a specific AI component
			// In combination with a distance check, this can be used to create LOD for AI
			Regulator* visionUpdateRegulator;
			Regulator* targetSelectionRegulator;


			// the bot's health. Every time the bot is shot this value is decreased. If
			// it reaches zero then the bot dies (and respawns)
			double health;
  
			// the bot's maximum health value. It starts its life with health at this value
			//float maxHealth;

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

			int faction;

			Vector3 orig;
			Vector3 dir;

			float sightRadius;
			int loot;
			int armor;

			double timeSinceDeath;

		};

	}
}