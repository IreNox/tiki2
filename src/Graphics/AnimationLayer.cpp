#include "Graphics/AnimationLayer.h"

namespace TikiEngine
{
	namespace Resources
	{
		AnimationLayer::AnimationLayer()
		{	 
			 
		}

		AnimationLayer::~AnimationLayer()
		{	 
		}


		void AnimationLayer::Update(TikiAnimation* animation)
		{
			this->transformMatrix = Matrix::CreateFromQuaternion(LocalQuaternion(animation))
				* Matrix::CreateTranslation(LocalTranslation(animation));
		}

		Vector3 AnimationLayer::LocalTranslation(TikiAnimation* animation)
		{
			if(animation->Left == animation->Right)
				return translation[animation->Left];
			if(animation->Right == -1)
				return translation[animation->Left];
			if(animation->Left == -1)
				return translation[animation->Right];

			return Vector3::Lerp(translation[animation->Left], translation[animation->Right], animation->Koeff);
		}

		Quaternion AnimationLayer::LocalQuaternion(TikiAnimation* animation)
		{
			if(animation->Left == animation->Right)
				return quaternionen[animation->Left];
			if(animation->Right == -1)
				return quaternionen[animation->Left];
			if(animation->Left == -1)
				return quaternionen[animation->Right];

			return Quaternion::Slerp(quaternionen.Get(animation->Left), quaternionen.Get(animation->Right), animation->Koeff);

		}

		Vector3 AnimationLayer::LocalTranslation(int left, int right, float koeff)
		{
			if(left == right)
				return translation[left];
			if(right == -1)
				return translation[left];
			if(left == -1)
				return translation[right];

			return Vector3::Lerp(translation[left], translation[right], koeff);
		}

		Quaternion AnimationLayer::LocalQuaternion(int left, int right, float koeff)
		{
			if(left == right)
				return quaternionen[left];
			if(right == -1)
				return quaternionen[left];
			if(left == -1)
				return quaternionen[right];

			return Quaternion::Slerp(quaternionen.Get(left), quaternionen.Get(right), koeff);
		}

		Matrix AnimationLayer::LocalTransform(const double& time)
		{
			return transformMatrix;
		}

		List<Vector3>& AnimationLayer::GetTranslation()
		{
			return this->translation;
		}

		List<Quaternion>& AnimationLayer::GetQuaternion()
		{
			return this->quaternionen;
		}
	}
}