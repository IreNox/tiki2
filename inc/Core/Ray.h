#pragma once

#include "Core/Vector3.h"
#include "Core/ICollider.h"

namespace TikiEngine
{
  using namespace TikiEngine::Components;

  struct Ray
  {
    Ray(const Vector3& origin, const Vector3& direction)
    {
      this->Origin = origin;
      this->Direction = direction;
    }

    Vector3 Origin;
    Vector3 Direction;
  };

  struct RaycastHit
  {
    /* The impact point in world space where the ray hit the collider. */
    Vector3 Point;

    /* The normal of the surface the ray hit. */
    Vector3 Normal;

    /* The distance from the ray's origin to the impact point. */
    Single Distance;

    /* The Collider that was hit. */
    ICollider* Collider;
  };
}