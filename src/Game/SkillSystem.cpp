
#include "Game/SkillSystem.h"

namespace TikiEngine
{
	namespace AI
	{
		#pragma region Class
		SkillSystem::SkillSystem(TikiBot* owner)
			: owner(owner)
		{
		}

		SkillSystem::~SkillSystem()
		{
			FOREACH(skills, SafeRelease(&skills[i]));
		}
		#pragma endregion

		#pragma region Member
		void SkillSystem::Init()
		{

		}

		void SkillSystem::Draw(const DrawArgs& args)
		{
			FOREACH_PTR_CALL(skills, Draw(args));
		}

		void SkillSystem::Update(const UpdateArgs& args)
		{
			static Key keys[4] = { KEY_Q, KEY_W, KEY_E, KEY_R };

			UInt32 i = 0;
			while (i < skills.Count())
			{
				if (args.Input.GetKeyPressed(keys[i]))
				{
					skills[i]->Aktivate();
				}

				skills[i]->Update(args);
				i++;
			}
		}
		#pragma endregion
	}
}