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

		~Transform();

		Vector3 GetForward();
		Vector3 GetUp();
		Vector3 GetLeft();

		const Vector3& Position() const;
		const Vector3& Scale() const;
		const Quaternion& Rotation() const;

		Vector3& Position();
		Vector3& Scale();
		Quaternion& Rotation();

		bool IsDirty();

		void FillWorldMatrix(Matrix* worldMatrix);

	private:

		GameObject* gameObject;

		bool isDirty;
		Matrix world;

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		Transform(GameObject* gameObject);

		void checkWorldMatrix();

	};
}