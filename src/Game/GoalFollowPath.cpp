
#include "Game/GoalFollowPath.h"

#include "Game/GoalTraverseEdge.h"
#include "Game/GoalTypes.h"
#include "Core/IGraphics.h"


namespace TikiEngine
{
	namespace AI
	{
		GoalFollowPath::GoalFollowPath(TikiBot* bot, std::list<PathEdge> pathList)
			: GoalComposite<TikiBot>(bot, Goal_Follow_Path),
			  path(pathList)
		{
		}

		void GoalFollowPath::Activate(const UpdateArgs& args)
		{
			status = Active;
			
			// get a reference to the next edge
			PathEdge edge = path.front();

			// remove the edge from the path
			path.pop_front();

			// add a new subgoal to traverse an edge, if we loop, don't arrive
			AddSubgoal(new GoalTraverseEdge(owner, edge, path.empty()));
		}


		int GoalFollowPath::Process(const UpdateArgs& args)
		{
			// if status is inactive, call Activate()
			ActivateIfInactive(args);

			status = ProcessSubgoals(args);

			//if there are no subgoals present check to see if the path still has edges.
			//remaining. If it does then call activate to grab the next edge.
			if (status == Completed && !path.empty())
				Activate(args);

			return status;
		}


		void GoalFollowPath::Draw(const DrawArgs& args)
		{
#if _DEBUG
			std::list<PathEdge>::iterator it;
			for (it = path.begin(); it != path.end(); ++it)
			{
				Vector3 src = Vector3(it->Source().X, owner->Pos3D().Y, it->Source().Y);
				Vector3 dest = Vector3(it->Destination().X, owner->Pos3D().Y, it->Destination().Y);
				args.Graphics->DrawLine(src, dest, Color::White);
			}
#endif

			GoalComposite<TikiBot>::Draw(args);
		}

	}
}