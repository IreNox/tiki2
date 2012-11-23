#pragma once

#include "PhysX/NxCharacter/NxController.h"

namespace TikiEngine
{
    namespace Physics
    {
        class ControllerHitReport : public NxUserControllerHitReport
        {
            virtual NxControllerAction onShapeHit(const NxControllerShapeHit& hit);
            virtual NxControllerAction onControllerHit(const NxControllersHit& hit);
        };
    }
}