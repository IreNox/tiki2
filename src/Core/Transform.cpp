
#include "Core/Transform.h"

namespace TikiEngine
{
	Transform::Transform()
		: Position(0.0f), Rotation(Quaternion::Identity), Scale(1.0f)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::FillWorldMatrix(Matrix* worldMatrix) const
	{
		Matrix rot = Matrix::CreateFromQuaternion(this->Rotation);
		Matrix scale = Matrix::CreateScaleMatrix(this->Scale);
		Matrix trans = Matrix::CreateTranslation(this->Position);

		*worldMatrix = scale * rot * trans;
	}

	Vector3 Transform::GetForward()
	{
		return this->Rotation * Vector3::ForwardRH;
	}

	Vector3 Transform::GetUp()
	{
		return this->Rotation * Vector3::Up;
	}

	Vector3 Transform::GetLeft()
	{
		return this->Rotation * Vector3::Left;
	}
}