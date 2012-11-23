
#include "Game/SensorMemory.h"
#include "Game/GameState.h"
#include "Game/TikiBot.h"
#include "Game/SceneLevel.h"
#include "Core/IGraphics.h"
#include "Game/WeaponSystem.h"

namespace TikiEngine
{
	namespace AI
	{
		SensorMemory::SensorMemory(TikiBot* bot, double memSpan)
		{
			owner = bot;
			memorySpan = memSpan;
		}

		void SensorMemory::RemoveBotFromMemory(TikiBot* bot)
		{
			MemoryMap::iterator record = memoryMap.find(bot);
			if (record != memoryMap.end())
				memoryMap.erase(record);
		}

		void SensorMemory::UpdateVision(const UpdateArgs& args)
		{
			UInt32 i = 0;
			
			while (i < owner->GetGameState()->GetScene()->GetObjects()->Count())
			{
				GameObject* go = owner->GetGameState()->GetScene()->GetObjects()->Get(i);
				TikiBot* curBot = go->GetComponent<TikiBot>();
				if(curBot != 0 && curBot != owner && curBot->GetFaction() != owner->GetFaction())
				{
					MakeNewRecordIfNotAlreadyPresent(curBot);

					MemoryRecord& info = memoryMap[curBot];

					// test if there is LOS between bots
					if (owner->HasLOSTo(curBot->Pos3D()))
					{
						info.Shootable = true;
                        info.TimeLastSensed = args.Time.TotalTime;
                        info.lastSensedPosition = curBot->Pos3D();
                        info.TimeLastVisible = args.Time.TotalTime;

						//// test if the bot is within FOV
						//if (IsSecondInFOVOfFirst(owner->Pos(), owner->Heading(), curBot->Pos(), owner->FieldOfView()))
						//{
						//	info.TimeLastSensed = args.Time.TotalTime;
						//	info.lastSensedPosition = curBot->Pos3D();
						//	info.TimeLastVisible = args.Time.TotalTime;

						//	if (info.WithinFOV == false)
						//	{
						//		info.WithinFOV = true;
						//		info.TimeBecameVisible = info.TimeLastSensed;
						//	}
						//}
						//else
						info.WithinFOV = true;

					}
					else
					{
						info.Shootable = false;
						info.WithinFOV = false;
					}

				} // if(ent != 0 && curBot != owner)
				i++;
			} // next bot
		}

		bool SensorMemory::IsOpponentShootable(TikiBot* opponent) const
		{
			MemoryMap::const_iterator it = memoryMap.find(opponent);
			if (it != memoryMap.end())
				return it->second.Shootable;

			return false;
		}

		bool SensorMemory::IsOpponentWithinFOV(TikiBot* opponent) const
		{
			MemoryMap::const_iterator it = memoryMap.find(opponent);

			if (it != memoryMap.end())
				return it->second.WithinFOV;

			return false;
		}

		Vector3 SensorMemory::GetLastRecordedPositionOfOpponent(TikiBot* opponent) const
		{
			MemoryMap::const_iterator it = memoryMap.find(opponent);

			if (it != memoryMap.end())
				return it->second.lastSensedPosition;

			throw std::runtime_error("<SensoryMemory::GetLastRecordedPositionOfOpponent>: Attempting to get position of unrecorded bot");
		}

		double SensorMemory::GetTimeOpponentHasBeenVisible(TikiBot* opponent, const GameTime& time) const
		{
			MemoryMap::const_iterator it = memoryMap.find(opponent);

			if (it != memoryMap.end() && it->second.WithinFOV)
				return time.TotalTime - it->second.TimeBecameVisible;

			return 0;
		}

		double SensorMemory::GetTimeOpponentHasBeenOutOfView(TikiBot* opponent, const GameTime& time) const
		{
			MemoryMap::const_iterator it = memoryMap.find(opponent);

			if (it != memoryMap.end())
				return time.TotalTime - it->second.TimeLastVisible;

			return MaxDouble;
		}

		double SensorMemory::GetTimeSinceLastSensed(TikiBot* opponent, const GameTime& time) const
		{
			MemoryMap::const_iterator it = memoryMap.find(opponent);

			if (it != memoryMap.end() && it->second.WithinFOV)
				return time.TotalTime - it->second.TimeLastSensed;

			return 0;
		}


		std::list<TikiBot*> SensorMemory::GetListOfRecentlySensedOpponents(const GameTime& time) const
		{
			// this will store all the opponents the bot can remember
			std::list<TikiBot*> opponents;

			double currentTime = time.TotalTime;

			MemoryMap::const_iterator curRecord = memoryMap.begin();
			for (curRecord; curRecord != memoryMap.end(); ++curRecord)
			{
				// if this bot has been updated in the memory recently, add to list
				if ( (currentTime - curRecord->second.TimeLastSensed) <= memorySpan)
					opponents.push_back(curRecord->first);

			} // for

			return opponents;
		}

		void SensorMemory::Draw(const DrawArgs& args)
		{
#if _DEBUG
			std::list<TikiBot*> opponents = GetListOfRecentlySensedOpponents(args.Time);
			std::list<TikiBot*>::const_iterator it;
			
			for(it = opponents.begin(); it != opponents.end(); ++it)
			{
				Vector3 p = (*it)->Pos3D();
				float b = (*it)->GetController()->GetRadius();

				args.Graphics->DrawLine(Vector3(p.X - b, p.Y, p.Z - b), Vector3(p.X + b, p.Y, p.Z - b), Color::Red);
				args.Graphics->DrawLine(Vector3(p.X + b, p.Y, p.Z - b), Vector3(p.X + b, p.Y, p.Z + b), Color::Red);
				args.Graphics->DrawLine(Vector3(p.X + b, p.Y, p.Z + b), Vector3(p.X - b, p.Y, p.Z + b), Color::Red);
				args.Graphics->DrawLine(Vector3(p.X - b, p.Y, p.Z + b), Vector3(p.X - b, p.Y, p.Z - b), Color::Red);
			}
#endif
		}

		void SensorMemory::MakeNewRecordIfNotAlreadyPresent(TikiBot* opponent)
		{
			// else check to see if this Opponent already exists in the memory. 
			// If it doesn't, create a new record
			if (memoryMap.find(opponent) == memoryMap.end())
				memoryMap[opponent] = MemoryRecord();
		}

	}
}
