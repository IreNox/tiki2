#include "Game/PEHealAura.h"
#include "Game/Utils.h"


namespace TikiEngine
{
    namespace Particles
    {
        PEHealAura::PEHealAura(Engine* engine)
            :ParticleEffect(engine)
        {
            // 1000 particles, 500 per second -> 2 lifetime
           // this->SParticleBudget(100000);
            renderType = PRT_PointList;
            releasePerSecound = 400; //500;
            lifeTime = 2.5;
            
            interp.MiddlePosition = 0.3f;
        }


        void PEHealAura::CreateParticle(Particle* particle)
        {
            float r = Random(0, TwoPi);
            float circleSize = Random(0, 50);
            particle->Position = Vector3(sinf(r) * circleSize, 0, cosf(r) * circleSize);
            particle->Color = Color::White;
            particle->Color.A = 0;
            particle->Rotation = 0;
            particle->Size = Vector2::One / 15;
            particle->Velocity = Vector3::UnitY * 50;

        }

        void PEHealAura::UpdateParticle(Particle* particle)
        {
            particle->Color.A = interp.GetValue(particle->Age); //1 - particle->Age;
            //particle->Position.Y = sin(particle->Age * 20) * 0.2f;
            //particle->Position.Z = cos(particle->Age * 20) * 0.2f;
            //particle->Rotation = particle->Age * 3.14159f;
        }

    }
}