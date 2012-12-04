#include "Physics/ControllerHitReport.h"
#include "PhysX/Physics/NxActor.h"
#include "Core/ICollider.h"

namespace TikiEngine
{
    namespace Physics
    {
        NxControllerAction ControllerHitReport::onShapeHit(const NxControllerShapeHit& hit)
        {
            //if(1 && hit.shape)
            //{
            //    NxCollisionGroup group = hit.shape->getGroup();
            //    if(group != CG_Collidable_Non_Pushable)
            //    {
            //        NxActor& actor = hit.shape->getActor();
            //        if(actor.isDynamic())
            //        {

            //            // We only allow horizontal pushes. Vertical pushes when we stand on dynamic objects creates
            //            // useless stress on the solver. It would be possible to enable/disable vertical pushes on
            //            // particular objects, if the gameplay requires it.
            //            if(hit.dir.y == 0.0f)
            //            {
            //                NxF32 coeff = actor.getMass() * hit.length * 10.0f;
            //                actor.addForceAtLocalPos(hit.dir*coeff, NxVec3(0,0,0), NX_IMPULSE);
            //                //actor.addForceAtPos(hit.dir*coeff, hit.controller->getPosition(), NX_IMPULSE);
            //                //						actor.addForceAtPos(hit.dir*coeff, hit.worldPos, NX_IMPULSE);
            //            }
            //        }
            //    }
            //}

            return NX_ACTION_NONE;
        }

        NxControllerAction ControllerHitReport::onControllerHit(const NxControllersHit& hit)
        {
             NxActor* actor = hit.controller->getActor();
             NxActor* other = hit.other->getActor();
 
			 // check shape for group flags, not the freakin actor itself!
             if (other->getShapes()[0]->getGroup() != CG_Collidable_Non_Pushable)
             {
                 NxF32 coeff = 10.0f; //actor->getMass() * 1000.0f;
                 NxVec3 dir = hit.other->getPosition() - hit.controller->getPosition();
                 dir.y = 0;
                 dir.setMagnitude(0.05f);
                 //dir.normalize();

                 NxCCTInteractionFlag c, o;
                 c = hit.controller->getInteraction(); //save interaction states
                 o = hit.other->getInteraction();
                 hit.controller->setInteraction(NXIF_INTERACTION_EXCLUDE); //disable collision to stop recursive loop
                 hit.other->setInteraction(NXIF_INTERACTION_EXCLUDE);

                 NxU32 activeGroups = (1<<CG_Collidable_Non_Pushable) | 
                                      (1<<CG_Collidable_Pushable);
                 NxU32 cf;

                 hit.other->move(dir, activeGroups, 0.001f, cf);
                 hit.controller->setInteraction(c);
                 hit.other->setInteraction(o);

             }


            //NxActor* other = 
            //NxF32 coeff = hit.other->getActor().getMass() * hit.length * 10.0f;
           // actor.addForceAtLocalPos(hit.dir*coeff, NxVec3(0,0,0), NX_IMPULSE);


            return NX_ACTION_NONE;
        }

    }
}