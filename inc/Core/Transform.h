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

		inline Vector3 GetForward() const { return rotation * Vector3::Forward; }
		inline Vector3 GetUp() const { return rotation * Vector3::Up; }
		inline Vector3 GetLeft() const { return rotation * Vector3::Left; }

		inline const Vector3& GPosition() const { return position; }
		inline const Vector3& GScale() const { return scale; }
		inline const Quaternion& GRotation() const { return rotation; }

		inline Vector3& SPosition()		{ isDirty = true; isSGDirty = true; return position; }
		inline Vector3& SScale()		{ isDirty = true; return scale; }
		inline Quaternion& SRotation()	{ isDirty = true; return rotation; }

		inline bool IsDirty() { return isDirty; }
		void MarkAsClean();

		inline bool IsSGDirty() { return isSGDirty; }
		inline void MarkAsSGClean() { isSGDirty = false; }

		void FillWorldMatrix(Matrix* worldMatrix);
		inline const Matrix& GetWorld() { checkWorldMatrix(); return totalWorld; }

	private:

		GameObject* gameObject;

		bool isDirty;
		bool isSGDirty;
		Matrix goWorld;
		Matrix totalWorld;

		Vector3 position;
		Quaternion rotation;
		Vector3 scale;

		Transform();
		Transform(GameObject* gameObject);

		void checkWorldMatrix();

	};
}