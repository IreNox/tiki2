
#include "Core/Transform.h"

namespace TikiEngine
{
	#pragma region Class
	Transform::Transform(GameObject* gameObject)
		: position(0.0f), rotation(Quaternion::Identity), scale(1.0f), isDirty(true)
	{
	}

	Transform::~Transform()
	{
	}
	#pragma endregion

	#pragma region Member
	bool Transform::IsDirty()
	{
		return isDirty;
	}

	void Transform::MarkAsClean()
	{
		isDirty = false;
	}

	void Transform::FillWorldMatrix(Matrix* worldMatrix)
	{
		checkWorldMatrix();

		*worldMatrix = world;
	}
	#pragma endregion

	#pragma region  Member - Get Direction
	Vector3 Transform::GetForward()
	{
		return rotation * Vector3::ForwardRH;
	}

	Vector3 Transform::GetUp()
	{
		return rotation * Vector3::Up;
	}

	Vector3 Transform::GetLeft()
	{
		return rotation * Vector3::Left;
	}
	#pragma endregion

	#pragma region Member - Get/Set
	const Vector3& Transform::GPosition() const
	{
		return position;
	}

	Vector3& Transform::SPosition()
	{
		this->isDirty = true;
		return position;
	}

	const Vector3& Transform::GScale() const
	{
		return scale;
	}

	Vector3& Transform::SScale()
	{		
		this->isDirty = true;
		return scale;
	}

	const Quaternion& Transform::GRotation() const
	{
		return rotation;
	}

	Quaternion& Transform::SRotation()
	{
		this->isDirty = true;
		return rotation;
	}
	#pragma endregion

	#pragma region Private Member
	void Transform::checkWorldMatrix()
	{
		if (!isDirty) return;

		Matrix rot = Matrix::CreateFromQuaternion(this->rotation);
		Matrix scale = Matrix::CreateScaleMatrix(this->scale);
		Matrix trans = Matrix::CreateTranslation(this->position);

		world = scale * rot * trans;
		isDirty = false;
	}
	#pragma endregion
}