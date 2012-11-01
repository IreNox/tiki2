#pragma once

#include "Game/NavigationCell.h"
#include "Game/NavigationPath.h"
#include "Game/NavigationMesh.h"

namespace TikiEngine
{
    namespace AI
    {
        class TikiBot;

        class PathPlanner
        {
        public:
            PathPlanner(TikiBot* bot);
            ~PathPlanner();

            bool Create(NavigationMesh* navMesh);

            //  Given a target, this method first determines if nodes can be reached from 
            //  the bot's current position and the target position. If either end point
            //  is unreachable the method returns false. 
            bool RequestPathTo(const Vector3& target);

            void Update(const UpdateArgs& args);
            void Draw(const DrawArgs& args);

        private:
            NavigationMesh* parent;
            NavigationCell* currentCell;
            TikiBot* bot;
            
            bool pathActive;				         // true when we are using a path to navigate
            NavigationPath path;			         // our path object
            NavigationPath::WayPointID nextWaypoint; // ID of the next waypoint we will move to

            Vector3 pathMovement;
            Vector3 pathPos;
        };

    }
}