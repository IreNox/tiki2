#pragma once

#include "Core/EngineObject.h"
#include "Core/TikiTimer.h"
#include "Core/ITexture.h"
#include "Core/GameObject.h"

namespace TikiEngine
{
	namespace AI
	{
		class TikiBot;
	}

	namespace Game
	{	
		using namespace TikiEngine::AI;			
		using namespace TikiEngine::Resources;

		class GameState;

		enum SkillFlags
		{
			ST_Invalid		= 0,

			ST_Active		= 1 << 0,
			ST_Passive		= 1 << 1,

			ST_TargetAOE	= 1 << 2,
			ST_TargetBot	= 1 << 3,
			ST_TargetAura	= 1 << 4,		
			ST_TargetNoBot	= 1 << 5,
		};

		struct SkillDescription
		{
			float AOERange;
			float ActivationRange;
			SkillFlags Flags;

			wcstring TexNameIcon;
			wcstring TexNameCrosshair;

			double Cooldown;
			double DurationOfEffect;

			SkillDescription(float activationRange, SkillFlags flags, float aoeRange, wcstring texNameIcon, wcstring texNameCrosshair, double cooldown, double durationOfEffect)
				: ActivationRange(activationRange), AOERange(aoeRange), Flags(flags), TexNameIcon(texNameIcon), TexNameCrosshair(texNameCrosshair),
				  Cooldown(cooldown), DurationOfEffect(durationOfEffect)
			{
			}
		};

		class Skill : public EngineObject
		{
		public:
			
			Skill(TikiBot* owner, const SkillDescription& desc); //SkillFlags flags, double cooldown, float crosshairSize, wstring crosshair);
			~Skill();

			void Aktivate();
			void CancelActivation();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			inline float GetInRange() { return inRange; }
			inline bool GetOnActivation() { return onActivation; }

			inline float GetCrosshairSize() { return description.AOERange; }
			inline ITexture* GetCrosshairTexture() { return crosshair; }

		protected:

			TikiBot* owner;
			GameState* gameState;

			virtual void internActivation(const Vector3& target) { throw "NotImplemented"; }
			virtual void internActivation(GameObject* target) { throw "NotImplemented"; }

			virtual void internDraw(const DrawArgs& args) = 0;
			virtual void internUpdate(const UpdateArgs& args) = 0;

		private:

			TikiEnum<SkillFlags> flags;
			SkillDescription description;

			ITexture* icon;
			ITexture* crosshair;

			bool isReady;
			TikiTimer cooldownTimer;

			bool onActivation;
			bool atWork;
			bool inRange;
		
		};
	}
}