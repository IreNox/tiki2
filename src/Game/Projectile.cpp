#include "Game/Projectile.h"
#include "Game/TikiBot.h"
#include "Core/ICollider.h"

namespace TikiEngine
{
	namespace AI
	{
		Projectile::Projectile(GameState* gameState, GameObject* gameObject)
			: MovingEntity(gameState, gameObject)
		{
			sphere = engine->librarys->CreateComponent<ISphereCollider>(gameObject);
			sphere->AddRef();
			sphere->TriggerEnter.AddHandler(this);
		}

		Projectile::~Projectile()
		{
			sphere->TriggerEnter.RemoveHandler(this);
			SafeRelease(&sphere);
		}

		void Projectile::Init(ProjectileDescription desc)
		{
			//Vector2 heading2D = Vector2(desc.Heading.X, desc.Heading.Z);
			MovingEntity::Init(desc.Scale, Vector2::Zero, desc.MaxSpeed, desc.Heading, 0, desc.MaxForce);

			target = desc.Target;
			origin = desc.Origin;
			damage = desc.Damage;
			shooterID = desc.ShooterID;
            shooter = desc.Shooter;
			dead = false;
			impacted = false;	
			timeOfLife = 0;
			lifeTime = desc.LifeTime;

			sphere->SetMaterial(gameState->GetDefaultMaterial());
			sphere->SetCenter(desc.Origin);
			sphere->SetRadius(desc.Scale);
			sphere->SetDynamic(true);
			sphere->SetTrigger(true);
			sphere->SetGroup(CG_Collidable_Non_Pushable);

			//Vector2 vel = desc.Heading * desc.MaxSpeed;
			//vel.Truncate(desc.MaxSpeed);
			//Vector3 vel = Vector3::Normalize(desc.Target - desc.Origin);
			//vel = vel* desc.MaxSpeed;
			//sphere->GetRigidBody()->SetMass(desc.Mass);
			//sphere->GetRigidBody()->SetVelocity(vel);
		}

		void Projectile::Handle(ICollider* sender, const TriggerEnterArgs& args)
		{

  		}

        void Projectile::SetProjectileType(ProjectileType pType)
        {
            projectileType = pType;
        }


        ProjectileType Projectile::GetProjectileType()
        {
            return projectileType;
        }


		void Projectile::Update(const UpdateArgs& args)
		{
			// remove if older than lifeTime
       		timeOfLife += args.Time.ElapsedTime;
			if (timeOfLife >= lifeTime)
				dead = true;
		}

	}
}