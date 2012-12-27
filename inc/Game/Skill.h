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

			ST_Active		= 0x01,
			ST_Passive		= 0x02,

			ST_TargetAOE	= 0x04,
			ST_TargetBot	= 0x08
		};

		class Skill : public EngineObject
		{
		public:

			Skill(TikiBot* owner, SkillFlags flags, double cooldown, float crosshairSize, wstring crosshair);
			~Skill();

			void Aktivate();
			void CancelActivation();

			void Draw(const DrawArgs& args);
			void Update(const UpdateArgs& args);

			inline bool GetOnActivation() { return onActivation; }
			inline float GetCrosshairSize() { return crosshairSize; }
			inline ITexture* GetCrosshairTexture() { return crosshair; }

		protected:

			TikiBot* owner;
			GameState* gameState;

			virtual void internActivation(const UpdateArgs& args, const Vector3& target) { }
			virtual void internActivation(const UpdateArgs& args, GameObject* target) { }

			virtual void internDraw(const DrawArgs& args) = 0;
			virtual void internUpdate(const UpdateArgs& args) = 0;

		private:

			TikiEnum<SkillFlags> flags;

			ITexture* crosshair;
			float crosshairSize;

			bool isReady;
			TikiTimer cooldownTimer;

			bool onActivation;
			bool atWork;
		
		};
	}
}