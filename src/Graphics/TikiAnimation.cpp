#include "Graphics/TikiAnimation.h"

namespace TikiEngine
{
	namespace Resources
	{
		TikiAnimation::TikiAnimation(FbxAnimStack* stack)
			:name(stack->GetName())
		{
			this->layer = stack->GetMember<FbxAnimLayer>(0);//<FbxAnimLayer>(0);
			int animationlayerCount = stack->GetSrcObjectCount<FbxAnimLayer>();

			FbxTakeInfo* take = stack->GetScene()->GetTakeInfo(this->name);

			this->startTime = take->mLocalTimeSpan.GetStart().GetSecondDouble();
			this->stopTime = take->mLocalTimeSpan.GetStop().GetSecondDouble();
		}
		TikiAnimation::~TikiAnimation()
		{

		}

		FbxAnimLayer* TikiAnimation::Layer()
		{
			return this->layer;
		}
	}
}