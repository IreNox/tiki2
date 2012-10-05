#pragma once

#include "Core/Vector3.h"

namespace TikiEngine
{
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
}