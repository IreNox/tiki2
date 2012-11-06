#include "Game/TargetingSystem.h"

#include "Game/TikiBot.h"
#include "Game/SensorMemory.h"
#include "Game/Utils.h"
#include <list>

namespace TikiEngine
{
	namespace AI
	{
		TargetingSystem::TargetingSystem(TikiBot* owner)
		{
			this->owner = owner;
			this->currentTarget = 0;
		}

		void TargetingSystem::Update(const UpdateArgs& args)
		{
			float closestDistSoFar = MaxFloat;
			currentTarget = 0;

			// grab a list of all the opponents the owner can sense
			std::list<TikiBot*> sensedBots;
			sensedBots = owner->GetSensorMem()->GetListOfRecentlySensedOpponents(args.Time);

			std::list<TikiBot*>::const_iterator curBot = sensedBots.begin();
			for (curBot; curBot != sensedBots.end(); ++curBot)
			{
				// make sure the bot is alive and that it is not the owner
				if ( (*curBot)->IsAlive() && (*curBot != owner) )
				{
					float dist = Vector2::DistanceSquared((*curBot)->Pos(), owner->Pos());

					if (dist < closestDistSoFar)
					{
						closestDistSoFar = dist;
						currentTarget = *curBot;
					} // if
				} // if
			} // for
		}
		
		bool TargetingSystem::IsTargetWithinFOV() const
		{
			return owner->GetSensorMem()->IsOpponentWithinFOV(currentTarget);
		}

		bool TargetingSystem::IsTargetShootable() const
		{
			return owner->GetSensorMem()->IsOpponentShootable(currentTarget);
		}

		Vector3 TargetingSystem::GetLastRecordedPosition() const
		{
			return owner->GetSensorMem()->GetLastRecordedPositionOfOpponent(currentTarget);
		}

		double TargetingSystem::GetTimeTargetHasBeenVisible(const UpdateArgs& args) const
		{
			return owner->GetSensorMem()->GetTimeOpponentHasBeenVisible(currentTarget, args.Time);
		}

		double TargetingSystem::GetTimeTargetHasBeenOutOfView(const UpdateArgs& args) const
		{
			return owner->GetSensorMem()->GetTimeOpponentHasBeenOutOfView(currentTarget, args.Time);
		}
	}
}