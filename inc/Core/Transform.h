#pragma once

#include "Core/Matrix.h"
#include "Core/Vector3.h"
#include "Core/Quaternion.h"

namespace TikiEngine
{	
	class GameObject;

	class Transform
	{
		friend class GameObject;

	public:

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		~Transform();

		Vector3 GetForward();
		Vector3 GetUp();
		Vector3 GetLeft();

		Vector3 GetPosition();
		void SetPosition(const Vector3& pos);

		Vector3 GetScale();
		void SetScale(const Vector3& scale);

		Quaternion GetRotation();
		void SetRotation(const Quaternion& rot);

		void FillWorldMatrix(Matrix* worldMatrix);

	private:

		Transform(GameObject* gameObject);

		bool isDirty;

		GameObject* gameObject;

		Matrix world;

		void checkWorldMatrix();

	};
}