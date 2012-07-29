#pragma once

#include "Core/Matrix.h"
#include "Core/Vector3.h"
#include "Core/Quaternion.h"

namespace TikiEngine
{	
	class Transform
	{
	public:

		Vector3 Position;
		Quaternion Rotation;
		Vector3 Scale;

		Transform();
		~Transform();

		void FillWorldMatrix(Matrix* worldMatrix) const;
	};
}