#pragma once

#include "Core/Matrix.h"
#include "Core/Vector3.h"

namespace TikiEngine
{	
	class Transform
	{
	public:

		Vector3 Position;
		Vector3 Rotation;
		Vector3 Scale;

		Transform();
		~Transform();

		void Move(Vector3 direction);

		Matrix* GetWorldMatrix();
	};
}