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
			TikiAnimation(FbxAnimStack* stack);
			~TikiAnimation();

			FbxAnimLayer* Layer();

		private:
			const char* name;

			FbxAnimLayer* layer;

			double startTime;
			double stopTime;
		};
	}
}