
#include "Game/SensorMemory.h"
#include "Game/GameState.h"
#include "Game/TikiBot.h"
#include "Game/SceneLevel.h"


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
				if(curBot != 0 && curBot != owner)
				{
					MakeNewRecordIfNotAlreadyPresent(curBot);

					MemoryRecord& info = memoryMap[curBot];

					// TODO: test if there is LOS between bots
				} // if(ent != 0)
				i++;
			}
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