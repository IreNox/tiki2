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
			SF_Invalid		= 0,

			SF_Active		= 1 << 0,
			SF_Passive		= 1 << 1,

			SF_TargetAOE	= 1 << 2,
			SF_TargetBot	= 1 << 3,
			SF_TargetAura	= 1 << 4,		
			SF_TargetPoint	= 1 << 5,
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

			SkillDescription(double cooldown, float activationRange, float aoeRange, double durationOfEffect, SkillFlags flags, wcstring texNameIcon, wcstring texNameCrosshair)
				: ActivationRange(activationRange), AOERange(aoeRange), Flags(flags), TexNameIcon(texNameIcon), TexNameCrosshair(texNameCrosshair),
				  Cooldown(cooldown), DurationOfEffect(durationOfEffect)
			{
			}
		};

		class Skill : public EngineObject
		{
		public:
			
			Skill(TikiBot* owner, const SkillDescription& desc);
			~Skill();

			void Aktivate();
			void CancelActivation();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			inline float GetInRange() { return inRange; }
			inline bool GetHasAOE() { return flags.HasFlag(SF_TargetAOE); }
			inline bool GetOnActivation() { return onActivation; }

			inline float GetCrosshairSize() { return description.AOERange; }
			inline ITexture* GetCrosshairTexture() { return crosshair; }

			inline ITexture* GetIconTexture() { return icon; }

		protected:

			bool atWork;
			bool isReady;
			bool onActivation;

			TikiBot* owner;
			GameState* gameState;

			virtual bool internActivationBot(TikiBot* target) { throw "NotImplemented"; }
			virtual void internActivationPoint(const Vector3& target) { throw "NotImplemented"; }
			virtual void internActivationAuraFrame(const UpdateArgs& args, TikiBot* target) { throw "NotImplemented"; }

			virtual void internDraw(const DrawArgs& args) {};
			virtual void internUpdate(const UpdateArgs& args) {};

		private:

			TikiEnum<SkillFlags> flags;
			SkillDescription description;

			ITexture* icon;
			ITexture* crosshair;

			TikiTimer workTimer;
			TikiTimer cooldownTimer;

			bool inRange;
		
		};
	}
}