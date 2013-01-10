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
			double Cooldown;
			double DurationOfEffect;

			float AOERange;
			float ActivationRange;

			UInt32 MaxLevel;

			SkillFlags Flags;

			wcstring TexNameIcon;
			wcstring TexNameCrosshair;

			SkillDescription(double cooldown, float activationRange, float aoeRange, double durationOfEffect, UInt32 maxLevel, SkillFlags flags, wcstring texNameIcon, wcstring texNameCrosshair)
				: ActivationRange(activationRange), AOERange(aoeRange), Flags(flags), TexNameIcon(texNameIcon), TexNameCrosshair(texNameCrosshair),
				  Cooldown(cooldown), DurationOfEffect(durationOfEffect), MaxLevel(maxLevel)
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

			void Upgrade();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			inline bool GetInRange() const { return inRange; }
			inline bool GetHasAOE() const { return flags.HasFlag(SF_TargetAOE); }
			inline bool GetOnActivation() const { return onActivation; }

			inline ITexture* GetIconTexture() const { return icon; }
			inline ITexture* GetCrosshairTexture() const { return crosshair; }

			inline const SkillDescription& GetDesc() const { return description; }

			inline UInt32 GetCurrentLevel() const { return currentLevel; }
			inline double GetAtWorkState() const { return atWork; }
			inline double GetCooldownState() const { return (!isReady ? cooldownTimer.GetCurrentState() : 0.0); }
			inline const wstring& GetCurrentLevelString() const { return currentLevelString; }

		protected:

			bool atWork;
			bool isReady;
			bool onActivation;

			UInt32 currentLevel;
			wstring currentLevelString;
			SkillDescription description;

			TikiBot* owner;
			GameState* gameState;

			virtual bool internActivationBot(TikiBot* target) { throw "NotImplemented"; }
			virtual void internActivationPoint(const Vector3& target) { throw "NotImplemented"; }
			virtual void internActivationAuraFrame(const UpdateArgs& args, TikiBot* target) { throw "NotImplemented"; }

			virtual void internDraw(const DrawArgs& args) {};
			virtual void internUpdate(const UpdateArgs& args) {};

			virtual void internUpgrade() {}

		private:

			TikiEnum<SkillFlags> flags;

			ITexture* icon;
			ITexture* crosshair;

			TikiTimer workTimer;
			TikiTimer cooldownTimer;

			bool inRange;
		
		};
	}
}