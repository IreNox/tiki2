#include "Graphics/TikiAnimation.h"

namespace TikiEngine
{
	namespace Resources
	{
		TikiAnimation::TikiAnimation(FbxAnimLayer* layer)
			:name(layer->GetName())
		{
			
			this->layer = layer;
		}
		TikiAnimation::~TikiAnimation()
		{

		}

		FbxAnimLayer* TikiAnimation::Layer()
		{
			return this->layer;
		}
		const char* TikiAnimation::Name()
		{
			return this->name;
		}

		double& TikiAnimation::StartTime()
		{
			return this->startTime;
		}

		double& TikiAnimation::StopTime()
		{
			return this->stopTime;
		}
	}
}