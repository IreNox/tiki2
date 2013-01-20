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
			heal = false;
            projectileType = PT_Rocket;
		}

		Rocket::~Rocket()
		{

		}

		void Rocket::Init(ProjectileDescription desc, float radius, bool heal)
		{
			Projectile::Init(desc);
			this->aoeRadius = radius;
			this->heal = heal;
			this->projTarget = Vector2(desc.Target.X, desc.Target.Z);

			Vector3 toTarget = Vector3::Normalize(desc.Target - desc.Origin);
			toTarget = toTarget * desc.MaxSpeed;

			sphere->SetCenter(desc.Origin);
			sphere->GetRigidBody()->SetMass(desc.Mass);
			sphere->GetRigidBody()->SetVelocity(Vector3(toTarget.X, 0, toTarget.Z));
		}


		void Rocket::Handle(ICollider* sender, const TriggerEnterArgs& args)
		{
			TikiBot* bot = args.otherCollider->GetGameObject()->GetComponent<TikiBot>();
			if (bot != 0)
			{
				if (bot->ID() != shooterID)
				{
					if (heal)
					{
						if (bot->GetFaction() == shooter->GetFaction())
						{
							impacted = true;
							dead = true;
							InflictAoeHeal();
						}
					}
					else
					{
						if (bot->GetFaction() != shooter->GetFaction())
						{
							impacted = true;
							dead = true;
							InflictAoEDamage();
						}
					}
				}

			}
// 			else
// 			{
// 				ITriangleMeshCollider* coll = dynamic_cast<ITriangleMeshCollider*>(args.otherCollider);
// 				if (coll != 0)
// 				{
// 					impacted = true;
// 					dead = true;
// 
// 					if (heal)
// 						InflictAoeHeal();
// 					else
// 						InflictAoEDamage();
// 				}
// 			}
		}

		void Rocket::Update(const UpdateArgs& args)
		{

			if (Vector2::DistanceSquared(sphere->GetCenter().XZ(), projTarget) < 3.0f * 3.0f )
			{
				impacted = true;
				dead = true;

				if (heal)
					InflictAoeHeal();
				else
					InflictAoEDamage();
			}

			// handle lifetime
			//Projectile::Update(args);
		}


		void Rocket::InflictAoEDamage()
		{
			// loop all bots and make distance check			
			Vector2 projPos = this->GetCollider()->GetCenter().XZ();

			gameState->GetScene()->SceneGraph.Do([&](GameObject* go) {
				TikiBot* curBot = go->GetComponent<TikiBot>();

				if (curBot != 0 && curBot->GetFaction() != shooter->GetFaction())
				{
					float rad = aoeRadius + (float)curBot->BRadius();

					if (Vector2::Distance(projPos, curBot->Pos()) < rad)
					{
						curBot->ReduceHealth(damage, true);
						if (curBot->IsDead()) shooter->KilledBot(curBot);
					}
				}
			});
		}

		void Rocket::InflictAoeHeal()
		{
			Vector2 projPos = this->GetCollider()->GetCenter().XZ();

			gameState->GetScene()->SceneGraph.Do([&](GameObject* go) {
				TikiBot* curBot = go->GetComponent<TikiBot>();

				if (curBot != 0 && curBot->GetFaction() != shooter->GetFaction())
				{
					float rad = aoeRadius + (float)curBot->BRadius();

					if (Vector2::Distance(projPos, curBot->Pos()) < rad)
					{
						curBot->IncreaseHealth(damage);
					}
				}
			});
		}
	}
}