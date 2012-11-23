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
			SafeRelease(&sphere);
		}

		void Projectile::Init(ProjectileDescription desc, const UpdateArgs& args)
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
			timeOfCreation = args.Time.TotalTime;
			lifeTime = timeOfCreation;

			sphere->SetMaterial(0);
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

		void Projectile::Update(const UpdateArgs& args)
		{
			// remove if older than 2 secs
       		lifeTime += args.Time.ElapsedTime;
			if (lifeTime >=  timeOfCreation + 2.0)
				dead = true;
		}

	}
}