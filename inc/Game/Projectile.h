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
			/*! @brief how much damage it inflicts */
			double Damage;

			/*! @brief the target's position */
			Vector3 Target;
			/*! @brief the ID of the bot that fired this shot */
			int ShooterID;
			/*! @brief the start position of the projectile */
			Vector3 Origin;
			/*! @brief the heading of the projectile */
			Vector2 Heading;

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
				Damage = 5.0;
                LifeTime = 3.0f;
                Shooter = 0;
			}
		};

        enum ProjectileType {PT_Bullet, PT_Rocket };

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

           void SetProjectileType(ProjectileType pType);
           ProjectileType GetProjectileType();

		protected:

			double damage;

			Vector3 target;
			Vector3 origin;
			int shooterID;
			bool dead;
			bool impacted;
            TikiBot* shooter;

			double lifeTime;
			double timeOfLife;
			
			ISphereCollider* sphere;

            ProjectileType projectileType;

			void Init(ProjectileDescription desc);

		};
	}
}