#include "Game/Bullet.h"
#include "Game/TikiBot.h"
#include "Core/ITriangleMeshCollider.h"

namespace TikiEngine
{
    namespace AI
    {
        Bullet::Bullet(GameState* gameState, GameObject* gameObject)
            : Projectile(gameState, gameObject)
        {
        }

        Bullet::~Bullet()
        {
        }

        void Bullet::Init(ProjectileDescription desc, const UpdateArgs& args)
        {
            Projectile::Init(desc, args);

            Vector3 toTarget = Vector3::Normalize(desc.Target - desc.Origin);
            toTarget = toTarget * desc.MaxSpeed;
            Vector2 vel = desc.Heading * desc.MaxSpeed;
            vel.Truncate(desc.MaxSpeed);

            sphere->GetRigidBody()->SetMass(desc.Mass);
            sphere->GetRigidBody()->SetVelocity(Vector3(vel.X, toTarget.Y, vel.Y));
        }


        void Bullet::Handle(ICollider* sender, const TriggerEnterArgs& args)
        {
            // TODO: faction
            TikiBot* bot = args.otherCollider->GetGameObject()->GetComponent<TikiBot>();
            if (bot != 0)
            {
                if (bot->ID() != shooterID && bot->GetFaction() != shooter->GetFaction())
                {
                    impacted = true;
                    dead = true;

					//gameState->GetEngine()->HLog.Write("bot hit, health reduced.");
                    bot->ReduceHealth(damage);
                }
            }
            else
            {
                // ITriangleMeshCollider* coll = args.otherCollider->GetGameObject()->GetComponent<ITriangleMeshCollider>();
                ITriangleMeshCollider* coll = dynamic_cast<ITriangleMeshCollider*>(args.otherCollider);
                if (coll != 0)
                {
                    impacted = true;
                    dead = true;
                }
            }
        }


        void Bullet::Update(const UpdateArgs& args)
        {
            // handle lifetime
            Projectile::Update(args);
        }
    }
}