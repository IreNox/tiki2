#pragma once
#define FBXSDK_NEW_API
#include "fbxsdk.h"
#include "Core/TikiObject.h"


namespace TikiEngine
{
	namespace Resources
	{
		class TikiAnimation : public TikiObject
		{
		public:
			TikiAnimation(FbxAnimLayer* layer);
			~TikiAnimation();

			FbxAnimLayer* Layer();
			const char* Name();

			double& StartTime();
			double& StopTime();

		private:
			const char* name;

			FbxAnimLayer* layer;

			double startTime;
			double stopTime;
		};
	}
}