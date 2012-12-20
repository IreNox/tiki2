#include "Game/Rocket.h"
#include "Game/TikiBot.h"
#include "Core/ITriangleMeshCollider.h"
#include "Game/SceneLevel.h"


namespace TikiEngine
{
	namespace AI
	{
		Rocket::Rocket(GameState* gameState, GameObject* gameObject)
			: Projectile(gameState, gameObject)			
		{
			aoeRadius = 20.0f;
		}

		Rocket::~Rocket()
		{

		}

		void Rocket::Init(ProjectileDescription desc, float radius, const UpdateArgs& args)
		{
			Projectile::Init(desc, args);
			this->aoeRadius = radius;

			Vector3 toTarget = Vector3::Normalize(desc.Target - desc.Origin);
			toTarget = toTarget * desc.MaxSpeed;
			Vector3 vel = toTarget;

			sphere->SetCenter(desc.Origin);
			sphere->GetRigidBody()->SetMass(desc.Mass);
			sphere->GetRigidBody()->SetVelocity(Vector3(vel.X, toTarget.Y, vel.Z));
		}


		void Rocket::Handle(ICollider* sender, const TriggerEnterArgs& args)
		{
			TikiBot* bot = args.otherCollider->GetGameObject()->GetComponent<TikiBot>();
			if (bot != 0)
			{
				if (bot->ID() != shooterID && bot->GetFaction() != shooter->GetFaction())
				{
					impacted = true;
					dead = true;
					InflictAoEDamage();
				}
			}
			else
			{
				ITriangleMeshCollider* coll = dynamic_cast<ITriangleMeshCollider*>(args.otherCollider);
				if (coll != 0)
				{
					impacted = true;
					dead = true;
					InflictAoEDamage();
				}
			}
		}

		void Rocket::Update(const UpdateArgs& args)
		{
			// handle lifetime
			Projectile::Update(args);
		}


		void Rocket::InflictAoEDamage()
		{
			// loop all bots and make distance check
			for (UInt32 i = 0; i < gameState->GetScene()->GetElements().Count(); i++)
			{
				GameObject* current = gameState->GetScene()->GetElements().Get(i);
				TikiBot* curBot = current->GetComponent<TikiBot>();
				if (curBot != 0 && curBot->GetFaction() != shooter->GetFaction())
				{
					float rad = aoeRadius + (float)curBot->BRadius();
					Vector2 projPos = Vector2(GetCollider()->GetCenter().X, GetCollider()->GetCenter().Z);
					float dist = Vector2::Distance(projPos, curBot->Pos());
					if (dist < rad)
					{
						curBot->ReduceHealth(damage);
						if (curBot->IsDead() && shooter->EntityType() == ET_Hero)
							gameState->IncrementResource(10);
					}
				}
			}
		}


	}
}