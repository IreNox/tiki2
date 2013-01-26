#pragma once

#include "Core/TypeDef.h"

namespace TikiEngine
{
	namespace AI
	{
		enum
		{
			Goal_Think,
			Goal_Wander,
			Goal_Seek_To_Position,
			Goal_Follow_Path,
			Goal_Traverse_Edge,
			Goal_Move_To_Position,
			Goal_Explore,
			Goal_Hunt_Target,
			Goal_Attack_GlobalTarget,
			Goal_Attack_Target,
			Goal_Attack_Move,
			Goal_Patrol
		};

		class GoalTypeToString
		{
		public:

			static wstring Convert(int gt)
			{
				switch(gt)
				{
				case Goal_Think : 
					return L"Think";
				case Goal_Wander : 
					return L"Wander";
				case Goal_Seek_To_Position : 
					return L"Seek_To_Position";
				case Goal_Follow_Path: 
					return L"Follow_Path";
				case Goal_Traverse_Edge : 
					return L"Traverse_Edge";
				case Goal_Move_To_Position : 
					return L"Move_To_Position";
				case Goal_Explore : 
					return L"Explore";
				case Goal_Hunt_Target : 
					return L"Hunt_Target";
				case Goal_Attack_GlobalTarget: 
					return L"Attack_Global_Target";
				case Goal_Attack_Target : 
					return L"Attack_Target";
				case Goal_Attack_Move : 
					return L"Attack_Move";
				case Goal_Patrol : 
					return L"Patrol";
				default:
					return L"UNKNOWN GOAL TYPE!";

				}//end switch
			}

		};


	}
}