#pragma once

#include "Game/MovingEntity.h"

#include "Core/ISphereCollider.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiBot;

		struct ProjectileDescription
		{
			Vector3 Target; // the target's position
			int ShooterID;  // the ID of the bot that fired this shot
			Vector3 Origin; // the start position of the projectile
			Vector2 Heading;// the heading of the projectile
			int Damage;		// how much damage it inflicts
			float Scale;
			float MaxSpeed;
			float Mass;
			float MaxForce;
            float LifeTime;
            TikiBot* Shooter;

			ProjectileDescription()
			{
				MaxSpeed = 150;
				Mass = 1;
				MaxForce = 150;
				Scale = 0.7f;
				Damage = 5;
                LifeTime = 3.0f;
                Shooter = 0;
			}
		};


		class Projectile : public MovingEntity, public TriggerEnterEventHandler
		{

		public:
			Projectile(GameState* gameState, GameObject* gameObject);
			virtual ~Projectile();

			virtual void Draw(const DrawArgs& args) { }
			virtual void Update(const UpdateArgs& args);
			void Write(std::ostream&  os)const { }
			void Read(std::ifstream& is) { }

			inline TikiBot* GetShooter() { return shooter; }
			inline ISphereCollider* GetCollider() { return sphere; }

			inline const Vector3& GetTarget() { return target; }

			virtual void Handle(ICollider* sender, const TriggerEnterArgs& args);

			// set to true if the projectile has impacted and has finished any explosion 
			// sequence. When true the projectile will be removed from the game
			bool IsDead() const { return dead; }

			// true if the projectile has impacted but is not yet dead (because it
			// may be exploding outwards from the point of impact for example)
			bool HasImpacted() const { return impacted; }


		protected:

			Vector3 target;
			Vector3 origin;
			int damage;
			int shooterID;
			bool dead;
			bool impacted;
            TikiBot* shooter;

			double lifeTime;
			double timeOfLife;
			
			ISphereCollider* sphere;

			void Init(ProjectileDescription desc);

		};
	}
}